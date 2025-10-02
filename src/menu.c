#include <stdio.h>
#include "menu.h"
#include "rubik-functions.h"

int first_menu()
{
    char charOpc;
    do
    {
        printf("\n\n\n\tEscolha uma das opcoes abaixo\n"
               "\t1. Usar cubo aleatorio gerado pelo programa\n"
               "\t2. Entrar com meu cubo\n\t");
        charOpc = getchar();
    } while(charOpc < '1' || charOpc > '2');

    return charOpc - '0';
}

int main_menu(int cube[])
{
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
               "                  0. Finalizar o programa\n"
               "                  ");
        charOpc = getchar();
        getchar();
    }while(charOpc<'0' || charOpc>'4');

    return charOpc - '0';
}


void run_free_mode(int cube[]) {
    int opc;
    do{
        opc = free_mode_menu(cube);
        if(opc == 0)
            return;
        apply_move(opc, cube);
    }while(!evaluete_state(cube));
}

int free_mode_menu(int cube[])
{
    int opc;
    do {
        //system("cls");
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
