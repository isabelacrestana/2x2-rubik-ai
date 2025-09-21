#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
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
void enqueue(void* q, NODE* newNode);
void enqueue_sorted(void* q, NODE* newNode);
void bfs_successors(void* q, NODE_INFO info, ht_t* ht, int *parentCube, ht_t* lookupTb);
void a_star_successors(void* q, NODE_INFO info, ht_t* ht, int *parentCube,  ht_t* lookupTb);
int bfs_can_expand(NODE* node, int maxDepth);
int bfs_can_visit(NODE* node, int maxDepth);
NODE* dequeue(void* q);
QUEUE* queue_free(QUEUE* q);
int queue_empty(void* q);


#endif // QUEUE_H_INCLUDED
