#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "queue.h"
#include "rubik-functions.h"

NODE* gen_node(NODE_INFO info)
{
    NODE* newNode;
    newNode = (NODE*) malloc(sizeof(NODE));
    newNode->info = info;
    newNode->next = NULL;
    return newNode;
}

int check_redundance(int depth, int *movs, int mov)
{
    int parent_mov, grandparent_mov;
    parent_mov = movs[depth - 1];

    if(depth>2)
    {
        grandparent_mov = movs[depth - 2];
        if(grandparent_mov == parent_mov && parent_mov == mov)
        {
            return 1;
        }
    }

    if(parent_mov%2 == 0)
    {
        // garantindo que nao eh o mov contrario
        if(mov == parent_mov-1)
            return 1;
    }

    // garantindo que nao eh o mov contrario
    if(mov == parent_mov + 1)
        return 1;

    return 0;
}

void cp_movs(int source[], int target[], int depth)
{
    for(int i = 0; i<depth+1; i++)
    {
        target[i] = source[i];
    }
}

int visit_state(NODE *visited)
{
    // Checando se está montado
    if(evaluete_state(visited->info.cube))
        return 1;

    return 0;
}