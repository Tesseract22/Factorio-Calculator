
from subprocess import Popen, PIPE
import os
import csv


cwd = os.getcwd()
os.chdir(r"C:\Users\caleb\HelloWorld\Calculator")

p = Popen([r'bin\socket.exe'], shell=True, stdout=PIPE, stdin=PIPE,)

item = "sulfur" + '\n'
item = bytes(item, 'UTF-8')
p.stdin.write(item)
p.stdin.flush()

amount = "5" + '\n'
amount = bytes(amount, 'UTF-8')
p.stdin.write(amount)
p.stdin.flush()
os.chdir(cwd)

lines = p.stdout.readlines()
res = []
print(lines)

res = []
for l in lines:
    res.append(l[:-1].decode("utf-8"))
reader = csv.reader(res, delimiter=',')