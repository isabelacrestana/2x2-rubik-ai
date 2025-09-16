#include <stdio.h>
#include "queue.h"
#include "stack.h"
#include "rubik-functions.h"
#include "hash-table.h"

int numEstados = 0;

STACK* stack_new()
{
    STACK* s = (STACK*) malloc(sizeof(STACK));
    s->top = NULL;  // aponta inicialmente para um endereço nulo
    return s;   //retorna o endereço
}

void push(STACK* s, int depth, int mov, int movs[], int cube[])
{
    NODE* new_node;
    new_node = (NODE*) malloc(sizeof(NODE));

    if(depth>0)
    {
        for(int i = 0; i<depth; i++)
        {
            new_node->movs[i] = movs[i];
        }
    }

    new_node->movs[depth] = mov;
    numEstados++;
    new_node->num = numEstados;

    cp(cube, new_node->cube);

    new_node->depth = depth;
    new_node->next = s->top;

    s->top = new_node;
}

void stack_generate_successors(STACK* s, int depth, int movs[], int parent_cube[], ht_t *ht)
{
    int parent_mov, grandparent_mov, cube[24], canInsert;
    parent_mov = movs[depth - 1];

    if(depth>2)
    {
        grandparent_mov = movs[depth - 2];
    }

    for(int i = 1; i<7; i++)
    {
        //printf("movimento inserido = %d\n", f->FIM->movimentos[indice]);
        canInsert = 1;
        if(depth>2)
        {
            if(grandparent_mov == parent_mov && parent_mov == i)
            {
                canInsert = 0;
            }
        }

        if(parent_mov%2 == 0)
        {
            // garantindo que nao eh o mov contrario
            if(i == parent_mov-1)
                canInsert = 0;
        }

        else
        {
            // garantindo que nao eh o mov contrario
            if(i == parent_mov + 1)
                canInsert = 0;
        }

        if (canInsert) {
            // monta o cubo do filho
            cp(parent_cube, cube);
            apply_move(i, cube);

            // só insere se não estiver na hash
            int exists = ht_get(ht, cube, depth);
            if(exists != 1)
            {
                push(s, depth, i, movs, cube);
                if(exists == -1)
                    numEstados--;
                else
                    ht_set(ht, cube, depth);
            }
        }
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


