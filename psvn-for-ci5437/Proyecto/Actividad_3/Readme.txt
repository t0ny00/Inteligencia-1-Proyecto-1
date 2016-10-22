Directorio contenedor de los archivos y programas necesarios para obtener los resultados de las actividades 3
además de las tablas con todos los resultados obtenidos

Esta actividad consiste en implementar un algoritmo de búsqueda ciega que opere en los árboles de búsqueda
de los problemas especificado, encontrando los costos de los caminos óptimos al goal para distintas instancias

El directorio contiene los siguientes archivos PSVN:

	*pancake16.psvn, para el prolema de pancakes con 16 panquecas
	*11puzzle.psvn, para el problema del 11-Puzzle
	*TopSpinCompact16_4.psvn, para el TopSpin 16-4
	*hanoi14_4.psvn, para el problema de Tower of Hanoi 14-4

A su vez, los programas ya compilados para ejecutar cada cálculo
Estos son los siguientes

	*pancake16.dfid, programa que calcula los resultados para el problema de pancakes con 16 panquecas
	*11puzzle.dfid, programa que calcula los resultados para el problema de 11-Puzzle
	*TopSpinCompact16_4.dfid, programa que calcula los resultados para el problema de TopSpin 16-4
	*hanoi144.dfid, programa que calcula los resultados para el problema de Tower of Hanoi de 14 discos con 4 estacas

estos programas se corren de la siguiente manera: ./nombreprograma.dfid (archivo entrada) (archivo salida)

También contiene el archivo Makefile para compilar cada uno de estos programas cuando así sea necesario

El directorio Resultados contiene un archivo CSV por cada problema en los cuales se encuentran las tablas con
los resultados de los mismos