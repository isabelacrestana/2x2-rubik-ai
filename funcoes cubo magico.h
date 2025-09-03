#ifndef FUNCOES_CUBO_MAGICO_H_INCLUDED
#define FUNCOES_CUBO_MAGICO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

// prototipos das funcoes
void copia(int origem[24], int destino[24]);

void vetorResposta(int v[24])
{
    //int vetor[24] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6};

    int vetor[24] = {1,4,6,1,3,1,5,6,4,5,2,3,2,4,5,2,3,6,5,6,1,2,4,3};

    //int vetor[24] = {1, 15, 5, 17, 12, 24, 13, 3, 11, 7, 21, 9, 4, 14, 6, 20, 22, 8, 19, 23, 2, 10, 18, 16};

    copia(vetor, v);

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

void tsh(int v[24])
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
    for(int i = 0; i < 24; i += 4) // cada 4 posições é uma face
    {
        if(v[i] != v[i+1] || v[i] != v[i+2] || v[i] != v[i+3])
            return 0; // face não está montada
    }

    return 1; // todas as faces montadas
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
            tsh(v);
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

void copia(int origem[24], int destino[24])
{
    for(int i = 0; i<24; i++)
    {
        destino[i] = origem[i];
    }
}

#endif // FUNCOES_CUBO_MAGICO_H_INCLUDED
