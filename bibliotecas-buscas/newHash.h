#ifndef NEWHASH_H_INCLUDED
#define NEWHASH_H_INCLUDED

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 7348321
#define CUBE_SIZE 24      // tamanho do cubo 2x2x2

typedef struct entry_t {
    int cube[CUBE_SIZE];     // estado do cubo
    struct entry_t *next;    // próximo da lista em caso de colisão
    int depth;
} entry_t;

typedef struct {
    entry_t **entries;
} ht_t;

// Função hash para o cubo
unsigned int hash_cube2(const int cube[CUBE_SIZE]) {
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

// Inserção na tabela hash
void ht_set(ht_t *hashtable, const int cube[CUBE_SIZE], int depth) {
    unsigned int slot = hash_cube2(cube);
    entry_t *entry = hashtable->entries[slot];

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
int ht_get(ht_t *hashtable, const int cube[CUBE_SIZE], const int depth) {
    unsigned int slot = hash_cube2(cube);
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
    return 0; // não encontrado
}

// Libera a memória da tabela hash
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

// Exemplo de uso
/*int main() {
    ht_t *ht = ht_create();

    int cube1[CUBE_SIZE] = {0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5};
    int cube2[CUBE_SIZE] = {1,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5};

    ht_set(ht, cube1);
    ht_set(ht, cube2);

    if(ht_get(ht, cube1)) {
        printf("cube1 encontrado!\n");
    }
    if(ht_get(ht, cube2)) {
        printf("cube2 encontrado!\n");
    }

    ht_free(ht);
    return 0;
}
*/
#endif // NEWHASH_H_INCLUDED
