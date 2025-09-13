#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED
#include "queue.h"
#include "stack.h"
#include "hash-table.h"

void bfs(int cubo[], QUEUE* f);
void loopDFS(int cubo[], STACK *p);
int iidfs(int max_depth, STACK* s, int cube[], ht_t *ht);

#endif // SEARCH_H_INCLUDED
