# Makefile para Rubik

CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,obj/%.o,$(SRC))
APP = bin/rubik
MAIN = apps/main.c

# Regra padrão
all: $(APP)

# Compila o executável
$(APP): $(OBJ) $(MAIN)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(OBJ) $(MAIN) -o $(APP)

# Compila os objetos na pasta obj
obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza de arquivos compilados
clean:
	rm -f obj/*.o $(APP)

.PHONY: all clean
