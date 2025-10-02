#include <stdio.h>
#include <stdlib.h>
#include "hash-table.h"
#include "rubik-functions.h"
#include "search_header.h"
#include "queue.h"
#include "stack.h"
#include "data.h"
#include "callback_fuctions.h"

int main()
{
    SearchStrategy bfs = { enqueue, dequeue, bfs_successors, bfs_can_expand, bfs_can_visit, queue_empty };
    EntryData d;
    FILE *file;
    QUEUE* q;
    int num;
    int solvedCube[24];
    ht_t *ht = ht_create();
    q = queue_new();

    printf("Gerando lookup table...\n");

    initSolvedCube(solvedCube);
    exec_search((void*)q,ht,NULL,solvedCube,&bfs,0, &num);

    printf("Lookup table completa.\n");

    file = fopen("lookup_tb.bin", "wb");
    if (!file) {
        perror("Erro ao abrir lookup_table.bin para escrita");
        exit(1);
    }


    for(int i = 0; i < TABLE_SIZE; i++) 
    {
        entry_t *entry = ht->entries[i];
        while(entry) {
            cp(entry->cube, d.cube);
            d.depth = entry->depth;

            fwrite(&d, sizeof(EntryData), 1, file);
            entry = entry->next;
        }
    }    

    fclose(file);
        
    ht_free(ht);
    queue_free(q);

    printf("Lookup table escrita no arquivo.\n");

    return 0;

}