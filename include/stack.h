#ifndef BIBLIOT_DFS_H_INCLUDED
#define BIBLIOT_DFS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "hash-table.h"

extern int numEstados;

// Estrutura que guarda o endere�o do primeiro elemento do tipo struct NO
typedef struct Stack
{
    NODE *top;
} STACK;

STACK* stack_new();
void push(STACK* s, NODE* newNode);
void dfs_successors(STACK* s, NODE_INFO info, ht_t* ht, int *parentCube);
NODE* pop(STACK* s);
STACK* stack_free(STACK* s);

#endif // BIBLIOT-DFS_H_INCLUDED
