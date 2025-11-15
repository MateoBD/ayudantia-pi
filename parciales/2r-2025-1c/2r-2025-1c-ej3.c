#include "2r-2025-1c-ej3.h"

#include <stdlib.h>
#include <string.h>

TList upPop(TList list, const char * person, unsigned int popularity)
{
    if (list == NULL) {
        TList new_node = malloc(sizeof(*new_node));
        new_node->person = person;
        new_node->popularity = popularity;
        new_node->tail = list;
        return new_node;
    }
    int c;
    if ((c = strcmp(person, list->person)) == 0) {
        list->popularity += popularity;
        return list;
    }

    TList aux = upPop(list->tail, person, popularity);

    if (aux->popularity > list->popularity) {
        list->tail = aux->tail;
        aux->tail = list;
        return aux;
    }
    list->tail = aux;
    return list;
}
