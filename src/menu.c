#include <stdio.h>
#include "menu.h"
#include "rubik-functions.h"

int main_menu(int cube[])
{
    int intOpc;
    char charOpc;

    do{
        //system("cls");
        printf("\n\n                    CUBO INICIAL\n\n");
        ui(cube);
        printf("\n\n"
               "                  Selecione uma das opcoes:\n"
               "                  1. Quero eu mesmo(a) montar o cubo\n"
               "                  2. Busca em Largura\n"
               "                  3. Busca em Profundidade Iterativa\n"
               "                  4. A*\n"
               "                  ");
        charOpc = getchar();
        getchar();
    }while(charOpc<'1' || charOpc>'4');

    return charOpc - '0';
}


void run_free_mode(int cube[]) {
    int opc;
    do{
        opc = free_mode_menu(cube);
        apply_move(opc, cube);
    }while(!evaluete_state(cube));
}

int free_mode_menu(int cube[])
{
    int opc;
    do {
        system("cls");
        printf("\n\n                  Modo de jogo: LIVRE\n\n\n");
        printf("\n                  Cubo Atual\n");
        ui(cube);
        printf("\n\n                  Selecione uma das acoes abaixo:\n"
               "                  1. Rodar lado direito para cima\n"
               "                  2. Rodar lado direito para baixo\n"
               "                  3. Rodar base no sentido anti-horario\n"
               "                  4. Rodar base no sentido horario\n"
               "                  5. Rodar parte de tras no sentido horario\n"
               "                  6. Rodar parte de tras no sentido anti-horario\n"
               "                  0. Sair\n"
               "                  ");
               scanf("%d", &opc);

    }while(opc<0 || opc>6);

    return opc;
}
