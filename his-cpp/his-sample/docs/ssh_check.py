import paramiko

ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect('192.168.192.138', port=22, username='root', password='123456', timeout=15, look_for_keys=False, allow_agent=False)

def run(cmd):
    stdin, stdout, stderr = ssh.exec_command(cmd, timeout=10)
    out = stdout.read().decode().strip()
    err = stderr.read().decode().strip()
    if out: print(out)
    if err: print(err)

print("=== DFS ===")
run('cd /home/dfs/docker/dockerfile_local && docker-compose ps')

print("\n=== RocketMQ ===")
run('cd /home/rocketmq/5.3.1 && docker-compose ps')

ssh.close()
