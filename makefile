CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = $(wildcard src/*.c)
MAIN = apps/main.c
BIN_MAIN = bin/rubik

LOOKUP_TB = apps/lookup_table_gen.c
BIN_LOOKUP_TB = bin/lookup-tb

# Alvo padrão
all: $(BIN_MAIN)

$(BIN_MAIN): $(SRC) $(MAIN)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) $(MAIN) -o $(BIN_MAIN)

# Criar a lookuptable
lookup_table: $(BIN_LOOKUP_TB)

$(BIN_LOOKUP_TB): $(SRC) $(LOOKUP_TB)
	mkdir -p bin
	$(CC) $(CFLAGS) $(SRC) $(LOOKUP_TB) -o $(BIN_LOOKUP_TB)

# Limpeza
clean:
	rm -rf bin/*
