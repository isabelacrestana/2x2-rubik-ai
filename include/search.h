#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#include "queue.h"
#include "stack.h"
#include "hash-table.h"

void run_search(int cube[], int search_type);
NODE* exec_search(QUEUE* q, STACK* s, int *cube, int bfsSearch, int maxDepth);
NODE* loopDFS(QUEUE *q, STACK *s, int cube[]);

#endif // SEARCH_H_INCLUDED
