#include <stdio.h>
#include "search.h"
#include "stack.h"
#include "queue.h"
#include "hash-table.h"
#include "rubik-functions.h"

void bfs(int cube[], QUEUE* q)
{
    int is_solved = 0;
    int movs[15];
    int depth;
    ht_t *ht = ht_create();

    // Inserindo nó inicial
    enqueue(q, 0, 0, movs, cube);
    ht_set(ht, cube, 0);

    printf("Encontrando o caminho...\n\n");
    do
    {
        if (!q || !q->INICIO)
            break;

        cp(q->INICIO->cube, cube);
        // Visita estado do primeiro nó da fila
        is_solved = visit_state(q->INICIO);

        if (!is_solved)
        {
            // Atualiza vetor de movimentos
            cp_movs(q->INICIO, movs);
            depth =  q->INICIO->depth + 1;

            // Remove o nó atual da fila
            dequeue(q);
            // Gera sucessores usando o cubo atual
            if(depth < 15)
                generate_successors(q, depth, movs, cube, ht);
        }
    } while (!is_solved);
}

void loopDFS(int cube[], STACK *s)
{
    int depth = -1;
    int search_cube[24];
    ht_t *ht = ht_create();

    printf("Encontrando o caminho...\n\n");

    do
    {
        ht = ht_create();
        cp(cube, search_cube);
    }while(!iidfs(depth++, s, search_cube, ht) && depth < 15);

    cp(search_cube, cube);
}

int iidfs(int max_depth, STACK* s, int cube[], ht_t *ht)
{
    int depth, movs[15], is_solved = 0;
    numEstados = 0;
    push(s, 0, 0, movs, cube);

    do
    {
        cp(s->topo->cube, cube);

        // Visita estado do primeiro nó da pilha
        if(s->topo->depth == max_depth)
            is_solved = visit_state(s->topo);

        if(is_solved)
            return 1;

        depth = s->topo->depth;

        // Atualiza vetor de movimentos
        cp_movs(s->topo, movs);

        pop(s);

        // Gera sucessores usando o cubo atual
        if(depth < max_depth)
            stack_generate_successors(s, depth+1, movs, cube, ht);

        if(!s->topo)
        {
            ht_free(ht);
            return 0;
        }
    } while (!is_solved);

    return 1;
}
