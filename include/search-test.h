#ifndef SEARCHTEST_H_INCLUDED
#define SEARCHTEST_H_INCLUDED
#include "queue.h"
#include "stack.h"
#include "hash-table.h"

void run_search(int *cube, int search_type, ht_t* lookupTb);
NODE* exec_search(QUEUE* q, STACK* s, ht_t* ht, ht_t* lookupTB, int *cube, int bfsSearch, int maxDepth);
NODE* loopDFS(QUEUE *q, STACK *s, ht_t* ht, int cube[]);

#endif // SEARCHTEST_H_INCLUDED
