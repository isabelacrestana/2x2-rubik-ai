#ifndef BIBLIOT_DFS_H_INCLUDED
#define BIBLIOT_DFS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "hash-table.h"

extern int numEstados;

// Estrutura que guarda o endere�o do primeiro elemento do tipo struct NO
typedef struct Stack
{
    NODE *top;
} STACK;

STACK* stack_new();
void push(STACK* s, int depth, int mov, int movs[], int cube[]);
void stack_generate_successors(STACK* s, int depth, int movs[], int parent_cube[], ht_t *ht);
NODE* pop(STACK* s);
STACK* stack_free(STACK* s);

#endif // BIBLIOT-DFS_H_INCLUDED
