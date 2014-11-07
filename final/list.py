f = open('list.txt','w')
for count in range(1024):
  name = "frame"
  name = name + str(count)
  name = name + ".jpg\n"
  f.write(name)
f.close()
