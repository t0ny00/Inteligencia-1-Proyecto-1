Directorio contenedor de los archivos y programas necesarios para obtener los resultados de las actividades 1 y 2
además de la tabla con todos los resultados obtenidos

Esta actividad consistía en comparar los árboles de búsqueda generados para distintos problemas
cada uno con distintos niveles de eliminación de duplicados.

Para esto el algoritmo generador para los problemas fue implementado con DFS.

El directorio contiene los siguientes archivos PSVN

	*pancakes24.psvn, para el prolema de pancakes con 24 panquecas
	*pancakes28.psvn, para el problema de pancakes con 28 panquecas
	*11puzzle.psvn, para el problema del 11-Puzzle
	*TopSpinCompact22_4.psvn, para el TopSpin 22-4
	*TopSpinCompact26_4.psvn, para el TopSpin 26-4
	*hanoi14_4.psvn, para el problema de Tower of Hanoi 14-4
	*hanoi16_4.psvn, para el problema de Tower of Hanoi 16-4

A su vez, los programas ya compilados para ejecutar cada cálculo
Estos son los siguientes

	*pancakes24.searchTreeDFS, programa que calcula los resultados para el problema de pancakes con 24 panquecas
	*pancakes28.searchTreeDFS, programa que calcula los resultados para el problema de pancakes con 28 panquecas
	*11puzzle.searchTreeDFS, programa que calcula los resultados para el problema del 11-Puzzle
	*TopSpinCompact22_4.searchTreeDFS, programa que calcula los resultados para el problema de TopSpin 22-4
	*TopSpinCompact26_4.searchTreeDFS, programa que calcula los resultados para el problema de TopSpin 26-4
	*hanoi14_4.searchTreeDFS, programa que calcula los resultados para el problema de Tower of Hanoi 14-4
	*hanoi16_4.searchTreeDFS, programa que calcula los resultados para el problema de Tower of Hanoi 16-4

También contiene el archivo Makefile para compilar cada uno de estos programas cuando así sea necesario

El directorio Resultados contiene un archivo CSV que contiene los resultados obtenidos al correr cada uno de estos
programas