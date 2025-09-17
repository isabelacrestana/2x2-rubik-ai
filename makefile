CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC = $(wildcard src/*.c)
OBJ_SRC = $(patsubst src/%.c,obj/%.o,$(SRC))

MAIN = apps/main.c
OBJ_MAIN = obj/main.o

BIN_MAIN = bin/rubik

LOOKUP_TB = apps/lookup_table_gen.c
OBJ_LOOKUP_TB = obj/lookup_table_gen.o

BIN_LOOKUP_TB = bin/lookup-tb

# Alvo padrão
all: $(BIN_MAIN)

$(BIN_MAIN): $(OBJ_SRC) $(OBJ_MAIN)
	$(CC) $(CFLAGS) $(OBJ_SRC) $(OBJ_MAIN) -o $(BIN_MAIN)

# Compila objetos dos src
obj/%.o: src/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Compila objeto da main
obj/%.o: apps/%.c
	mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@


# Criar a lookuptable
lookup_table: $(BIN_LOOKUP_TB)

$(BIN_LOOKUP_TB): $(OBJ_SRC) $(OBJ_LOOKUP_TB)
	$(CC) $(CFLAGS) $(OBJ_SRC) $(OBJ_LOOKUP_TB) -o $(BIN_LOOKUP_TB)

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
	rm *.bin