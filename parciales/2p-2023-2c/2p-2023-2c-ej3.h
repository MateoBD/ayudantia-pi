#ifndef _2P_2023_2C_EJ3_H
#define _2P_2023_2C_EJ3_H

#include <stdlib.h>

struct node
{
    char head;
    struct node * tail;
};

typedef struct node * TList;

size_t contarGrupos(char * str, char c);

size_t countGroups(TList list, char c);

#endif // _2P_2023_2C_EJ3_H
