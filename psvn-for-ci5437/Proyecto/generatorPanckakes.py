
a = []
for i in range(24):
	a.append('X' + str(i))

for i in range(2,25):
	regla = ""
	letras = ""
	rayitas = ""
	for j in range(i):
		regla += a[j]+' '
		letras = a[j]+' ' + letras
	for k in range(24-i):
		rayitas += '- '
	regla += rayitas + '=> ' + letras + rayitas
	print (regla)