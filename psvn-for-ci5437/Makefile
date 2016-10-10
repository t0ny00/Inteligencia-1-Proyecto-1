CC = gcc
CXX = g++
#OPT = -g
OPT = -g -Wall -O3


bin/psvn2c: src/psvn2c.cpp src/psvn2c.hpp src/psvn.cpp src/psvn.hpp
	$(CXX) $(OPT) src/psvn2c.cpp src/psvn.cpp -o $@

clean:
	rm -fr bin/psvn2c bin/*.dSYM *.o *~
