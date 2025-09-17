#include <stdio.h>
#include "queue.h"
#include "rubik-functions.h"
#include "hash-table.h"
#include "common.h"

int num = 0;

QUEUE* queue_new()
{
    QUEUE *q;
    q = (QUEUE*) malloc(sizeof(QUEUE));
    q -> front = NULL;
    q -> rear = NULL;
    return q;
}

void enqueue(QUEUE* q, NODE* newNode)
{
    if (!(q->front == NULL))
        q->rear->next = newNode;
    q->rear = newNode;

    if (q->front == NULL)
        q->front = q->rear;
}

void enqueueSorted(QUEUE* q, NODE* newNode, int fCost)
{
    // Se a fila estiver vazia, insira o primeiro elemento.
    if (!q->front)
    {
        q->front = newNode;
        q->rear = newNode;
        newNode->next = NULL; // Garantir que o next seja nulo
        return;
    }

    NODE* previous = NULL;
    NODE* current = q->front;

    // Percorre a fila até encontrar a posição correta
    // ou chegar ao fim da lista.
    while (current != NULL && fCost >= current->info.fCost)
    {
        previous = current;
        current = current->next;
    }

    // A posição correta está entre 'previous' e 'current'.
    
    // Se 'previous' for NULL, a inserção é no início da fila.
    if (previous == NULL)
    {
        newNode->next = q->front;
        q->front = newNode;
    }
    // Caso contrário, a inserção é no meio ou no fim.
    else
    {
        newNode->next = current;
        previous->next = newNode;
    }
    
    // Se 'current' for NULL, a inserção foi no fim da fila,
    // então atualizamos o 'rear'.
    if (current == NULL)
    {
        q->rear = newNode;
    }
}

void bfs_successors(QUEUE* q, NODE_INFO info, ht_t* ht, int* parentCube)
{
    int cube[24];
    info.depth++;

    for(int i = 6; i>0; i--)
    {       
        //if (!check_redundance(info.depth, info.movs, i)) {
            // monta o cubo do filho
            cp(parentCube, cube);
            apply_move(i, cube);
            cp(cube, info.cube);
            info.movs[info.depth] = i;

            // só insere se não estiver na hash
            // vou sempre passar 0 no terceiro argumento pois nao é necessario para esse tipo de busca
            if (!ht_get(ht, cube, 20)) {
                enqueue(q, gen_node(info));
                ht_set(ht, cube, info.depth);
            }
        //}
    }
}

void a_star_successors(QUEUE* q, NODE_INFO info, ht_t* ht, int *parentCube, ht_t* lookupTb)
{

    int cube[24], fCost;
    info.depth++;

    for(int i = 6; i>0; i--)
    {       
        //if (!check_redundance(info.depth, info.movs, i)) {
            // monta o cubo do filho
            cp(parentCube, cube);
            apply_move(i, cube);
            cp(cube, info.cube);
            info.movs[info.depth] = i;

            // só insere se não estiver na hash
            // vou sempre passar 0 no terceiro argumento pois nao é necessario para esse tipo de busca
            if (!ht_get(ht, cube, 0)) {
                // f(n) = g(n) + h(n)
                // f(n) = info.depth + ht->depth
                fCost = info.depth + get_heuristic_value(lookupTb, cube);
                info.fCost = fCost - random_num(0, 2);
                enqueueSorted(q, gen_node(info), fCost);
                ht_set(ht, cube, 0);
            }
       // }
    }
}

NODE* dequeue(QUEUE* q)
{
    NODE* temp = q->front;

    if (q->front == NULL)
    {
        printf("Fila vazia...");
        exit(1);
    }

    q->front = temp->next;

    if (q->front == NULL)
    {
        q->rear = NULL;
    }

    return temp;
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

