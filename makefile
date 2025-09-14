CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = $(wildcard src/*.c)
OBJ_SRC = $(patsubst src/%.c,obj/%.o,$(SRC))

MAIN = apps/main.c
OBJ_MAIN = obj/main.o

BIN = bin/rubik

# Alvo padrão
all: $(BIN)

$(BIN): $(OBJ_SRC) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_SRC) $(OBJ_MAIN) -o $(BIN)

# Compila objetos dos src
obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Compila objeto da main
obj/%.o: apps/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf obj/*.o bin/*
