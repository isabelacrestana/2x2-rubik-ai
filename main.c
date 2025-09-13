#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "funcoes cubo magico.h"
#include "bibliotecas-buscas/bibliot-bfs.h"
#include "bibliotecas-buscas/filaVisitados.h"
#include "bibliotecas-buscas/bibliot-dfs.h"
#include "bibliotecas-buscas/newHash.h"

void bfs(int cubo[24], FILA* f);
void loopDFS(int cubo[24], PILHA *p);
int iidfs(int max, PILHA* p, int cubo[], ht_t *ht);

void menu(int matriz[][12]);
int opcoesJogador(int v[24]);
int aleatorio(int n_min, int n_max);
int cuboInicial(int v[24]);

int main() {
    srand(time(NULL)); // Inicializa o gerador com o tempo atual

    int cubo_magico[24], inicio[24], caminhoAteResposta[20], ultimaPosicao;
    int opc;

    FILA* f = CriaFila();
    PILHA* p = CriaPilha();

    // iniciando como matriz resposta so para comparar:
    vetorResposta(cubo_magico);
    printf("\n\nCubo antes de embaralhar:\n");
    interfaceGrafica(cubo_magico);

    printf("\n\nCubo depois de embaralhar\n");
   // realiza_mov(4, cubo_magico);
     //   realiza_mov(1, cubo_magico);
      //  realiza_mov(5, cubo_magico);
    //cuboInicial(cubo_magico);
    interfaceGrafica(cubo_magico);

    copia(cubo_magico, inicio);

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
               "                  Selecione uma das opcoes:\n"
               "                  1. Quero eu mesmo(a) montar o cubo\n"
               "                  2. Busca em Largura\n"
               "                  3. Busca em Profundidade Iterativa\n"
               "                  ");
        scanf("%d", &opc);
    }while(opc<1 && opc>3);

    if(opc == 1)
    {

        do{
            opc = opcoesJogador(cubo_magico);
            realiza_mov(opc, cubo_magico);
        }while(cubo_magico);
    }
    system("cls");

    if(opc == 2)
    {
        bfs(cubo_magico, f);
        printf("Fim da busca bfs!\n\n");

        if(f->INICIO)
        {
            ultimaPosicao = f->INICIO->ultimaPos;
            printf("profundidade final = %d\n\n", f->INICIO->ultimaPos);
            printf("Passo a passo ate a resposta:\n");
            for(int i = 1; i<ultimaPosicao + 1; i++)
            {
                printf("%d. ", i);
                printMovimentos(f->INICIO->movimentos[i]);
            }
            printf("\nNum de estados gerados = %d\n", num);
        }

        else
            printf("\nNum de estados gerados = %d\nNao foi encontrado um caminho. Cubo invalido.\n", num);

        LimpaFila(f);
    }

    if(opc == 3)
    {
        loopDFS(cubo_magico, p);
        printf("\n\nFim da busca dfs iterativa!\n\n");
        if(p->topo)
        {
            printf("profundidade final = %d\n\n", p->topo->ultimaPos);
            ultimaPosicao = p->topo->ultimaPos;
            printf("Passo a passo ate a resposta:\n");
            for(int i = 1; i<ultimaPosicao + 1; i++)
            {
                printf("%d. ", i);
                printMovimentos(p->topo->movimentos[i]);
            }
            printf("\n\nNum de estados gerados = %d\n", p->topo->num);
        }
        else
            printf("Num de estados gerados = %d\nNao foi encontrado um caminho. Cubo invalido.\n", numEstados);
        LimpaPilha(p);
    }

    printf("\n\n                 ---Cubo embaralhado---\n\n");
    interfaceGrafica(inicio);
    printf("\n\n\n                   ---Cubo montado---\n\n");
    interfaceGrafica(cubo_magico);
    printf("\n\n");

    return 0;
}

int aleatorio(int n_min, int n_max)
{
    return rand() % (n_max - n_min + 1) + n_min;
}

// funcao que embaralha o cubo a partir da matriz resposta
int cuboInicial(int v[24])
{
    int anterior = 0, num;
    int mov;
    vetorResposta(v);
    num = aleatorio(12,12);

    while(num > 0)
    {
        mov = aleatorio(1,6);   // dps adicionar todos os 6 movimentos (por enquanto so temos esses)
        if(mov != anterior)
        {
           realiza_mov(mov, v);
           anterior = num;
           num--;
        }
    }
}

int opcoesJogador(int v[24])
{
    int opc;
    do {
        system("cls");
        printf("\n\n                  Modo de jogo: LIVRE\n\n\n");
        printf("\n                  Cubo Atual\n");
        interfaceGrafica(v);
        //printf("\n Matriz:\n");
        //imprime(v);
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

void bfs(int cubo[24], FILA* f)
{
    int montado=0;
    int vetorMovimentos[20];
    int posicao;
    ht_t *ht = ht_create();

    // Inserindo nó inicial
    InsereFila(f, 0, 0, vetorMovimentos, cubo);
    ht_set(ht, cubo, 0);

    printf("Encontrando o caminho...\n\n");
    do
    {
        if (!f || !f->INICIO)
            break;

        copia(f->INICIO->cubo, cubo);
        // Visita estado do primeiro nó da fila
        montado = visitaEstado(f, cubo);

        if (!montado)
        {
            // Atualiza vetor de movimentos
            vetor(f, vetorMovimentos);
            posicao =  f->INICIO->ultimaPos + 1;

            // Remove o nó atual da fila
            RemoveFila(f);
            // Gera sucessores usando o cubo atual
            if(posicao < 15)
                funcaoSucessora(f, posicao, vetorMovimentos, cubo, ht);
        }
    } while (!montado);
}

void loopDFS(int cubo[], PILHA *p)
{
    int profund = -1;
    int vetorMovimentos[20];
    int cubo_busca[24];
    ht_t *ht = ht_create();

    printf("Encontrando o caminho...\n\n");

    do
    {
        ht = ht_create();
        copia(cubo, cubo_busca);
    }while(!iidfs(profund++, p, cubo_busca, ht) && profund < 15);

    copia(cubo_busca, cubo);
}

int iidfs(int max, PILHA* p, int cubo[], ht_t *ht)
{
    int posicao, vetorMovimentos[20], montado = 0;
    numEstados = 0;
    Push(p, 0, 0, vetorMovimentos, cubo);

    do
    {
        copia(p->topo->cubo, cubo);

        // Visita estado do primeiro nó da pilha
        if(p->topo->ultimaPos == max)
            montado = visitaEstadoDfs(p, cubo);

        if(montado)
            return 1;

        posicao = p->topo->ultimaPos;

        // Atualiza vetor de movimentos
        vetorBfs(p, vetorMovimentos);

        Pop(p);

        // Gera sucessores usando o cubo atual
        if(posicao < max)
            funcaoSucessoraDfs(p, posicao + 1, vetorMovimentos, cubo, max, ht);

        if(!p->topo)
        {
            ht_free(ht);
            return 0;
        }
    } while (!montado);
}
