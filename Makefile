# Caminhos e opções
CC       := gcc
CFLAGS   := -Iinclude -O2 -Wall -Wextra -Wno-unused-parameter
LDFLAGS  := -lraylib -lopengl32 -lgdi32 -lwinmm
SRC      := $(wildcard src/*.c)
BIN_DIR  := bin
OUT_EXE  := $(BIN_DIR)/raygame.exe

.PHONY: all run clean

all: $(OUT_EXE)

$(OUT_EXE): $(SRC)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT_EXE) $(LDFLAGS)

run: all
	./$(OUT_EXE)

clean:
	@rm -rf $(BIN_DIR)
