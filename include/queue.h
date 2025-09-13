#ifndef BIBLIOT_BFS_H_INCLUDED
#define BIBLIOT_BFS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "hash-table.h"

extern int num;
//Estrutura dos elementos da fila
typedef struct node
{
    int movs[15];
    int cube[24];
    int depth;
    int num;
    struct node *next;  //aponta para o próx elemento
} NODE;

typedef struct Queue
{
    NODE *INICIO;
    NODE *FIM;
} QUEUE;

QUEUE* queue_new();
void enqueue(QUEUE* q, int depth, int mov, int movs[], int cube[]);
void generate_successors(QUEUE* q, int depth, int movs[], int parent_cube[], ht_t* ht);
int visit_state(NODE *visited);
void cp_movs(NODE *source, int target[]);
void dequeue(QUEUE* q);
QUEUE* queue_free(QUEUE* q);


#endif // BIBLIOT_BFS_H_INCLUDED
