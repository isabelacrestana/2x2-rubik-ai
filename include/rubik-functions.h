#ifndef FUNCOES_CUBO_MAGICO_H_INCLUDED
#define FUNCOES_CUBO_MAGICO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>

// prototipos das funcoes
void vetorResposta(int v[]);
void imprime(int v[]);
void cld(int v[]);
void bld(int v[]);
void bsa(int v[]);
void bsh(int v[]);
void tsa(int v[]);
void tsh(int v[]);
void ui(int v[]);
int evaluete_state(int v[]);
void apply_move(int mov, int v[]);
void cp(int source[], int target[]);
int random_num(int n_min, int n_max);
void random_rubik(int v[]);


#endif // FUNCOES_CUBO_MAGICO_H_INCLUDED
