#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash-table.h"
#include "rubik-functions.h"

// Funcao hash para o cubo
unsigned int hash_cube(const int cube[CUBE_SIZE]) {
    unsigned long value = 0;
    for(int i = 0; i < CUBE_SIZE; i++) {
        value = value * 31 + cube[i]; // 31 ou 37 funcionam bem
    }
    return value % TABLE_SIZE;
}

// Cria tabela hash
ht_t *ht_create(void) {
    ht_t *hashtable = malloc(sizeof(ht_t));

    hashtable->entries = malloc(sizeof(entry_t*) * TABLE_SIZE);
    for(int i = 0; i < TABLE_SIZE; i++) {
        hashtable->entries[i] = NULL;
    }
    return hashtable;
}

// Compara dois estados do cubo
int cube_equal(const int a[CUBE_SIZE], const int b[CUBE_SIZE]) {
    for(int i = 0; i < CUBE_SIZE; i++) {
        if(a[i] != b[i]) return 0;
    }
    return 1;
}

// Inser��o na tabela hash
void ht_set(ht_t *hashtable, const int cube[CUBE_SIZE], int depth) {
    unsigned int slot = hash_cube(cube);

    // Cria nova entrada
    entry_t *new_entry = malloc(sizeof(entry_t));
    for(int i = 0; i < CUBE_SIZE; i++) {
        new_entry->cube[i] = cube[i];
    }
    new_entry->next = hashtable->entries[slot];
    new_entry->depth = depth;
    hashtable->entries[slot] = new_entry;
}

// Busca na tabela hash
int ht_get(ht_t *hashtable, int cube[CUBE_SIZE], const int depth) {
    unsigned int slot = hash_cube(cube);
    entry_t *entry = hashtable->entries[slot];

    while(entry) {
        if(cube_equal(entry->cube, cube))
        {
            if(entry->depth > depth)
            {
                entry->depth = depth;
                return -1;
            }
            return 1;
        }
        entry = entry->next;
    }

    return 0; // nao encontrado
}

// Libera a memoria da tabela hash
void ht_free(ht_t *hashtable) {
    for(int i = 0; i < TABLE_SIZE; i++) {
        entry_t *entry = hashtable->entries[i];
        while(entry) {
            entry_t *tmp = entry;
            entry = entry->next;
            free(tmp);
        }
    }
    free(hashtable->entries);
    free(hashtable);
}

int get_heuristic_value(ht_t *lookupTb, int *cube)
{
    int slot = hash_cube(cube);

    entry_t *entry = lookupTb->entries[slot];

    while(entry) {
        if(cube_equal(entry->cube, cube))
        {
            return entry->depth;            
        }
        entry = entry->next;
    }

    printf("Nao achei\n");

    return 0;
}
