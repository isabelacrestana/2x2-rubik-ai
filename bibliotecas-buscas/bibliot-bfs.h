#ifndef BIBLIOT_BFS_H_INCLUDED
#define BIBLIOT_BFS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "../funcoes cubo magico.h"
#include "filaVisitados.h"
#include "hash.h"

int num = 0;
//Estrutura dos elementos da fila
typedef struct no
{
    int movimentos[20];
    int cubo[24];
    int ultimaPos;
    int num;
    struct no *prox;  //aponta para o próx elemento
} NO;

typedef struct Fila
{
    NO *INICIO;
    NO *FIM;
} FILA;

FILA* LimpaFila(FILA* f);

FILA* CriaFila()
{
    FILA *f;
    f = (FILA*) malloc(sizeof(FILA));
    f -> INICIO = NULL;
    f -> FIM = NULL;
    return f;
}

void InsereFila(FILA* f, int indice, int movimento, int vetorMovimentos[20], int cubo[])
{
    NO* novo;
    novo = (NO*) malloc(sizeof(NO));

    if(indice>0)
    {
        for(int i = 0; i<indice; i++)
        {
            novo->movimentos[i] = vetorMovimentos[i];
        }
    }

    num++;

    novo->movimentos[indice] = movimento;
    novo->num = num;

    copia(cubo, novo->cubo);

    novo->ultimaPos = indice;
    novo->prox = NULL;

    if (!(f->INICIO == NULL))
        f->FIM->prox = novo;
    f->FIM = novo;

    if (f->INICIO == NULL)
        f->INICIO = f->FIM;
}

void funcaoSucessora(FILA* f, int indice, int vetorMovimentos[20], int cubo_pai[24])
{
    int movimentoDoPai, movimentoDoVo, vetor[24], podeInserir;
    movimentoDoPai = vetorMovimentos[indice - 1];

    if(indice>2)
    {
        movimentoDoVo = vetorMovimentos[indice - 2];
    }

    for(int i = 6; i>0; i--)
    {
        //printf("movimento inserido = %d\n", f->FIM->movimentos[indice]);
        podeInserir = 1;
        if(indice>2)
        {
            if(movimentoDoVo == movimentoDoPai && movimentoDoPai == i)
            {
                podeInserir = 0;
            }
        }

        if(movimentoDoPai%2 == 0)
        {
            // garantindo que nao eh o mov contrario
            if(i == movimentoDoPai-1)
                podeInserir = 0;
        }

        else
        {
            // garantindo que nao eh o mov contrario
            if(i == movimentoDoPai + 1)
                podeInserir = 0;
        }

        if (podeInserir) {
        // monta o cubo do filho
        copia(cubo_pai, vetor);
        realiza_mov(i, vetor);

        // converte pra CubeState
        CubeState state;
        for (int k = 0; k < 24; k++)
            state[k] = (uint8_t)vetor[k];

        // só insere se não estiver na hash
        if (insert_if_not_exists(state, indice)) {
            InsereFila(f, indice, i, vetorMovimentos, vetor);
        }
    }

    }
}

int visitaEstado(FILA* f, int cubo[])
{
    // Checando se está montado
    if(funcao_avaliadora(cubo))
        return 1;

    return 0;
}

int vetor(FILA *f, int vetorMovimentos[20])
{
    NO* cubo = f->INICIO;
    int ultimaPosicao = cubo->ultimaPos;

    for(int i = 0; i<ultimaPosicao+1; i++)
    {
        vetorMovimentos[i] = cubo->movimentos[i];
    }

    return ultimaPosicao;
}

int CuboMontado(FILA *f, int vetorMovimentos[20])
{
    int ultimaPosicao = vetor(f, vetorMovimentos);
    f = LimpaFila(f);
    return ultimaPosicao;
}

void RemoveFila(FILA* f)
{
    int num;
    NO* aux = f -> INICIO;

    if (f -> INICIO == NULL)
    {
        printf("Fila vazia...");
        exit(1);
    }

    aux = aux -> prox;
    free(f->INICIO);
    f->INICIO = aux;

    if (aux == NULL)
    {
        f->FIM = NULL;
    }
}

void ImprimeFila(FILA* f)
{
    NO* aux;

    if (!(f -> INICIO))
        printf("Fila vazia!!");

    else
    {
        aux = f -> INICIO;

        while (aux)
        {
            //printf("%d ", aux -> valor);
            aux = aux -> prox;
        }
    }
}

FILA* LimpaFila(FILA* f)
{
    NO* recebida = f->INICIO;
    NO* aux = recebida;

    while (recebida)
    {
        aux = aux->prox;
        free(recebida);
        recebida = aux;
    }

    free(f);
    return NULL;
}



#endif // BIBLIOT_BFS_H_INCLUDED
