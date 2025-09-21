#include <stdio.h>

#include "search-test.h"
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

    SearchStrategy bfs = { enqueue, dequeue, bfs_successors, bfs_can_expand, bfs_can_visit, queue_empty };
    SearchStrategy dfs = { push, pop, dfs_successors, dfs_can_expand, dfs_can_visit, stack_empty };
    SearchStrategy astar = { enqueue_sorted, dequeue, a_star_successors, bfs_can_expand, bfs_can_visit ,queue_empty };

    printf("Encontrando o caminho...\n\n");

    if(search_type == 2) {  // BFS
        answer = exec_search((void*)q, ht, NULL, cube, &bfs, 0);
        printf("\n\nFim da busca bfs!\n\n");
        queue_free(q);
        ht_free(ht);
    } 

    else 
    {
        // DFS
        if(search_type == 3) 
        {
            answer = loopDFS((void*)s, ht, cube, &dfs);
            printf("\n\nFim da busca dfs iterativa!\n\n");
            stack_free(s);
            ht_free(ht);
        }

        // A*
        else
        {
            answer = exec_search((void*)q, ht, lookupTb, cube, &astar, 0);
            queue_free(q);
            ht_free(ht);
        }
    }

    if(!answer)
        printf("\nNao foi encontrado um caminho. Cubo invalido.\n");
    else
    {
        show_search_result(answer, search_type, cube);
        free(answer);
    }
}

NODE* exec_search(void* ds, ht_t* ht, ht_t* lookupTB, int *cube, SearchStrategy* strategy, int maxDepth)
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
    int cont = 0;

    while(!is_solved)
    {
        if (strategy->ds_empty(ds))
            return NULL;

        // removendo o nó inicial da fila/pilha
        removed = strategy->remove(ds);

        // visitando o nó removido e sei que a raiz nao é a reposta
        if(removed->info.num != 1)
        {
            if(strategy->can_visit)
            {
                is_solved = visit_state(removed);
                cont++;
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
        {
            printf("Numero de nos visitados: %d\n", cont);
            return removed;
        }
    }
    return NULL;
}

NODE* loopDFS(void *s, ht_t* ht, int cube[], SearchStrategy* strategy)
{
    int depth = -1;
    NODE* answer;
    
    while(depth < 15)
    {
        num = 0;
        if (depth != -1) {
            ht_free(ht);
            ht = ht_create();
        }
        answer = exec_search(s, ht, NULL, cube, strategy, depth++);
        if(answer)
            return answer;
    }
    
    return NULL;
}
