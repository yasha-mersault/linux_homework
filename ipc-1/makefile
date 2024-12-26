all: signal-echo

signal-echo: signal_echo.o
	g++ -o signal-echo signal_echo.o

signal_echo.o: signal_echo.cpp
	g++ -c signal_echo.cpp

clean:
	rm -f *.o signal-echo
