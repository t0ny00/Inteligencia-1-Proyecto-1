Directorio contenedor de los archivos necesarios para obtener los resultados de la actividad 4,
además de la tabla con todos los resultados obtenidos.

Esta actividad consistía implementar A* y IDA* para resolver las instancias provistas para cada 
problema.


El directorio contiene los siguientes archivos PSVN

	*pancakes28.psvn, para el problema de pancakes con 28 panquecas
	*15puzzle.psvn, para el problema del 15-Puzzle

A su vez, los programas ya compilados para ejecutar cada cálculo.
Estos son los siguientes:

	*pancakes28.a_starGap, programa que calcula los resultados para el problema de pancakes con 28 panquecas mediante la Heuristica Gap con el Algoritmo de A*

	*pancakes28.idaGap, programa que calcula los resultados para el problema de pancakes con 28 panquecas
	mediante la Heuristica Gap con el Algoritmo de IDA*

	*15puzzle.a_starMan, programa que calcula los resultados para el problema de 15 puzzle
	mediante la Heuristica Manhattan con el Algoritmo de A*

	*15puzzle.a_starPDB, programa que calcula los resultados para el problema de 15 puzzle
	mediante la Heuristica PDB con el Algoritmo de A*

	*15puzzle.idaMan, programa que calcula los resultados para el problema de 15 puzzle
	mediante la Heuristica Manhattan con el Algoritmo de IDA*

	*15puzzle.idaPDB, programa que calcula los resultados para el problema de 15 puzzle
	mediante la Heuristica PDB con el Algoritmo de IDA*

De igual forma se encuentran los archivos abstractores para la Heuristica PDB utilizada por 15 puzzle,
encontrando asi tanto los psvn como los archivos con extension '.abst'.

Además, se uso el programa hecho en python 15puzzle_executer.py para correr los algoritmos con limite 
de memoria y atrapar las excepciones en caso de que una instancia sobrepasara la cantidad de memoria
límite.

Para correr cada algoritmo seria de la forma:
./algoritmo archivoEntrada.txt archivoSalida

El directorio 'Tablas Resultados' contiene varios archivos CSV que contienen los resultados obtenidos al correr cada uno de estos programas, en ellos se encuentra la salida calculada con tiempo limite
de 5 minutos, en cada tabla se puede apreciar tanto el Dominio como la Heuristica utilizada para calcular la respuesta.
