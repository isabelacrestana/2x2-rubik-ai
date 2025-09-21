#ifndef CALLBACK_FUNCTIONS_H_INCLUDED
#define CALLBACK_FUNCTIONS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "hash-table.h"
#include "common.h"
#include "queue.h"
#include "stack.h"

typedef struct SEARCH_STRATEGY
{
    void (*insert)(void* dataStructre, NODE* node);
    NODE* (*remove)(void* dataStructure);
    void (*successor_function)(void* ds, NODE_INFO info, ht_t* ht, int* cube, ht_t* lookupTb);
    int (*can_spand)(NODE* node, int maxDepth);
    int (*can_visit)(NODE* node, int maxDepth);
    int (*ds_empty)(void* ds);
} SearchStrategy;   

#endif // CALLBACK_FUNCTIONS_H_INCLUDED
