# Name: Makefile
# Author: Khedesh
# Date: 02/24/2012, 3:46 PM

CXX = g++

TOP = ..

CXX = g++
CFLAGS = `pkg-config gl glu sdl --cflags` -O2 -Wall -g -pipe -L$(KHAGINE_LIB) -I$(KHAGINE_INCLUDE) -I$(INCLUDE_DIR)
LIBS = -lkhagine `pkg-config gl glu sdl --libs` -lglut -lfreeimage -lSDL_image

KHAGINE_DIR = $(TOP)/../../Engine/khagine/v0.0.3
KHAGINE_LIB = $(KHAGINE_DIR)/build
KHAGINE_INCLUDE = $(KHAGINE_DIR)/include

BIN_DIR = $(TOP)/bin
BUILD_DIR = $(TOP)/build
INCLUDE_DIR = $(TOP)/include
SRC_DIR = .

SRCS = road.cpp bound.cpp car.cpp mesh.cpp obj_mesh_loader.cpp texture_loader.cpp \
	c3ds_mesh_loader.cpp graphics.cpp traffic.cpp main.cpp
OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRCS))

.PHONY: all clean

TARGET = $(BIN_DIR)/traffic

all: $(TARGET)

$(OBJS): $(BUILD_DIR)/%.o: ./%.cpp
	$(CXX) -c $(CFLAGS) $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CFLAGS) $(OBJS) $(LIBS) -o $@

clean:
	$(RM) -f $(OBJS)
