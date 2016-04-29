OBJS = Graph.o World.o main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

main: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o main

main.o: main.cpp Graph.h
	$(CC) $(CFLAGS) main.cpp

Graph.o: Graph.cpp Graph.h World.h
	$(CC) $(CFLAGS) Graph.cpp

World.o: World.cpp World.h
	$(CC) $(CFLAGS) World.cpp

