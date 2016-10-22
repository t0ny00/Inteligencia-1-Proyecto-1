Directorio contenedor de los archivos y programas necesarios para obtener los resultados de las actividades 5
además de las tablas con todos los resultados obtenidos

Esta actividad consiste en implementar el algoritmo WIDA* para calcular las distancias óptimas al goal
en una serie de instancias de distintos problemas dados, con una limitación de 10 minutos por corrida y
2GBs de uso de memoria

En el directorio se encuentran los siguientes archivos PSVN:

	*pancakes28.psvn, para el problema de pancakes con 28 panquecas
	*15puzzle.psvn, para el problema de 15-Puzzle

A su vez, los programas ya compilados para ejecutar cada cálculo
Estos son los siguientes

	*pancakes28.widaGap, programa que calcula los resultados para el problema de pancakes28 con el algoritmo WIDA* utilizando la heurística gap
	*15puzzle.widaMan, programa que calcula los resultados para el problema de 15-Puzzle con el algoritmo WIDA* utilizando la heurística Manhattan
	*15puzzle.widaPDB, programa que calcula los resultados para el problema de 15-Puzzle con el algoritmo WIDA* utilizando la heurística PDB

De igual manera, el directorio contiene los archivos de extensión .abst y el ejecutale abstractor utilizados en conjunto para generar los archivos
de entrada y poder obtener los resultados de la actividad

También contiene el archivo Makefile para compilar cada uno de estos programas cuando así sea necesario

El directorio Tablas Resultados contiene un archivo CSV por cada problema en los cuales se encuentran las tablas con
los resultados de los mismos