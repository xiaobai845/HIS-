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
    if out: print(out)
    if err: print(err)

print("=== MongoDB container status ===")
run('cd /home/mongodb && docker-compose ps')

print()
print("=== MongoDB logs (last 5) ===")
run('docker logs mongodb --tail 5 2>&1')

ssh.close()
