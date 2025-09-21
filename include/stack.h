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
void push(void* s, NODE* newNode);
void dfs_successors(void* s, NODE_INFO info, ht_t* ht, int *parentCube, ht_t* lookupTb);
NODE* pop(void* s);
int dfs_can_expand(NODE* node, int maxDepth);
int dfs_can_visit(NODE* node, int maxDepth);
STACK* stack_free(STACK* s);
int stack_empty(void* s);

#endif // BIBLIOT-DFS_H_INCLUDED
