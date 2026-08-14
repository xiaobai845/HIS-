import paramiko

ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())

try:
    ssh.connect('192.168.192.138', port=22, username='root', password='123456', timeout=15, look_for_keys=False, allow_agent=False)
    print('>>> connected')

    def run(cmd):
        print(f'>>> {cmd}')
        stdin, stdout, stderr = ssh.exec_command(cmd, timeout=15)
        out = stdout.read().decode().strip()
        err = stderr.read().decode().strip()
        if out: print(out)
        if err: print(err)

    # Step 1: stop + remove all containers
    run('docker stop dfs-storage dfs-tracker rocketmq-broker rocketmq-console rocketmq-namesrv')
    run('docker rm dfs-storage dfs-tracker rocketmq-broker rocketmq-console rocketmq-namesrv')

    # Step 2: copy DFS to /home
    run('cp -a /root/dfs /home/ 2>/dev/null; echo "DFS copied"')
    run('ls /home/dfs/docker/dockerfile_local/docker-compose.yml')

    # Step 3: copy RocketMQ to /home
    run('cp -a /root/rocketmq /home/ 2>/dev/null; echo "RocketMQ copied"')
    run('ls /home/rocketmq/5.3.1/docker-compose.yml')

    # Step 4: fix DFS docker-compose.yml paths
    run("sed -i 's|/root/dfs|/home/dfs|g' /home/dfs/docker/dockerfile_local/docker-compose.yml")
    run('grep /home/dfs /home/dfs/docker/dockerfile_local/docker-compose.yml')

    # Step 5: fix RocketMQ docker-compose.yml - write new one
    mq_yml = """services:
  rocketmq-namesrv:
    image: apache/rocketmq:5.3.1
    networks:
      - mq
    restart: always
    container_name: rocketmq-namesrv
    ports:
      - "9876:9876"
    environment:
      - JAVA_OPT_EXT=-server -Xms128m -Xmx128m -Xmn64m
      - TZ=Asia/Shanghai
    volumes:
      - ./namesrv/logs:/home/rocketmq/logs
      - ./namesrv/store:/home/rocketmq/store
      - /etc/localtime:/etc/localtime:ro
    command: sh mqnamesrv
  rocketmq-broker:
    image: apache/rocketmq:5.3.1
    networks:
      - mq
    restart: always
    container_name: rocketmq-broker
    ports:
      - "10909:10909"
      - "10911:10911"
      - "10912:10912"
      - "8081:8081"
      - "8082:8080"
    environment:
      - JAVA_OPT_EXT=-server -Xms128m -Xmx128m -Xmn64m
      - TZ=Asia/Shanghai
    volumes:
      - ./broker/logs:/home/rocketmq/logs
      - ./broker/store:/home/rocketmq/store
      - ./broker/conf/broker.conf:/home/rocketmq/conf/broker.conf
      - /etc/localtime:/etc/localtime:ro
    command: sh mqbroker -c /home/rocketmq/conf/broker.conf -n rocketmq-namesrv:9876 --enable-proxy
    depends_on:
      - rocketmq-namesrv
  rocketmq-console:
    image: apacherocketmq/rocketmq-dashboard:2.1.0
    networks:
      - mq
    restart: always
    container_name: rocketmq-console
    ports:
      - "8280:8082"
    environment:
      - JAVA_OPTS=-Drocketmq.namesrv.addr=rocketmq-namesrv:9876 -Dlogging.level.root=info -Dcom.rocketmq.sendMessageWithVIPChannel=false
      - TZ=Asia/Shanghai
    volumes:
      - /etc/localtime:/etc/localtime:ro
    depends_on:
      - rocketmq-namesrv
      - rocketmq-broker
networks:
  mq:
    name: rocketmq_network
    driver: bridge"""
    run(f"cat > /home/rocketmq/5.3.1/docker-compose.yml << 'EOF'\n{mq_yml}\nEOF")
    run('echo docker-compose.yml written')

    # Step 6: ensure broker conf dir + file
    run('mkdir -p /home/rocketmq/5.3.1/broker/conf')
    run('cp /home/rocketmq/5.3.1/conf/broker.conf /home/rocketmq/5.3.1/broker/conf/')
    run('chmod 644 /home/rocketmq/5.3.1/broker/conf/broker.conf')

    # Step 7: start DFS
    run('cd /home/dfs/docker/dockerfile_local && docker-compose up -d')

    # Step 8: start RocketMQ
    run('cd /home/rocketmq/5.3.1 && docker-compose up -d')

    print('=== Done ===')

except Exception as e:
    print(f'Error: {type(e).__name__}: {e}')

finally:
    ssh.close()
