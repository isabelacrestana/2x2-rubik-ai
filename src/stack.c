#include <stdio.h>
#include "stack.h"
#include "rubik-functions.h"
#include "hash-table.h"
#include "common.h"
#include "queue.h"

STACK* stack_new()
{
    STACK* s = (STACK*) malloc(sizeof(STACK));
    s->top = NULL;  // aponta inicialmente para um endereço nulo
    return s;   //retorna o endereço
}

void push(STACK* s, NODE* newNode)
{
    newNode->next = s->top;
    s->top = newNode;
}

void dfs_successors(STACK* s, NODE_INFO info, ht_t* ht, int *parentCube)
{
    int cube[24];
    info.depth++;

    for(int i = 1; i<7; i++)
    {
        //if (!check_redundance(info.depth, info.movs, i)) {
            // monta o cubo do filho
            cp(parentCube, cube);
            apply_move(i, cube);
            cp(cube, info.cube);
            info.movs[info.depth] = i;

            // só insere se não estiver na hash
            int exists = ht_get(ht, cube, info.depth);
            if(exists != 1)
            {
                push(s, gen_node(info));
                if(exists == -1)
                    num--;
                else
                    ht_set(ht, cube, info.depth);
            }
        //}
    }
}

NODE* pop(STACK* s)
{
    if (s->top == NULL)
    {
        printf("Pilha Vazia...");
        exit(1);
    }

    NODE* aux = s->top;

    s->top = s->top->next;
    return aux;
}

STACK* stack_free(STACK* s)
{
    NODE* aux = s->top;  // aux recebe o endereço do top da pilha

    while(aux != NULL)    //loop que desaloca elemento por elemento
    {
        NODE* n = aux->next;  //variável que guarda endereço do próx elemento
        free(aux);            //libera estrutura NO
        aux = n;              //aux recebe end do próximo elemento
    }

    free(s);  //Libera estutura que guardava o end do top da pilha
    return NULL;   // Pilha aponta para nulo
}


