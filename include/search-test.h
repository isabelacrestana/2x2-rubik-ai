#ifndef SEARCHTEST_H_INCLUDED
#define SEARCHTEST_H_INCLUDED
#include "queue.h"
#include "stack.h"
#include "hash-table.h"
#include "callback_fuctions.h"

void run_search(int *cube, int search_type, ht_t* lookupTb);
NODE* exec_search(void* ds, ht_t* ht, ht_t* lookupTB, int *cube, SearchStrategy* strategy, int maxDepth);
NODE* loopDFS(void *s, ht_t* ht, int cube[], SearchStrategy* strategy);

#endif // SEARCHTEST_H_INCLUDED
