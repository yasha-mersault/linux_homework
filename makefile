CC=g++
CCFLAGS=-c

all: complex_numbers

complex_numbers: main.o complex.o sort.o
	$(CC) main.o complex.o sort.o -o complex_numbers

main.o: main.cpp
	$(CC) $(CCFLAGS) main.cpp

complex.o: complex.cpp
	$(CC) $(CCFLAGS) complex.cpp

sort.o: sort.cpp
	$(CC) $(CCFLAGS) sort.cpp

clean:
	rm -rf *.o complex_numbers


