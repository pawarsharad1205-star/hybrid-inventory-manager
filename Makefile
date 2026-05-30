CXX      := g++
CC       := gcc
CFLAGS   := -Wall -Wextra -std=c11   -Iinclude
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude
TARGET   := inventory_manager

SRC_C   := src/inventory.c
SRC_CXX := src/InventoryManager.cpp src/main.cpp

OBJ_C   := $(SRC_C:.c=.o)
OBJ_CXX := $(SRC_CXX:.cpp=.o)
OBJS    := $(OBJ_C) $(OBJ_CXX)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile C source as C
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Compile C++ source as C++
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET) inventory.dat
