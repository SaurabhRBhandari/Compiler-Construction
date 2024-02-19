# read t1.txt
s = open('t1.txt', 'r').read()
# remove /n
s = s.replace('\n', '')
s = s.replace(' ', '')
print(s)