#ifndef BIBLIOT_DFS_H_INCLUDED
#define BIBLIOT_DFS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "../funcoes cubo magico.h"
#include "filaVisitados.h"
#include "hash.h"

extern HashEntry* hash_table[TABLE_SIZE];  // cada posição é uma lista ligada

int numEstados =0;
/* Criando uma bibioteca de manipulação de pilhas em C */


// Estrutura que guarda o endereço do primeiro elemento do tipo struct NO
typedef struct pilha
{
    NO *topo;
} PILHA;

void ImprimePilha(PILHA* p);
int vetorBfs(PILHA *p, int vetorMovimentos[20]);

PILHA* CriaPilha()
{
    PILHA* p = (PILHA*) malloc(sizeof(PILHA));
    p->topo = NULL;  // aponta inicialmente para um endereço nulo
    return p;   //retorna o endereço
}

void Push(PILHA* p, int indice, int movimento, int vetorMovimentos[20], int cubo[])
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
    numEstados++;
    novo->num = numEstados;

    copia(cubo, novo->cubo);

    novo->ultimaPos = indice;
    novo->prox = p->topo;

    p->topo = novo;
}

void funcaoSucessoraDfs(PILHA* p, int indice, int vetorMovimentos[20], int cubo_pai[24], int iteration)
{
    int movimentoDoPai, movimentoDoVo, vetor[24], podeInserir, vetorM[20], returnHash;
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

        if (podeInserir) {
            // monta o cubo do filho
            copia(cubo_pai, vetor);
            realiza_mov(i, vetor);

            // converte pra CubeState
            CubeState state;
            for (int k = 0; k < 24; k++)
                state[k] = (uint8_t)vetor[k];

            // só insere se não estiver na hash
            returnHash = insert_if_not_exists(state, indice);
            if(returnHash != 0)
            {
                Push(p, indice, i, vetorMovimentos, vetor);
                if(returnHash == -1)
                    numEstados--;
            }
        }
    }
}

int visitaEstadoDfs(PILHA* p, int cubo[])
{
    // Checando se está montado
    if(funcao_avaliadora(cubo))
        return 1;

    return 0;
}

int vetorBfs(PILHA *p, int vetorMovimentos[20])
{
    NO* cubo = p->topo;
    int ultimaPosicao = cubo->ultimaPos;

    for(int i = 0; i<ultimaPosicao+1; i++)
    {
        vetorMovimentos[i] = cubo->movimentos[i];
    }

    return ultimaPosicao;
}

NO* Pop(PILHA* p)
{
    if (p->topo == NULL)
    {
        printf("Pilha Vazia...");
        exit(1);
    }

    NO* aux = p->topo;

    p->topo = p->topo->prox;
    return aux;
}

PILHA* LimpaPilha(PILHA* p)
{
    NO* aux = p -> topo;  // aux recebe o endereço do topo da pilha

    while(aux != NULL)    //loop que desaloca elemento por elemento
    {
        NO* q = aux -> prox;  //variável que guarda endereço do próx elemento
        free(aux);            //libera estrutura NO
        aux = q;              //aux recebe end do próximo elemento
    }

    //free(p);  //Libera estutura que guardava o end do topo da pilha
    return NULL;   // Pilha aponta para nulo
}

void ImprimePilha(PILHA* p)
{
    NO* aux;

    if (p == NULL)    //verificação...
    {
        printf("\nPilha vazia...");
    }

    else
    {
        for (aux = p -> topo; aux != NULL ; aux = aux -> prox)  //loop para percorrrer todos os elementos
        // condição de parada é o ponteiro ser nulo
        {
            printf("%d ", aux->num);
        }
    }

}


#endif // BIBLIOT-DFS_H_INCLUDED
