# Name: Makefile
# Author: Khedesh
# Date: 02/24/2012, 3:07 PM
# Description: This is a Makefile for Traffic. It use Khagine for simulation.

CXX = g++
CFLAGS = `pkg-config gl glu sdl --cflags` -O2 -Wall -g -pipe -L$(KHAGINE_LIB) -I$(KHAGINE_INCLUDE)
LIBS = -lkhagine `pkg-config gl glu sdl --libs` -lglut

KHAGINE_DIR = ../Engine/khagine/v0.0.3
KHAGINE_LIB = $(KHAGINE_DIR)/build
KHAGINE_INCLUDE = $(KHAGINE_LIB)/include

BIN_DIR = ./bin
BUILD_DIR = ./build
INCLUDE_DIR = ./include
SRC_DIR = ./src

TARGET = $(BIN_DIR)/traffic
OUT_FILE = test.log

TAR = tar
GZIP = gzip

RM = rm

MAX_SIM_TIME = 10000

.PHONY: obj run gz clean

obj:
	$(MAKE) -C $(SRC_DIR)

run: $(TARGET)
	$(TARGET) $(MAX_SIM_TIME) $(OUT_FILE)
	$(MAKE) run -C ./test/graphics2d

gz:
	$(TAR) -cf traffic.tar ../traffic-backup
	$(GZIP) traffic.tar

clean:
	$(RM) -f $(TARGET)
	$(MAKE) -C $(SRC_DIR) clean
	$(RM) -f $(OUT_FILE)
	$(RM) -f traffic.tar.gz
