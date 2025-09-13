#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"
#include "queue.h"
#include "menu.h"
#include "print.h"
#include "hash-table.h"
#include "search.h"
#include "rubik-functions.h"

int main() {
    srand(time(NULL)); // Inicializa o gerador com o tempo atual

    int rubik[24], inicio[24], ultimaPosicao;
    int opc;

    QUEUE* q = queue_new();
    STACK* s = stack_new();

    // iniciando como matriz resposta so para comparar:
    vetorResposta(rubik);
    printf("\n\nCubo antes de embaralhar:\n");
    ui(rubik);

    printf("\n\nCubo depois de embaralhar\n");
    ui(rubik);

    cp(rubik, inicio);

    printf("\n\nPressione ENTER...");
    getchar();   // substitui getch()
    system("clear");  // substitui system("cls")

    printf("\n\n                     BEM VINDO AO PROGRAMA (...)\n\n\n"
           "                  Pressione ENTER para iniciar...");
    getchar();   // substitui getch()

    opc = main_menu(rubik);

    if(opc == 1)
    {
        do{
            opc = free_mode_menu(rubik);
            apply_move(opc, rubik);
        }while(!evaluete_state(rubik));
    }
    system("clear");

    if(opc == 2)
    {
        bfs(rubik, q);
        printf("Fim da busca bfs!\n\n");

        if(q->INICIO)
        {
            ultimaPosicao = q->INICIO->depth;
            printf("profundidade final = %d\n\n", q->INICIO->depth);
            printf("Passo a passo ate a resposta:\n");
            for(int i = 1; i<ultimaPosicao + 1; i++)
            {
                printf("%d. ", i);
                print_mov(q->INICIO->movs[i]);
            }
            printf("\nNum de estados gerados = %d\n", num);
        }
        else
            printf("\nNum de estados gerados = %d\nNao foi encontrado um caminho. Cubo invalido.\n", num);

        queue_free(q); // estava 'f', mas a variável é 'q'
    }

    if(opc == 3)
    {
        loopDFS(rubik, s);
        printf("\n\nFim da busca dfs iterativa!\n\n");
        if(s->topo)
        {
            printf("profundidade final = %d\n\n", s->topo->depth);
            ultimaPosicao = s->topo->depth;
            printf("Passo a passo ate a resposta:\n");
            for(int i = 1; i<ultimaPosicao + 1; i++)
            {
                printf("%d. ", i);
                print_mov(s->topo->movs[i]);
            }
            printf("\n\nNum de estados gerados = %d\n", s->topo->num);
        }
        else
            printf("Num de estados gerados = %d\nNao foi encontrado um caminho. Cubo invalido.\n", numEstados);

        stack_free(s);
    }

    printf("\n\n                 ---Cubo embaralhado---\n\n");
    ui(inicio);
    printf("\n\n\n                   ---Cubo montado---\n\n");
    ui(rubik);
    printf("\n\n");

    return 0;
}
