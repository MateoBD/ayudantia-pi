#include "2p-2023-2c-ej3.h"
#include <stdlib.h>

size_t contarGrupos(char * str, char c)
{
    if (str[0] == '\0')
    {
        return 0;
    }
    size_t next_count = contarGrupos(str + 1, c);
    if (str[0] != c || str[1] == c)
    {
        return next_count;
    }
    return next_count + 1;
}

size_t countGroups(TList list, char c)
{
    if (list == NULL)
    {
        return 0;
    }
    if (list->tail == NULL)
    {
        return list->head == c;
    }
    size_t next_count = countGroups(list->tail, c);
    if (list->head != c || list->tail->head == c)
    {
        return next_count;
    }
    return next_count + 1;
}
