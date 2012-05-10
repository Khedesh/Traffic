# Makefile for LemonGraphics

CXX = g++
CFLAGS = -O2 -Wall -g -pipe
LIBS = -lSDL -lSDL_gfx -lSDL_ttf -lSDL_image -lm -lpthread

TOP = .

SRCS = $(wildcard $(TOP)/*.cpp)
OBJS = $(patsubst $(TOP)/%.cpp, $(TOP)/%.o, $(SRCS))

BIN = $(TOP)/LemonGraphics

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(TOP)/%.o: $(TOP)/%.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

run:
	$(BIN)

clean:
	rm -f $(OBJS) $(BIN)
