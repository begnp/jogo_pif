CC = gcc
CFLAGS = -Wall -std=c99

INCLUDE_DIR = include
RAYLIB_INCLUDE = /usr/include
INCLUDES = -I $(INCLUDE_DIR) -I $(RAYLIB_INCLUDE)

LIB_DIRS = -L /usr/lib
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
TARGET = $(BIN_DIR)/game

all: $(TARGET)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(BIN_DIR) $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIB_DIRS) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ_DIR)/*.o
	rm -f $(BIN_DIR)/game

.PHONY: all run clean