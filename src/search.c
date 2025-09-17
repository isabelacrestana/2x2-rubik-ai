#include <stdio.h>

#include "search-test.h"
#include "stack.h"
#include "queue.h"
#include "hash-table.h"
#include "print.h"
#include "rubik-functions.h"
#include "manage_lookup_tb.h"

void run_search(int *cube, int search_type, ht_t* lookupTb) {
    QUEUE* q = queue_new();
    STACK* s = stack_new();
    NODE* answer;
    ht_t *ht;
    ht = ht_create();

    printf("Encontrando o caminho...\n\n");

    if(search_type == 2) {  // BFS
        answer = exec_search(q, s, ht, NULL, cube, 1, 0);
        printf("\n\nFim da busca bfs!\n\n");
        queue_free(q);
        ht_free(ht);
    } 

    else 
    {
        // DFS
        if(search_type == 3) 
        {
            answer = loopDFS(q, s, ht, cube);
            printf("\n\nFim da busca dfs iterativa!\n\n");
            stack_free(s);
            ht_free(ht);
        }

        // A*
        else
        {
            answer = exec_search(q, s, ht, lookupTb, cube, 2, 0);
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

NODE* exec_search(QUEUE* q, STACK* s, ht_t* ht, ht_t* lookupTB, int *cube, int bfsSearch, int maxDepth)
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
    if(bfsSearch)
        enqueue(q, gen_node(initialInfo));
    else
        push(s, gen_node(initialInfo));

    ht_set(ht, cube, 0);
    int cont = 0;

    while(!is_solved)
    {
        if (!q->front && !s->top)
            return NULL;

        // removendo o nó inicial da fila/pilha
        if(bfsSearch)
            removed = dequeue(q);
        else
            removed = pop(s);


        // visitando o nó removido e sei que a raiz nao é a reposta
        if(removed->info.num != 1)
        {
            if(bfsSearch)
            {
                is_solved = visit_state(removed);
                cont++;
            }
                
            else
            {
                if(removed->info.depth == maxDepth) 
                {
                    is_solved = visit_state(removed);
                    cont++;
                }
            }
           
        }
        // caso nao seja a resposta, gera seus sucessores
        if (!is_solved)
        {
            rmInfo = removed->info;

            // Gera sucessores usando o cubo atual
            if(bfsSearch == 1)
                bfs_successors(q, rmInfo, ht, rmInfo.cube);

            else
            {
                if(bfsSearch == 0 && removed->info.depth < maxDepth)
                    dfs_successors(s, rmInfo, ht, rmInfo.cube);
                else if(bfsSearch == 2)
                    a_star_successors(q, rmInfo, ht, rmInfo.cube, lookupTB);
            }

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

NODE* loopDFS(QUEUE *q, STACK *s, ht_t* ht, int cube[])
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

        answer = exec_search(q, s, ht, NULL, cube, 0, depth++);
        if(answer)
            return answer;
    }
    
    return NULL;
}
