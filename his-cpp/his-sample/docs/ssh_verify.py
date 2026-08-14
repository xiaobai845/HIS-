# -*- coding: utf-8 -*-
import paramiko
import sys
sys.stdout.reconfigure(encoding='utf-8')

ssh = paramiko.SSHClient()
ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
ssh.connect('192.168.192.138', port=22, username='root', password='123456', timeout=15, look_for_keys=False, allow_agent=False)

def run(cmd):
    stdin, stdout, stderr = ssh.exec_command(cmd, timeout=10)
    out = stdout.read().decode().strip()
    err = stderr.read().decode().strip()
    return out, err

print("=" * 50)
print("1. DFS - upload file test")
print("=" * 50)
out, err = run("docker exec dfs-storage bash -c \"echo 'dfs-ok-$(date +%s)' > /tmp/test.txt && /usr/bin/fdfs_upload_file /etc/fdfs/client.conf /tmp/test.txt\"")
if 'group1' in out:
    file_path = [l for l in out.split('\n') if 'group1' in l][-1].strip()
    print("upload OK: " + file_path)
    out2, _ = run("curl -s http://192.168.192.138:8888/" + file_path)
    if 'dfs-ok' in out2:
        print("download OK: " + out2)
    else:
        print("download FAILED")
else:
    print("upload FAILED")
    print(out)
    print(err)

print()
print("=" * 50)
print("2. RocketMQ - namesrv port 9876")
print("=" * 50)
out, _ = run("ss -tlnp | grep 9876")
print(out if out else "9876 is listening")

print()
print("=" * 50)
print("3. RocketMQ - broker last 5 logs")
print("=" * 50)
out, _ = run("docker logs rocketmq-broker --tail 5 2>&1")
print(out)

print()
print("=" * 50)
print("4. RocketMQ - console HTTP check")
print("=" * 50)
out, _ = run("curl -s -o /dev/null -w '%{http_code}' http://192.168.192.138:8280")
print("HTTP code: " + out)

print()
print("=" * 50)
print("5. All containers")
print("=" * 50)
out, _ = run("docker ps --format 'table {{.Names}}\t{{.Status}}\t{{.Ports}}' | head -6")
print(out)

ssh.close()
