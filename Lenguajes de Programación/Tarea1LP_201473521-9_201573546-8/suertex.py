import re
import webbrowser

"""Expresiones regulares"""

re_separar = re.compile(r"(\s|\{|^)([0-9]{4,})(?!(\\|\w|\/|\{))")
re_fecha=re.compile(r"([0][1-9]|[12][0-9]|3[01])([^\s\d\w])([0][1-9]|[1][0-2])([^\s\d\w])(\d{4})")
re_cmd1=re.compile(r"\\(item|inicio|fin|titulo|nproy){+(.+)}")
re_cmd2=re.compile(r"\\(fn|fc)+{([\w\d! <>/]+)}")
re_cmd3=re.compile(r"\\(fn|fc)+?\{([^\\\{\}]+)\}")
re_func=re.compile(r"\\(separamiles|ofecha){}")
re_error1=re.compile(r"\\([a-zA-Z]+)+{")
re_error2=re.compile(r"[\\\{\}]+?")


##Funciones Globales##

"""
def tseparar(texto):
	Funcion que recibe una linea de texto y busca
	numeros de 4 o mas digitos que luego separa
	por puntos.
	
	Retorna la misma linea con los numeros separados 
	por miles.
"""

def tseparar(texto):
	c=0
	l=[]
	a=[]
	if re_separar.search(texto)!=None:
		nums = re_separar.findall(texto)	
		for tupla in nums:					
			numero = tupla[1]
			for char in numero:
				l.append(char)
			l.reverse()
			for j in l:
				if c ==3:
					a.append('.')
					c=0
				a.append(j)
				c+=1
			a.reverse()
			c=0
			numfinal = ''.join(a)
			texto = texto.replace(numero,numfinal)
			l=[]
			a=[]
	return texto

"""
def ofecha(texto):
	Funcion que recibe una linea de texto y busca
	fechas validas que luego cambia sus separadores a '/'.

	Retorna la misma linea con las fechas con los separadores '/'.
"""

def ofecha(texto):
	if re_fecha.search(texto)!=None:
		fechas = re_fecha.findall(texto)
		for tupla in fechas:
			fecha = ''+tupla[0]+tupla[1]+tupla[2]+tupla[3]+tupla[4]
			newfecha = ''+tupla[0]+'/'+tupla[2]+'/'+tupla[4]
		texto = texto.replace(fecha,newfecha)
		return texto

##Comandos Globales##

"""
def fnfc(txt):
	Funcion que recibe una linea de texto y busca
	comandos fn y fc solos y anidados de forma recursiva
	comprobando una ves transormado todo a html (cuando no hay comandos,
	linea de texto pura) revisa que no hayan \ }{ en el texto, de lo contrario
	corta el programa dando error de sintaxtis por consola.

	Retorna la linea de texto con todos los comandos fn y fc validos transformados a html.
"""

def fnfc(txt):
	m = re_cmd3.search(txt)
	if m != None:
		if m.group(1) == "fn":
			return fnfc(txt.replace(m.group(0),"<strong>"+m.group(2)+"</strong>"))
		elif m.group(1) == "fc":
			return fnfc(txt.replace(m.group(0),"<em>"+m.group(2)+"</em>"))
	m2 = re_error2.search(txt)
	if m2 != None:
		errorc()
	return txt

"""
def nproy(texto):
	Funcion que recibe un str como parametro y crea otro str modificado
    para el archivo HTML

	Retorna texto mas las cabeceras.
"""

def nproy(texto):
	h = "<head>\n<title>"+texto+"</title>\n</head>\n<body>\n"
	return h

"""
def titulo(texto):
	Funcion que recibe un str como parametro y crea otro str modificado
    para el archivo HTML

	Retorna texto mas las etiquetas de titulo.
"""

def titulo(texto):
	h = "<h1>"+fnfc(texto)+"</h1>\n"
	return h

"""
def inicio(texto):
	Funcion que recibe un str como parametro y comprueba si se trata
    de lista punteada o lista enumarada para su modificacion, si no
    tiene alguno de estos 2 textos, corta el programa devolviendo
    error por consola.

	Retorna texto mas las etiquetas de lista segun corresponda.
"""

def inicio(texto):
	if texto == "lista_punteada":
		h = "<ul>\n"
	elif texto == "lista_enumerada":
		h = "<ol>\n"
	else:
		errorc()
	return h

"""
def item(texto):
	Funcion que recibe un str como parametro y crea otro str modificado
    para el archivo HTML

	Retorna texto mas las etiquetas de item.
"""

def item(texto):
	h = "<li>"+fnfc(texto)+"</li>\n"
	return h

"""
def fin(texto):
	Funcion que recibe un str como parametro y comprueba si se trata
    de lista punteada o lista enumarada para su modificacion, si no
    tiene alguno de estos 2 textos, corta el programa devolviendo
    error por consola.

	Retorna texto mas las etiquetas de lista segun corresponda.
"""

def fin(texto):
	if texto == "lista_punteada":
		h = "</ul>\n"
	elif texto == "lista_enumerada":
		h = "</ol>\n"
	else:
		errorc()
	return h

"""
def transformar(cmdtxt):
	Funcion que recibe una lista con una tupla con 2 valores, el nombre del
	comando y el contenido del texto, luego los transforma a html llamando
	a las funciones anteriores.

	Retorna el texto con los comandos en html.
"""

def transformar(cmdtxt):
	if cmdtxt != None:
		cmd = cmdtxt[0][0]
		txt = cmdtxt[0][1]
		if cmd == 'nproy':
			return nproy(txt)
		elif cmd == 'titulo':
			return titulo(txt)
		elif cmd == 'inicio':
			return inicio(txt)
		elif cmd == 'item':
			return item(txt)
		elif cmd == 'fin':
			return fin(txt)

"""
def hacer(txt):
	Funcion que recibe una lista de tupla/s con los valores, el nombre del
	comando y el contenido del texto, y un flag, el proposito es confirmar 
	la existencia de separamiles y/o ofecha y verificar si hay fechas o numeros 
	miles dentro de los argumentos de los comandos transformandolos de ser asi.
	Y 

	Retorna la lista de tupla/s con las fechas y/o miles cambiados.
"""

def hacer(cmdtxt,flag):

	cmd = cmdtxt[0][0]
	txt = cmdtxt[0][1]
	cant_func= len(flag)

	if cant_func == 2:
		if re_fecha.search(txt) != None:
			txt = ofecha(txt)
		if re_separar.search(txt) != None:
			txt = tseparar(txt)
		return [(cmd,txt)]	
	elif cant_func == 1:
		if flag[0]=='separamiles':
			if re_separar.search(txt) != None:
				txt = tseparar(txt)
			return [(cmd,txt)]
		elif flag[0]=='ofecha':
			if re_fecha.search(txt) != None:
				txt = ofecha(txt)
			return [(cmd,txt)]
	else:
		return [(cmd,txt)]

"""
def hacer2(txt,flag):
	Funcion que recibe una linea de texto y un flag. Y separa miles y/o 
	cambia las fechas segun sea el caso detectando la existencia de estas
	funciones gracias al flag.

	Retorna el texto con las fechas y/o miles cambiados.
"""

def hacer2(txt,flag):
	cant_func= len(flag)
	if cant_func == 2:
		if re_fecha.search(txt) != None:
			txt = ofecha(txt)
		if re_separar.search(txt) != None:
			txt = tseparar(txt)
		return txt
	elif cant_func == 1:
		if flag[0]=='separamiles':
			if re_separar.search(txt) != None:
				txt = tseparar(txt)
			return txt
		elif flag[0]=='ofecha':
			if re_fecha.search(txt) != None:
				txt = ofecha(txt)
			return txt
	else:
		return txt

"""
def parrafo(linea):
	Esta funcion recibe una linea de texto plano y agrega la etiqueta de parrafo
	a los extremos de este string.

	Retorna la linea de texto transformada a html.
"""

def parrafo(linea):								
	linea= '<p>'+linea
	linea= linea.replace('\n','</p>\n')
	return linea

###Funciones Errores###

"""
def cmdnoexiste(linea):
	Funcion que recibe una linea de texto y busca la existencia de comandos en ella
	para luego determinar si existe dicho comando o no.

	Retorna True en caso de no existir el comando, caso contrario retorna False.
"""

def cmdnoexiste(linea):
	cmds = ['item','inicio','fin','titulo','nproy','fn','fc','separamiles','ofecha']
	c = re_error1.findall(linea)
	for tupla in c:
		if tupla not in cmds:
			return True
	return False

"""
def errores(arch,flaggy):
	Funcion que recorre el archivo en busca de errores, como el comando no existe
	o si se repite separamiles u ofecha en el texto.

	Retorna True en caso de haber error y caso contrario retorna False.
"""

def errores(arch,flaggy):
	flag=False
	for linea in arch:
		if re_error1.search(linea) != None:
			if cmdnoexiste(linea) == True:
				return True
		if re_func.search(linea) != None:
			lt=re_func.findall(linea)
			if lt[0]=='separamiles':
				if flaggy['aparecesepara']==False:
					flaggy['aparecesepara']=True
				else:
					return True
			elif lt[0]=='ofecha':
				if flaggy['apareceofecha']==False:
					flaggy['apareceofecha']=True
				else:
					return True

	return False

"""
def errorc():
	Funcion cuyo unico proposito es cortar el programa en caso de haber un error de sintaxis
	mientras se recorre el archivo por segunda vez.

	No retorna nada.
"""

def errorc():
	print "Error de Sintaxtis"
	exit(0)


##### Main #####
flaggy={
	'incio':True,
	'aparecenproy':False,
	'aparecesepara':False,
	'apareceofecha':False,

}
Flag=[]
archivo = open("SuerTex.txt","r")
archivo2= open("SuerTex.txt","r")
conc=''
if errores(archivo2,flaggy) == False:					#Se revisan los errores antes de proceder
	archivo2.close()
	pagina = open("test.html", "w")
	conc += "<!DOCTYPE HTML>\n"
	for linea in archivo:
		if re_func.match(linea) != None:		#Si la linea es una funcion
			c = re_func.findall(linea)			#Buscamos que funciones existen
			Flag.append(c[0])					#Guardamos cuales hay

		elif re_cmd1.search(linea) != None:		#Si la linea es un comando distinto de fn y fc
			c = re_cmd1.findall(linea)     		#Buscamos el comando y su argumento [('item', 'bien')]
			p = hacer(c,Flag) 					#Buscamos si hay fechas y/o miles para transformar
			conc += transformar(p)              #Luego transformamos a HTML
		else:									#Si la linea es solo parrafo
			linea = hacer2(linea,Flag)			#Buscamos si hay fechas y/o miles para transformar
			conc += parrafo(fnfc(linea))
	conc+='</body>'
	pagina.write(conc)
	pagina.close()
	webbrowser.open_new_tab("test.html")
	archivo.close()
else:
	print "Error de Sintaxis"

