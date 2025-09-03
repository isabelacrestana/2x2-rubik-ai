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

#define TABLE_SIZE 8388617    // Primo próximo de 4 milhões

typedef struct HashEntry {
    CubeState state;
    struct HashEntry* next;
} HashEntry;

HashEntry* hash_table[TABLE_SIZE] = {0};

// Compara dois estados
int compare_cubes(const CubeState a, const CubeState b) {
    for (int i = 0; i < 24; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

// Insere na tabela hash se não existir, retorna 1 se inseriu, 0 se já existia
int insert_if_not_exists(const CubeState cube) {
    uint32_t h = hash_cube(cube) % TABLE_SIZE;

    HashEntry* curr = hash_table[h];
    while (curr) {
        if (compare_cubes(curr->state, cube)) {
            return 0; // Já existe
        }
        curr = curr->next;
    }

    HashEntry* new_entry = malloc(sizeof(HashEntry));
    if (!new_entry) {
        fprintf(stderr, "Erro de alocação\n");
        exit(1);
    }
    memcpy(new_entry->state, cube, sizeof(CubeState));
    new_entry->next = hash_table[h];
    hash_table[h] = new_entry;

    return 1; // Inserido novo estado
}

#endif // HASH_H_INCLUDED
