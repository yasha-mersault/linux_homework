CC = g++
CFLAGS = -Wall -std=c++17
TARGET = demo-application

all: parallel_scheduler.o demo_application.o
	$(CC) -o $(TARGET) parallel_scheduler.o demo_application.o

parallel_scheduler.o: parallel_scheduler.cpp parallel_scheduler.h
	$(CC) $(CFLAGS) -c parallel_scheduler.cpp

demo_application.o: demo_application.cpp parallel_scheduler.h
	$(CC) $(CFLAGS) -c demo_application.cpp

clean:
	rm -f *.o $(TARGET)
