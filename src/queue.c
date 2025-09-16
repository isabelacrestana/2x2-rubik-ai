#include <stdio.h>
#include "queue.h"
#include "rubik-functions.h"
#include "hash-table.h"

int num = 0;

QUEUE* queue_new()
{
    QUEUE *q;
    q = (QUEUE*) malloc(sizeof(QUEUE));
    q -> front = NULL;
    q -> rear = NULL;
    return q;
}

void enqueue(QUEUE* q, int depth, int mov, int movs[], int cube[])
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

    num++;

    new_node->movs[depth] = mov;
    new_node->num = num;

    cp(cube, new_node->cube);

    new_node->depth = depth;
    new_node->next = NULL;

    if (!(q->front == NULL))
        q->rear->next = new_node;
    q->rear = new_node;

    if (q->front == NULL)
        q->front = q->rear;
}

void generate_successors(QUEUE* q, int depth, int movs[], int parent_cube[], ht_t* ht)
{
    int parent_mov, grandparent_mov, cube[24], canInsert;
    parent_mov = movs[depth - 1];

    if(depth>2)
    {
        grandparent_mov = movs[depth - 2];
    }

    for(int i = 6; i>0; i--)
    {
        //printf("movimento inserido = %d\n", f->rear->movimentos[indice]);
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
            // vou sempre passar 0 no terceiro argumento pois nao é necessario para esse tipo de busca
            if (!ht_get(ht, cube, 0)) {
                enqueue(q, depth, i, movs, cube);
                ht_set(ht, cube, 0);
            }
        }
    }
}

int visit_state(NODE *visited)
{
    // Checando se está montado
    if(evaluete_state(visited->cube))
        return 1;

    return 0;
}


void cp_movs(NODE *source, int target[])
{

    int depth = source->depth;

    for(int i = 0; i<depth+1; i++)
    {
        target[i] = source->movs[i];
    }
}

void dequeue(QUEUE* q)
{
    NODE* aux = q->front;

    if (q->front == NULL)
    {
        printf("Fila vazia...");
        exit(1);
    }

    aux = aux->next;
    free(q->front);
    q->front = aux;

    if (aux == NULL)
    {
        q->rear = NULL;
    }
}

QUEUE* queue_free(QUEUE* q)
{
    NODE* q_node = q->front;
    NODE* aux = q_node;

    while (q_node)
    {
        aux = aux->next;
        free(q_node);
        q_node = aux;
    }

    free(q);
    return NULL;
}

