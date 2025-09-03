#ifndef BIBLIOT_BFS_H_INCLUDED
#define BIBLIOT_BFS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "../funcoes cubo magico.h"
#include "hash.h"

int num = 0;
//Estrutura dos elementos da fila
typedef struct no
{
    int movimentos[20];
    int cubo_pai[24];
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

void InsereFila(FILA* f, int indice, int movimento, int vetorMovimentos[20], int cubo_pai[])
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

    novo->movimentos[indice] = movimento;
    novo->num = num++;
    if(cubo_pai)
        copia(cubo_pai, novo->cubo_pai);
    else
        cubo_pai = NULL;

   // printf("Movimento colocado = %d\n", novo->movimentos[indice]);
    novo->ultimaPos = indice;
    //printf("indice = %d\n", novo->ultimaPos);
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
    int cubo_novo[24];
    copia(cubo_pai, cubo_novo);

    movimentoDoPai = vetorMovimentos[indice - 1];

    if(indice>2)
    {
        movimentoDoVo = vetorMovimentos[indice - 2];
    }

    for(int i = 1; i<7; i++)
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

            if(podeInserir)
            {
                InsereFila(f, indice, i, vetorMovimentos, cubo_pai);
            }

    }
}

int visitaEstado(FILA* f, int cubo[])
{
    // visitando o primeiro da fila
    int ultimaPos = f->INICIO->ultimaPos;
    int movimento = f->INICIO->movimentos[ultimaPos];
    if(f->INICIO->ultimaPos > 0){
        copia(f->INICIO->cubo_pai, cubo);}
    // montando o cubo desse estado
    realiza_mov(movimento, cubo);

    // checando se está montado
    if(funcao_avaliadora(cubo))
        return 1;
    return 0;
}

/*void arrumaCubo(int cubo_inicial[24], int cubo[24], NO* primeiroDaLista)
{
    int indice = primeiroDaLista->prox->ultimaPos;
    NO* prox = primeiroDaLista->prox;

    int aux[24];
    if(indice!=0)
    {
        copia(cubo_inicial, aux);

        for(int i=1; i<indice; i++)
        {
            realiza_mov(prox->movimentos[i], aux);
        }

        copia(aux, cubo);
 /*   }


    // se nao tiver montado, preciso voltar o cubo para como estava antes
    /*if(movimento != 0)
    {
        if(movimento%2 == 0)
            realiza_mov(movimento - 1, cubo);

        else
            realiza_mov(movimento + 1, cubo);

        // vendo se preciso voltar mais uma vez
        if(indice < primeiroDaLista->prox->ultimaPos)
        {
            realiza_mov(primeiroDaLista->prox->movimentos[indice], cubo);
        }

        else if(indice > 1)
        {
            if(movimentoAnterior != primeiroDaLista->prox->movimentos[indice - 1])
            {
                if(movimentoAnterior%2 == 0)
                    realiza_mov(movimentoAnterior - 1, cubo);

                else
                    realiza_mov(movimentoAnterior + 1, cubo);

                realiza_mov(primeiroDaLista->prox->movimentos[indice - 1], cubo);
            }
        }
    }*/
//}

int encontraPosicao(NO* primeiroDaLista)
{
    int indice = primeiroDaLista->ultimaPos;
    int movimentoAnterior;

    if(primeiroDaLista->movimentos[indice] != 0)
    {
        movimentoAnterior = primeiroDaLista->movimentos[indice];

        // vendo se preciso voltar mais uma vez
        if(indice < primeiroDaLista->prox->ultimaPos)
        {
            return indice+1;
        }
        return indice;
    }

    return 1;

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
