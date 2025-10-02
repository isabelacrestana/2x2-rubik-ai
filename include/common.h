#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

typedef struct nodeInfo
{
    int movs[15];
    int cube[24];
    int depth;
    int fCost;

} NODE_INFO;

typedef struct node
{
    NODE_INFO info;
    struct node *next;  //aponta para o pr�x elemento
} NODE;

NODE* gen_node(NODE_INFO info);
int check_redundance(int depth, int *movs, int mov);
void cp_movs(int source[], int target[], int depth);
int visit_state(NODE *visited);

#endif // COMMON_H_INCLUDED