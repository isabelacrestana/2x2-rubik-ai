#include <stdio.h>
#include <stdlib.h>
#include "rubik-functions.h"

void initSolvedCube(int v[])
{
    // 1: BRANCO
    // 2: VERMELHO
    // 3: AMARELO
    // 4: LARANJA
    // 5: AZUL
    // 6: VERDE
    int vetor[24] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6};
    cp(vetor, v);
}


void imprime(int vetor[])
{
    for(int i = 0; i<24; i++)
    {
        printf("%02d ", vetor[i]);
    }
}

void cld(int v[])
{
    int aux,aux2;

    aux = v[1];
    v[1] = v[21];
    aux2 = v[17];
    v[17] = aux;
    aux = v[10];
    v[10] = aux2;
    v[21] = aux;

    aux = v[3];
    v[3] = v[23];
    aux2 = v[19];
    v[19] = aux;

    aux = v[8];
    v[8] = aux2;
    v[23] = aux;

    aux = v[4];
    v[4] = v[6];
    aux2 = v[5];
    v[5] = aux;
    aux = v[7];
    v[7] = aux2;
    v[6] = aux;
}

void bld(int v[])
{
    int aux1, aux2, aux3, aux4;

    aux1 = v[4];
    aux2 = v[5];
    aux3 = v[6];
    aux4 = v[7];

    v[4] = aux2;
    v[5] = aux4;
    v[6] = aux1;
    v[7] = aux3;

    aux1 = v[1];
    aux2 = v[3];
    v[1] = v[17];
    v[3] = v[19];

    aux3 = v[21];
    aux4 = v[23];
    v[21] = aux1;
    v[23] = aux2;

    aux1 = v[8];
    aux2 = v[10];
    v[8] = aux4;
    v[10] = aux3;
    v[17] = aux2;
    v[19] = aux1;
}

void bsa(int v[])
{
    int aux1, aux2, aux3, aux4;

    aux1 = v[20];
    aux2 = v[21];
    aux3 = v[22];
    aux4 = v[23];

    v[20] = aux3;
    v[21] = aux1;
    v[22] = aux4;
    v[23] = aux2;

    aux1 = v[2];
    aux2 = v[3];
    v[2] = v[14];
    v[3] = v[15];

    aux3 = v[6];
    aux4 = v[7];

    v[6] = aux1;
    v[7] = aux2;

    aux1 = v[10];
    aux2 = v[11];
    v[10] = aux3;
    v[11] = aux4;
    v[14] = aux1;
    v[15] = aux2;
}

void bsh(int v[])
{
    int aux1, aux2, aux3, aux4;

    aux1 = v[20];
    aux2 = v[21];
    aux3 = v[22];
    aux4 = v[23];

    v[20] = aux2;
    v[21] = aux4;
    v[22] = aux1;
    v[23] = aux3;

    aux1 = v[2];
    aux2 = v[3];
    v[2] = v[6];
    v[3] = v[7];

    aux3 = v[14];
    aux4 = v[15];
    v[14] = aux1;
    v[15] = aux2;

    aux1 = v[10];
    aux2 = v[11];
    v[10] = aux3;
    v[11] = aux4;

    v[6] = aux1;
    v[7] = aux2;
}

void tsa(int v[])
{
    int aux1, aux2, aux3, aux4;
    aux1 = v[8];
    aux2 = v[9];
    aux3 = v[10];
    aux4 = v[11];

    v[8] = aux3;
    v[9] = aux1;
    v[10] = aux4;
    v[11] = aux2;

    aux1 = v[22];
    aux2 = v[23];
    v[22] = v[12];
    v[23] = v[14];
    aux3 = v[5];
    aux4 = v[7];
    v[5] = aux2;
    v[7] = aux1;
    aux1 = v[16];
    aux2 = v[17];
    v[16] = aux3;
    v[17] = aux4;
    v[12] = aux2;
    v[14] = aux1;
}

void tsh(int v[])
{
    int aux1,aux2,aux3,aux4;
    aux1 = v[8];
    aux2 = v[9];
    aux3 = v[10];
    aux4 = v[11];
    v[8] = aux2;
    v[9] = aux4;
    v[10] = aux1;
    v[11] = aux3;
    aux1 = v[22];
    aux2 = v[23];
    v[22] = v[7];
    v[23] = v[5];
    aux3 = v[12];
    aux4 = v[14];
    v[12] = aux1;
    v[14] = aux2;
    aux1 = v[16];
    aux2 = v[17];
    v[16] = aux4;
    v[17] = aux3;
    v[5] = aux1;
    v[7] = aux2;

}

// Funcao que imprime o cubo para o jogador
void ui(int v[])
{
    printf("                        +---------+ \n"
           "                       / %02d   %02d / |\n"
           "                      /         /%02d|\n"
           "                     / %02d   %02d /   |\n"
           "                    +---------+ %02d |\n"
           "                    | %02d   %02d |  %02d|\n"
           "                    |         |   /\n"
           "                    | %02d   %02d |%02d/\n"
           "                    +---------+ /\n",
           v[16], v[17],
           v[5], v[18],
           v[19], v[4],
           v[0], v[1],
           v[7], v[2],
           v[3], v[6]);
}

int evaluete_state(int v[])
{
    for(int i = 0; i < 24; i += 4) // cada 4 posições é uma face
    {
        if(v[i] != v[i+1] || v[i] != v[i+2] || v[i] != v[i+3])
            return 0; // face não está montada
    }

    return 1; // todas as faces montadas
}

void apply_move(int mov, int v[])
{
    switch(mov)
    {
        case 1:
        {
            cld(v);
            break;
        }

        case 2:
        {
            bld(v);
            break;
        }

        case 3:
        {
            bsa(v);
            break;
        }

        case 4:
        {
            bsh(v);
            break;
        }

        case 5:
        {
            tsh(v);
            break;
        }

        case 6:
        {
            tsa(v);
            break;
        }

        case 0:
        {
            printf("Saindo do programa...\n");
            exit(1);
        }
    }
}

void cp(int source[], int target[])
{
    for(int i = 0; i<24; i++)
    {
        target[i] = source[i];
    }
}

int random_num(int n_min, int n_max)
{
    return rand() % (n_max - n_min + 1) + n_min;
}

// funcao que embaralha o cubo a partir da matriz resposta
void random_rubik(int v[])
{
    int previous = 0, num;
    int mov;
    initSolvedCube(v);
    num = random_num(12,12);

    while(num > 0)
    {
        mov = random_num(1,6);   // dps adicionar todos os 6 movimentos (por enquanto so temos esses)
        if(mov != previous)
        {
           apply_move(mov, v);
           previous = num;
           num--;
        }
    }
}

void enter_cube(int cube[])
{

    for(int i = 0; i<6; i++)
    {
        printf("\n\n\tCores\n"
            "\t1: BRANCO\n"
            "\t2: VERMELHO\n"
            "\t3: AMARELO\n"
            "\t4: LARANJA\n"
            "\t5: AZUL\n"
            "\t6: VERDE\n\n");

        printf("\tFACE ");
        switch(i)
        {
            case 0:
            {
                printf("DA FRENTE:\n");
                break;
            }
            case 1:
            {
                printf("DA DIREITA:\n");
                break;
            }
            case 2:
            {
                printf("DE TRAS:\n");
                break;
            }
            case 3:
            {
                printf("DA ESQUERDA:\n");
                break;
            }
            case 4:
            {
                printf("DE CIMA:\n");
                break;
            }
            case 5:
            {
                printf("DE BAIXO:\n");
                break;
            }
        }
    
        for(int j = 0; j<4; j++)
        {
            printf("\tCor posicao %d: \t", j+1);
            do
            {
                scanf("%d", &cube[4*i + j]);
            }while(cube[4*i + j] < 1 || cube[4*i + j] > 6);
        }

        printf("\t-------------------\n");
    }
}

int valid_cube(int cube[])
{
    int num[6] = {0,0,0,0,0,0};

    for(int i = 0; i < 24; i++)
    {
        num[cube[i] - 1]++;
        if(num[cube[i] - 1] > 4)
        {
            printf("\tCubo invalido\n");
            printf("\tEntre com o cubo novamente\n");
            return 0;
        }
    }

    return 1;
}