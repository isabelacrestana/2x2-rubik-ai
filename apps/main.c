#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "menu.h"
#include "print.h"
#include "search_header.h"
#include "rubik-functions.h"
#include "manage_lookup_tb.h"

int main() 
{
    srand(time(NULL)); // Inicializa o gerador com o tempo atual

    int rubik[24], initialCube[24], opc;
    ht_t *lookupTb = ht_create();
    get_lookup_table(lookupTb);

    initSolvedCube(rubik);
    //printf("\n\nCubo antes de embaralhar:\n");
    //ui(rubik);

    //printf("\n\nCubo depois de embaralhar\n");
    random_rubik(rubik);
    cp(rubik, initialCube);
    //ui(rubik);

    welcome_screen();
    fflush(stdin);

    opc = first_menu();
    if(opc == 2)
    {
        do
        {
            enter_cube(rubik);
        } while(!valid_cube(rubik));
        if(evaluete_state(rubik))
        {
            printf("Cubo solucionado\n");
            exit(0);
        }
    }
    else
        random_rubik(rubik);

    getchar();

    cp(rubik, initialCube);

    do
    {
        opc = main_menu(rubik);
        if(opc == 1)
        {
            run_free_mode(rubik);
            getchar();
        }

        else if(opc != 0) 
            run_search(rubik, opc, lookupTb);
        else
            exit(0);
    } while(opc!=0);

    ht_free(lookupTb); 

    return 0;
}
