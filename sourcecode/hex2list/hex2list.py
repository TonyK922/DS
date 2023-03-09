file_ori = open("log_origin.txt")
str = file_ori.read()
str = str.split(" ")
str2 = []
for i in range(0, len(str)):
	str2.append("0x"+ str[i]) 
str2 = ", ".join(str2)
str2 = "{" + str2 + "}"

file = open("log.txt", "w")

file.write(str2)