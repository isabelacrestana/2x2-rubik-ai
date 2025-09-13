CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = $(wildcard src/*.c)
OBJ_SRC = $(patsubst src/%.c,obj/%.o,$(SRC))

MAIN_WINDOWS = apps/main-windows.c
MAIN_UNIX    = apps/main-unix.c
OBJ_MAIN_WINDOWS = obj/main-windows.o
OBJ_MAIN_UNIX    = obj/main-unix.o

# Alvo padrão (Windows)
windows: $(OBJ_SRC) $(OBJ_MAIN_WINDOWS)
	$(CC) $(CFLAGS) $(OBJ_SRC) $(OBJ_MAIN_WINDOWS) -o bin/rubik-windows

# Alvo Unix
unix: $(OBJ_SRC) $(OBJ_MAIN_UNIX)
	$(CC) $(CFLAGS) $(OBJ_SRC) $(OBJ_MAIN_UNIX) -o bin/rubik-unix

# Compila objetos dos src
obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Compila objetos das mains
obj/%.o: apps/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza
clean:
	rm -rf obj/*.o bin/*
