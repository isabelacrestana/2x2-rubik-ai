#include <stdio.h>
#include "print.h"

void print_mov(int mov)
{
     switch(mov)
    {
        case 1:
        {
            printf("Rodar lado direito para cima\n");
            break;
        }

        case 2:
        {
            printf("Rodar lado direito para baixo\n");
            break;
        }

        case 3:
        {
            printf("Rodar base no sentido anti-horario\n");
            break;
        }

        case 4:
        {
            printf("Rodar base no sentido horario\n");
            break;
        }

        case 5:
        {
            printf("Rodar parte de tras no sentido horario\n");
            break;
        }

        case 6:
        {
            printf("Rodar parte de tras no sentido anti-horario\n");
            break;
        }


    }
}
