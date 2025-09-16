#include <stdio.h>
#include <stdlib.h>

#include "print.h"
#include "queue.h"
#include "stack.h"
#include "rubik-functions.h"

void welcome_screen() {
    printf("\n\nPressione ENTER...");
    getchar();
    system("clear");

    printf("\n\n                     BEM VINDO AO PROGRAMA (...)\n\n\n"
           "                  Pressione ENTER para iniciar...");
    getchar();
}

void print_mov(int mov)
{
     switch(mov)
    {
        case 1:
        {
            printf("Rodar lado direito para cima\n");
            break;
        }

        case 2:
        {
            printf("Rodar lado direito para baixo\n");
            break;
        }

        case 3:
        {
            printf("Rodar base no sentido anti-horario\n");
            break;
        }

        case 4:
        {
            printf("Rodar base no sentido horario\n");
            break;
        }

        case 5:
        {
            printf("Rodar parte de tras no sentido horario\n");
            break;
        }

        case 6:
        {
            printf("Rodar parte de tras no sentido anti-horario\n");
            break;
        }


    }
}

void show_search_result(NODE* answer, int ai_type, int *cube){
    int depth = answer->depth;
    printf("profundidade final = %d\n\n", depth);
    printf("Passo a passo ate a resposta:\n");
    for(int i = 1; i<depth + 1; i++)
    {
        printf("%d. ", i);
        print_mov(answer->movs[i]);
    }

    // it means that it was a bfs search
    if(ai_type == 2)
        printf("\nNum de estados gerados = %d\n", num);

    // it means that it was a iidfs search
    else
        printf("\nNum de estados gerados = %d\n", numEstados);

    printf("\n\n                 ---Cubo embaralhado---\n\n");
    ui(cube);
    printf("\n\n\n                   ---Cubo montado---\n\n");
    ui(answer->cube);
    printf("\n\n");

}
