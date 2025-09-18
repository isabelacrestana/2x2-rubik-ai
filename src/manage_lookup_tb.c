#include <stdio.h>
#include <stdlib.h>

#include "manage_lookup_tb.h"
#include "hash-table.h"
#include "data.h"

void get_lookup_table(ht_t *ht)
{
    EntryData d;

    FILE *file = fopen("lookup_tb.bin", "rb");
    if (!file) {
        perror("Erro ao abrir lookup_table.bin");
        exit(1);
    }

    while (fread(&d, sizeof(EntryData), 1, file) == 1)    
        ht_set(ht, d.cube, d.depth);
}
