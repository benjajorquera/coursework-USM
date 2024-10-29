#1
getwd()
Datos = read.csv(file="cdc_zika.csv", sep = ",")
summary(Datos)
Datos = subset(Datos, value != "" & report_date != "" )
Datos = Datos[complete.cases(Datos$value),]
Datos = Datos[complete.cases(Datos$report_date),]
Datos$value = as.numeric(as.character(Datos$value))
Datos = Datos[complete.cases(Datos$value),]
Datos = Datos[,!sapply(Datos,function(x) any(is.na(x)))]

Datos.sub.usa = Datos[grep("United_States", Datos$location),]
Datos.sub.arg = Datos[grep("Argentina", Datos$location),]
Datos.sub.bra = Datos[grep("Brazil", Datos$location),]
Datos.sub.col = Datos[grep("Colombia", Datos$location),]
Datos.sub.mex = Datos[grep("Mexico", Datos$location),]

Datos.sub.usa = subset(Datos.sub.usa, value != 0)	
Datos.sub.arg = subset(Datos.sub.arg, value != 0)
Datos.sub.bra = subset(Datos.sub.bra, value != 0)
Datos.sub.col = subset(Datos.sub.col, value != 0)
Datos.sub.mex = subset(Datos.sub.mex, value != 0)

Datos.sub.usa = Datos.sub.usa[grepl("confirmed", Datos.sub.usa$data_field) & !grepl("microcephaly", Datos.sub.usa$data_field) | grepl("reported", Datos.sub.usa$data_field),]
Datos.sub.arg = Datos.sub.arg[grepl("confirmed", Datos.sub.arg$data_field) & !grepl("microcephaly", Datos.sub.arg$data_field) | grepl("reported", Datos.sub.arg$data_field),]
Datos.sub.bra = Datos.sub.bra[grepl("confirmed", Datos.sub.bra$data_field) & !grepl("microcephaly", Datos.sub.bra$data_field) | grepl("reported", Datos.sub.bra$data_field),]
Datos.sub.col = Datos.sub.col[grepl("confirmed", Datos.sub.col$data_field) & !grepl("microcephaly", Datos.sub.col$data_field) | grepl("reported", Datos.sub.col$data_field),]
Datos.sub.mex = Datos.sub.mex[grepl("confirmed", Datos.sub.mex$data_field) & !grepl("microcephaly", Datos.sub.mex$data_field) | grepl("reported", Datos.sub.mex$data_field),]

Datos.sub.usa$location = as.character(Datos.sub.usa$location)
Datos.sub.usa$location = "United_States"
Datos.sub.usa$location = as.factor(Datos.sub.usa$location)
Datos.sub.arg$location = as.character(Datos.sub.arg$location)
Datos.sub.arg$location = "Argentina"
Datos.sub.arg$location = as.factor(Datos.sub.arg$location)
Datos.sub.bra$location = as.character(Datos.sub.bra$location)
Datos.sub.bra$location = "Brazil"
Datos.sub.bra$location = as.factor(Datos.sub.bra$location)
Datos.sub.col$location = as.character(Datos.sub.col$location)
Datos.sub.col$location = "Colombia"
Datos.sub.col$location = as.factor(Datos.sub.col$location)
Datos.sub.mex$location = as.character(Datos.sub.mex$location)
Datos.sub.mex$location = "Mexico"
Datos.sub.mex$location = as.factor(Datos.sub.mex$location)

mean(Datos.sub.usa$value) 
var(Datos.sub.usa$value) 
median(Datos.sub.usa$value)
quantile(Datos.sub.usa$value)
mean(Datos.sub.arg$value)
var(Datos.sub.arg$value)
median(Datos.sub.arg$value) 
quantile(Datos.sub.usa$value) 
mean(Datos.sub.bra$value) 
var(Datos.sub.bra$value)
median(Datos.sub.bra$value)
quantile(Datos.sub.bra$value) 
mean(Datos.sub.col$value) 
var(Datos.sub.col$value) 
median(Datos.sub.col$value) 
quantile(Datos.sub.col$value)
mean(Datos.sub.mex$value)
var(Datos.sub.mex$value)
median(Datos.sub.mex$value)
quantile(Datos.sub.mex$value) 

boxplot(Datos.sub.usa$value, Datos.sub.arg$value, Datos.sub.bra$value, Datos.sub.col$value, Datos.sub.mex$value, main="Virus Zika", xlab = "Paises" , ylab = "Numero de casos infectados", outline = FALSE ,ylim=c(0,30), col = c("blue"), varwidth = TRUE,  names = c("USA","Argentina","Brazil","Colombia","Mexico"))
boxplot(Datos.sub.usa$value, Datos.sub.arg$value, Datos.sub.bra$value, Datos.sub.col$value, Datos.sub.mex$value, main="Virus Zika", xlab = "Paises" , ylab = "Numero de casos infectados", outline = FALSE ,ylim=c(0,5000), col = c("blue"), varwidth = TRUE,  names = c("USA","Argentina","Brazil","Colombia","Mexico"))

#2

Datos = read.csv(file="titanic_data.csv", sep = ",")
Datos = subset(Datos, Survived != 0)
Datos.sub.h = subset(Datos, Sex == "male")
Datos.sub.m = subset(Datos, Sex == "female")

boxplot(Datos.sub.h$Age, Datos.sub.m$Age, main = "Edades supervivientes" , xlab = "Sexo" , ylab = "Edad", outline = FALSE ,ylim=c(0,80), col = c("green"), varwidth = TRUE,  names = c("Hombre", "Mujer"))

g = hist(Datos$Fare, plot=F)
g$counts = g$counts / sum(g$counts)
plot(g, freq=TRUE, ylab="Frecuencia Relativa", main = "Histograma precios pagados", xlab = "", col=c("green"))

Datos = subset(Datos, Cabin != "")

Datos.sub.cab1 = Datos[grep("A", Datos$Cabin),]
Datos.sub.cab2 = Datos[grep("B", Datos$Cabin),]
Datos.sub.cab3 = Datos[grep("C", Datos$Cabin),]

L = matrix(c(7,35,35),ncol=3,byrow=TRUE)
colnames(L) = c("A", "B", "C")
barplot(L, main="Casos sobrevivientes por tipo de cabina", xlab = "Cabina", ylab = "Sobrevivientes", col = c("green"))
