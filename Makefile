all: main

main: main.o SStat.o
	g++ SStat.o main.o -o SStat

main.o: main.cpp
	g++ -c main.cpp

SStat.o: SStat.cpp
	g++ -c SStat.cpp

clean:
	rm -rf *.o SStat
