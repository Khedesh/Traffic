# Makefile for Graphics of Traffic

CXX = g++
CFLAGS = -O2 -Wall -g -pipe -I$(INCLUDE_DIR)
LIBS = -lSDL -lSDL_image -lSDL_ttf -lSDL_gfx

SRC_DIR = .
OBJ_DIR = .
INCLUDE_DIR = .
BIN_DIR = .

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

TARGET = $(BIN_DIR)/graphics
FILE = ../../test.log

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) $(LIBS) -o $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

run:
	$(TARGET) $(FILE)

clean:
	rm -f $(OBJS) $(TARGET)
