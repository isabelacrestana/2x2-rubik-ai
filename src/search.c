#include <stdio.h>
#include "search.h"
#include "stack.h"
#include "queue.h"
#include "hash-table.h"
#include "print.h"
#include "rubik-functions.h"

void run_search(int cube[], int search_type) {
    QUEUE* q = queue_new();
    STACK* s = stack_new();
    NODE* answer;

    printf("Encontrando o caminho...\n\n");

    if(search_type == 2) {  // BFS
        answer = exec_search(q, s, cube, 1, 0);
        printf("\n\nFim da busca bfs!\n\n");
        queue_free(q);
    } else {  // DFS
        answer = loopDFS(q, s, cube);
        printf("\n\nFim da busca dfs iterativa!\n\n");
        stack_free(s);
    }

    if(!answer)
        printf("\nNao foi encontrado um caminho. Cubo invalido.\n");
    else
    {
        show_search_result(answer, search_type, cube);
        free(answer);
    }
}

NODE* exec_search(QUEUE* q, STACK* s, int *cube, int bfsSearch, int maxDepth)
{
    int is_solved = 0, movs[15];
    ht_t *ht = ht_create();
    NODE *removed;

    // Inserindo nó inicial
    if(bfsSearch)
        enqueue(q, 0, 0, movs, cube);
    else
        push(s, 0, 0, movs, cube);

    ht_set(ht, cube, 0);

    while(!is_solved)
    {
        if (!q->front && !s->top)
        {
            ht_free(ht);
            return NULL;
        }

        // removendo o nó inicial da fila/pilha
        if(bfsSearch)
            removed = dequeue(q);
        else
            removed = pop(s);

        // visitando o nó removido
        is_solved = visit_state(removed);
        // caso nao seja a resposta, gera seus sucessores
        if (!is_solved)
        {
            // Gera sucessores usando o cubo atual
            if(bfsSearch)
                generate_successors(q, removed->depth + 1, removed->movs, removed->cube, ht);

            else
            {
                if(removed->depth < maxDepth)
                    stack_generate_successors(s, removed->depth + 1, removed->movs, removed->cube, ht);
            }

            // desaloca o nó removido
            free(removed);
        }
        // caso esteja resolvido, retorna esse nó
        else 
        {
            ht_free(ht);
            return removed;
        }
    }
    return NULL;
}

NODE* loopDFS(QUEUE *q, STACK *s, int cube[])
{
    int depth = -1;
    ht_t *ht;
    NODE* answer;
    
    while(depth < 15)
    {
        ht = ht_create();
        answer = exec_search(q, s, cube, 0, depth++);
        if(answer)
            return answer;
    }
    
    return NULL;
}
