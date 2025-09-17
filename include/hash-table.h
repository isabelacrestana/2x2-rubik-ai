#ifndef NEWHASH_H_INCLUDED
#define NEWHASH_H_INCLUDED

#define TABLE_SIZE 7348321
#define CUBE_SIZE 24      // tamanho do cubo 2x2x2

typedef struct entry_t {
    int cube[CUBE_SIZE];     // estado do cubo
    struct entry_t *next;    // pr�ximo da lista em caso de colis�o
    int depth;
} entry_t;

typedef struct {
    entry_t **entries;
} ht_t;

// Fun��o hash para o cubo
unsigned int hash_cube(const int cube[CUBE_SIZE]);

ht_t *ht_create(void);

// Compara dois estados do cubo
int cube_equal(const int a[CUBE_SIZE], const int b[CUBE_SIZE]);

// Inser��o na tabela hash
void ht_set(ht_t *hashtable, const int cube[CUBE_SIZE], int depth);

// Busca na tabela hash
int ht_get(ht_t *hashtable, int cube[CUBE_SIZE], const int depth);

// Libera a mem�ria da tabela hash
void ht_free(ht_t *hashtable);

int get_heuristic_value(ht_t *lookupTb, int *cube);

#endif // NEWHASH_H_INCLUDED
