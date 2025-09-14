#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"
#include "print.h"
#include "search.h"
#include "rubik-functions.h"

int main() {
    srand(time(NULL)); // Inicializa o gerador com o tempo atual

    int rubik[24], initialCube[24], opc;

    vetorResposta(rubik);
    printf("\n\nCubo antes de embaralhar:\n");
    ui(rubik);

    printf("\n\nCubo depois de embaralhar\n");
    random_rubik(rubik);
    cp(rubik, initialCube);
    ui(rubik);

    welcome_screen();
    fflush(stdin);

    opc = main_menu(rubik);
    system("clear");

    if(opc == 1)
        run_free_mode(rubik);

    else 
        run_search(rubik, opc);

    printf("\n\n                 ---Cubo embaralhado---\n\n");
    ui(initialCube);
    printf("\n\n\n                   ---Cubo montado---\n\n");
    ui(rubik);
    printf("\n\n");

    return 0;
}
