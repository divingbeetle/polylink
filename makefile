TARGET = polylink

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Compiler
CC = gcc
CFLAGS = -Wall -I$(INC_DIR)
LFLAGS = 

# Files
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Rules
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -g
endif

all: directories $(BIN_DIR)/$(TARGET)

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(TARGET): $(OBJ)
	$(CC) $^ -o $@ $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) 

clean:
	rm -rf $(OBJ_DIR) 
	rm -rf $(BIN_DIR)

.PHONY: all clean