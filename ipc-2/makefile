all: prime-calculator

prime-calculator: prime_calculator.o
	g++ -o prime-calculator prime_calculator.o

prime_calculator.o: prime_calculator.cpp
	g++ -c prime_calculator.cpp

clean:
	rm -f *.o prime-calculator
