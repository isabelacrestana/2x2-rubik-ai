#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t CubeState[24];

// Função hash FNV-1a
uint32_t hash_cube(const CubeState cube) {
    uint32_t hash = 2166136261u;
    for (int i = 0; i < 24; i++) {
        hash ^= cube[i];
        hash *= 16777619u;
    }
    return hash;
}

// Tamanho da tabela (primo próximo de 8 milhões, bom para BFS grande)
#define TABLE_SIZE 8388617

typedef struct HashEntry {
    CubeState state;
    int depth;
    struct HashEntry* next;
} HashEntry;

HashEntry* hash_table[TABLE_SIZE];  // cada posição é uma lista ligada

//int current_generation = 0;

// Inicializa a hash table
void init_hash() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_table[i] = NULL;
    }
}

// Compara dois estados
int compare_cubes(const CubeState a, const CubeState b) {
    return memcmp(a, b, sizeof(CubeState)) == 0;
}

// Insere na tabela hash se não existir, retorna 1 se inseriu, 0 se já existia
int insert_if_not_exists(const CubeState cube, int depth) {
    uint32_t h = hash_cube(cube) % TABLE_SIZE;

    HashEntry* curr = hash_table[h];
    while (curr) {
        if (compare_cubes(curr->state, cube)){
            if(curr->depth > depth) {
                curr->depth = depth;
                return -1;
            }
            return 0;
        }
        curr = curr->next;
    }

    // Se o estado não foi encontrado, cria um novo nó para encadear
    HashEntry* new_entry = malloc(sizeof(HashEntry));
    if (!new_entry) {
        fprintf(stderr, "Erro de alocação\n");
        exit(1);
    }
    memcpy(new_entry->state, cube, sizeof(CubeState));
    new_entry->depth = depth;
    new_entry->next = hash_table[h];
    hash_table[h] = new_entry;

    return 1; // Inserido novo estado
}

#endif // HASH_H_INCLUDED
