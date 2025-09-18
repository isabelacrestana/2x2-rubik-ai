#ifndef BIBLIOT_BFS_H_INCLUDED
#define BIBLIOT_BFS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "hash-table.h"
#include "common.h"

extern int num;

typedef struct Queue
{
    NODE *front;
    NODE *rear;
} QUEUE;

QUEUE* queue_new();
void enqueue(QUEUE* q, NODE* newNode);
void enqueueSorted(QUEUE* q, NODE* newNode, int fCost);
void bfs_successors(QUEUE* q, NODE_INFO info, ht_t* ht, int *parentCube);
void a_star_successors(QUEUE* q, NODE_INFO info, ht_t* ht, int *parentCube,  ht_t* lookupTb);
NODE* dequeue(QUEUE* q);
QUEUE* queue_free(QUEUE* q);


#endif // BIBLIOT_BFS_H_INCLUDED
