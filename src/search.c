#include <stdio.h>

#include "search_header.h"
#include "stack.h"
#include "queue.h"
#include "hash-table.h"
#include "print.h"
#include "rubik-functions.h"
#include "manage_lookup_tb.h"
#include "callback_fuctions.h"

void run_search(int *cube, int search_type, ht_t* lookupTb) {
    QUEUE* q = queue_new();
    STACK* s = stack_new();
    NODE* answer;
    ht_t *ht;
    ht = ht_create();
    int visitedNumber = 0;

    SearchStrategy bfs = { enqueue, dequeue, bfs_successors, bfs_can_expand, bfs_can_visit, queue_empty };
    SearchStrategy dfs = { push, pop, dfs_successors, dfs_can_expand, dfs_can_visit, stack_empty };
    SearchStrategy astar = { enqueue_sorted, dequeue, a_star_successors, bfs_can_expand, bfs_can_visit ,queue_empty };

    printf("Encontrando o caminho...\n\n");

    if(search_type == 2) {  // BFS
        answer = exec_search((void*)q, ht, NULL, cube, &bfs, 0, &visitedNumber);
        printf("\n\nFim da busca bfs!\n\n");
    } 

    else 
    {
        // DFS
        if(search_type == 3) 
        {
            answer = loopDFS((void*)s, ht, cube, &dfs, &visitedNumber);
            printf("\n\nFim da busca dfs iterativa!\n\n");
        }

        // A*
        else
        {
            answer = exec_search((void*)q, ht, lookupTb, cube, &astar, 0, &visitedNumber);
            printf("\n\nFim da busca A*!\n\n");
        }
    }

    printf("Numero de estados visitados: %d \n", visitedNumber);

    if(!answer)
        printf("\nNao foi encontrado um caminho. Cubo invalido.\n");
    else
    {
        show_search_result(answer, cube);
        free(answer);
    }

    stack_free(s);
    queue_free(q);
    ht_free(ht);
}

NODE* exec_search(void* ds, ht_t* ht, ht_t* lookupTB, int *cube, SearchStrategy* strategy, int maxDepth, int *visitedNumber)
{
    int is_solved = 0;
    NODE *removed;
    NODE_INFO rmInfo, initialInfo;
    int cuboInicial[24];
    cp(cube, cuboInicial);

    cp(cube, initialInfo.cube);
    initialInfo.depth = 0;
    initialInfo.fCost = 0;

    // Inserindo nó inicial
    strategy->insert(ds, gen_node(initialInfo));

    ht_set(ht, cube, 0);

    while(!is_solved)
    {
        if (strategy->ds_empty(ds))
            return NULL;

        // removendo o nó inicial da fila/pilha
        removed = strategy->remove(ds);

        // visitando o nó removido e sei que a raiz nao é a reposta
        if(removed->info.depth != 0)
        {
            if(strategy->can_visit)
            {
                is_solved = visit_state(removed);
                (*visitedNumber)++;
            }
        }

        // caso nao seja a resposta, gera seus sucessores
        if (!is_solved)
        {
            rmInfo = removed->info;

            // Gera sucessores usando o cubo atual
            if(strategy->can_expand(removed, maxDepth))
                strategy->successor_function(ds, rmInfo, ht, rmInfo.cube, lookupTB);
                
            // desaloca o nó removido
            free(removed);
        }
        // caso esteja resolvido, retorna esse nó
        else 
            return removed;
    }
    // se chegar aqui é pq nao encontrou solucao 
    return NULL;
}

NODE* loopDFS(void *s, ht_t* ht, int cube[], SearchStrategy* strategy, int *visitedNumber)
{
    int depth = 0;
    NODE* answer;
    
    while(depth < 15)
    {
        if (depth != -1) {
            ht_free(ht);
            ht = ht_create();
        }
        answer = exec_search(s, ht, NULL, cube, strategy, ++depth, visitedNumber);
        if(answer)
            return answer;
    }
    
    return NULL;
}
