#Carga de datos
dataOrig <- read.csv("D:/Universidad/2023/2023-1/Lenguajes_de_programacion/TI/SobelLP/SobelLP/imgO.csv", header = TRUE)
dataModiC <- read.csv("D:/Universidad/2023/2023-1/Lenguajes_de_programacion/TI/SobelLP/SobelLP/imgC.csv", header = TRUE)
dataModiB <- read.csv("D:/Universidad/2023/2023-1/Lenguajes_de_programacion/TI/SobelLP/SobelLP/imgB.csv", header = TRUE)
#Generar vectores simples
hist_valuesO <- unlist(dataOrig)
hist_valuesMC <- unlist(dataModiC)
hist_valuesMB <- unlist(dataModiB)
#Histogramas
hO <- hist(hist_valuesO, main = "Histograma", xlab = "Valor", ylab = "Frecuencia", breaks = 45, col = "#7FB3D5")
hMC <- hist(hist_valuesMC, main = "Histograma", xlab = "Valor", ylab = "Frecuencia", breaks = 45, col = "#7FB3D5")
hMB <- hist(hist_valuesMB, main = "Histograma", xlab = "Valor", ylab = "Frecuencia", breaks = 45, col = "#7FB3D5")
#Lineas de frecuencia
install.packages("agricolae")
library(agricolae)
polygon.freq(hO, frequency = 1, 
             col = "darkred", lwd = 2)
polygon.freq(hMC, frequency = 1, 
             col = "darkred", lwd = 2)
polygon.freq(hMB, frequency = 1, 
             col = "darkred", lwd = 2)

