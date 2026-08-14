# -*- coding: utf-8 -*-
import paramiko, sys
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

print("=== Create DB + collection + insert data ===")
run('''docker exec mongodb6 mongosh --quiet --eval "
    use hospital;
    db.patients.insertOne({name: 'zhangsan', age: 28, sex: 'M', createTime: new Date()});
    db.patients.insertOne({name: 'lisi', age: 35, sex: 'F', createTime: new Date()});
    print('Inserted 2 records');
"''')

print()
print("=== Query all ===")
run('''docker exec mongodb6 mongosh --quiet --eval "
    use hospital;
    print('Total: ' + db.patients.countDocuments({}));
    printjson(db.patients.find().toArray());
"''')

ssh.close()
