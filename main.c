#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "funcoes cubo magico.h"

void menu(int matriz[][12]);
int opcoesJogador(int v[24]);
int aleatorio(int n_min, int n_max);
int cuboInicial(int v[24]);

int main() {
    srand(time(NULL)); // Inicializa o gerador com o tempo atual

    int cubo_magico[24];
    int opc;

    // iniciando como matriz resposta so para comparar:
    vetorResposta(cubo_magico);
    printf("\n\nCubo antes de embaralhar:\n");
    interfaceGrafica(cubo_magico);

    printf("\n\nCubo depois de embaralhar\n");
    //cuboInicial(cubo_magico);
    interfaceGrafica(cubo_magico);

    printf("\n\npressione qualquer tecla...");
    getch();
    system("cls");



    printf("\n\n                     BEM VINDO AO PROGRAMA (...)\n\n\n"
           "                  Pressione qualquer tecla para iniciar...");
    getch();

    // por enquanto so temos a opcao 1
    do{
        //system("cls");
        printf("\n\n                    CUBO INICIAL\n\n");
        interfaceGrafica(cubo_magico);
        printf("\n\n"
               "                  Selecione uma das opcoes: (so opcao 1 funciona)\n"
               "                  1. Quero eu mesmo(a) montar o cubo\n"
               "                  2. Quero que a IA resolva para mim\n"
               "                  ");
        scanf("%d", &opc);
    }while(opc!=1 && opc!=2);

    if(opc == 1)
    {

        do{
            opc = opcoesJogador(cubo_magico);
            realiza_mov(opc, cubo_magico);
        }while(cubo_magico);
    }
    system("cls");

    /*if(opc == 2)
    {
        loopIA(f, v, cubo_magico);
        ultimaPosicao = CuboMontado(f, caminhoAteResposta);
        printf("Caminho ate a resposta: ");
        for(int i = 0; i<ultimaPosicao+1; i++)
        {
            printf("%d - ", caminhoAteResposta[i]);
        }
    }*/
    printf("\n\n         Voce venceu :) !\n");
    interfaceGrafica(cubo_magico);


    return 0;
}

int aleatorio(int n_min, int n_max)
{
    return rand() % (n_max - n_min + 1) + n_min;
}

// funcao que embaralha o cubo a partir da matriz resposta
int cuboInicial(int v[24])
{
//    int anterior = 0, num;
//    int mov;
//
//    matrizResposta(matriz);
//    num = aleatorio(10,15);
//
//    while(num > 0)
//    {
//        mov = aleatorio(1,3);   // dps adicionar todos os 6 movimentos (por enquanto so temos esses)
//        if(mov != anterior)
//        {
//            realiza_mov(mov, matriz);
//            if(mov > 6)
//            {
//                realiza_mov(mov-6, matriz);    // para poder embaralhar tbm com os movimentos "inversos"
//                realiza_mov(mov-6, matriz);
//                realiza_mov(mov-6, matriz);
//            }
//            anterior = num;
//            num--;
//        }
//    }
    vetorResposta(v);
}

int opcoesJogador(int v[24])
{
    int opc;
    do {
        system("cls");
        printf("\n\n                  Modo de jogo: LIVRE\n\n\n");
        printf("\n                  Cubo Atual\n");
        interfaceGrafica(v);
        printf("\n Matriz:\n");
        imprime(v);
        printf("\n\n                  Selecione uma das acoes abaixo: (apenas 3 a 5 e 13 a 16 implementadas!!)\n"
               "                  1. Rodar lado direito para cima\n"
               "                  2. Rodar lado direito para baixo\n"
               "                  3. Rodar parte base no sentido anti-horario\n"
               "                  4. Rodar parte base no sentido horario\n"
               "                  5. Rodar parte de tras no sentido horario\n"
               "                  6. Rodar parte de tras no sentido anti-horario"
               "                  7. Quero que a IA resolva para mim\n"
               "                  0. Sair\n"
               "                  ");
               scanf("%d", &opc);

    }while(opc<0 || opc>7);

    return opc;
}
