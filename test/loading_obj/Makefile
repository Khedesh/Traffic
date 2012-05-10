# Makefile for obj loader

CXX = g++
CFLAGS = `pkg-config --cflags gl glu` -g -Wall -O2 -pipe
LIBS = `pkg-config --libs gl glu` -lglut -lm -lpthread -lfreeimage

SRCS = main.cpp obj.cpp texture.cpp
OBJS = $(patsubst %.cpp, %.o, $(SRCS))

all: $(OBJS)
	$(CXX) $(OBJS) $(CFLAGS) $(LIBS) -o main

%.o: %.cpp
	$(CXX) $< $(CFLAGS) -c -o $@

clean:
	rm -f *.o
