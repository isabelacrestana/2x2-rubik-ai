#ifndef FILAVISITADOS_H_INCLUDED
#define FILAVISITADOS_H_INCLUDED
#include "../funcoes cubo magico.h"
#include "bibliot-bfs.h"

//Estrutura dos elementos da fila
typedef struct estado
{
    int vet[24];
    struct estado *prox;  //aponta para o próx elemento
} ESTADO;

typedef struct Visitados
{
    ESTADO *INICIO;
    ESTADO *FIM;
} VISITADOS;

VISITADOS* CriaVisitados()
{
    VISITADOS *v;
    v = (VISITADOS*) malloc(sizeof(VISITADOS));
    v -> INICIO = NULL;
    v -> FIM = NULL;
    return v;
}

int comparaVetor(int v1[], int v2[]);

ESTADO* InsereVisitados(VISITADOS* v, int vet[])
{
    ESTADO* novo;
    novo = (ESTADO*) malloc(sizeof(ESTADO));

    copia(vet, novo->vet);

    novo->prox = NULL;

    if (!(v->INICIO == NULL))
        v->FIM->prox = novo;
    v->FIM = novo;

    if (v->INICIO == NULL)
        v->INICIO = v->FIM;

    return novo;
}

void RemoveVisitados(VISITADOS* v)
{
    ESTADO* aux = v -> INICIO;

    if (v -> INICIO == NULL)
    {
        printf("Fila vazia...");
        exit(1);
    }

    aux = aux -> prox;
    free(v->INICIO);
    v->INICIO = aux;

    if (aux == NULL)
    {
        v->FIM = NULL;
    }
}

void ImprimeVisitados(VISITADOS* v)
{
    ESTADO* aux;

    if (!(v -> INICIO))
        printf("Fila vazia!!");

    else
    {
        aux = v -> INICIO;

        while (aux)
        {
            //printf("%d ", aux -> valor);
            aux = aux -> prox;
        }
    }
}

VISITADOS* LimpaVisitados(VISITADOS* v)
{
    ESTADO* recebida = v->INICIO;
    ESTADO* aux = recebida;

    while (recebida)
    {
        aux = aux->prox;
        free(recebida);
        recebida = aux;
    }

    free(v);
    return NULL;
}

int comparaVetor(int v1[], int v2[])
{
    for(int i = 0; i<24; i++)
    {
        if(v1[i] != v2[i])
            return 0;
    }

    return 1;
}

int buscaVisitados(VISITADOS* v, int vet[24])
{
    ESTADO* aux;

    if (!(v->INICIO))
        printf("Fila vazia!!");

    else
    {
        aux = v -> INICIO;

        while (aux)
        {
            if(comparaVetor(aux->vet, vet))
                return 1;
            aux = aux -> prox;
        }
    }
    return 0;
}

#endif // FILAVISITADOS_H_INCLUDED
