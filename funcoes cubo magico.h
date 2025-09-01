#ifndef FUNCOES_CUBO_MAGICO_H_INCLUDED
#define FUNCOES_CUBO_MAGICO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

// prototipos das funcoes

void vetorResposta(int v[24])
{
    for(int i = 0; i<24; i++)
    {
        v[i] = i+1;
    }
}

void imprime(int vetor[24])
{
    for(int i = 0; i<24; i++)
    {
        printf("%02d ", vetor[i]);
    }
}

void cld(int v[24])
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

void bld(int v[24])
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

void bsa(int v[24])
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

void bsh(int v[24])
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

void tsa(int v[24])
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

// Funcao que imprime o cubo para o jogador
void interfaceGrafica(int v[24])
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

int face_montada(int v[24], int face)
{
    for(int i = 0; i<3; i++)
    {
        if(v[i]!=v[i+1])
            return 0;
    }

    return 1;
}

int funcao_avaliadora(int v[24])
{
    for(int i=0; i<20; i+=4)
    {
        // ja retorna caso ache uma face que nao esteja montada
        if(!face_montada(v,i))
            return 0;
    }

    return 1; // cubo montado
}

void realiza_mov(int mov, int v[24])
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
            break;
        }

        case 6:
        {
            tsa(v);
            break;
        }

        case 7:
        {
            break;
        }

        case 0:
        {
            break;
        }
    }
}

#endif // FUNCOES_CUBO_MAGICO_H_INCLUDED
