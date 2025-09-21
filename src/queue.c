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

void enqueue(void* q, NODE* newNode)
{
    QUEUE* queue = (QUEUE*) q;
    if (!(queue->front == NULL))
        queue->rear->next = newNode;
    queue->rear = newNode;

    if (queue->front == NULL)
        queue->front = queue->rear;
}

void enqueue_sorted(void* q, NODE* newNode)
{
    QUEUE* queue = (QUEUE*) q;
    int fCost = newNode->info.fCost;
    // Se a fila estiver vazia, insira o primeiro elemento.
    if (!queue->front)
    {
        queue->front = newNode;
        queue->rear = newNode;
        newNode->next = NULL; // Garantir que o next seja nulo
        return;
    }

    NODE* previous = NULL;
    NODE* current = queue->front;

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
        newNode->next = queue->front;
        queue->front = newNode;
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
        queue->rear = newNode;
    }
}

void bfs_successors(void* q, NODE_INFO info, ht_t* ht, int *parentCube, ht_t* lookupTb)
{
    int cube[24];
    info.depth++;

    for(int i = 6; i>0; i--)
    {       
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
    }
}

void a_star_successors(void* q, NODE_INFO info, ht_t* ht, int *parentCube, ht_t* lookupTb)
{
    int cube[24], fCost;
    info.depth++;

    for(int i = 6; i>0; i--)
    {       
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
            enqueue_sorted(q, gen_node(info));
            ht_set(ht, cube, 0);
        }
    }
}

int bfs_can_expand(NODE* node, int maxDepth)
{
    return 1;
}

int bfs_can_visit(NODE* node, int maxDepth)
{
    return 1;
}

NODE* dequeue(void* q)
{
    QUEUE* queue = (QUEUE*) q;
    NODE* temp = queue->front;

    if (queue->front == NULL)
    {
        printf("Fila vazia...");
        exit(1);
    }

    queue->front = temp->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
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

int queue_empty(void* q)
{
    QUEUE* queue = (QUEUE*) q;

    if(queue->front)
        return 0;
    return 1;
}

