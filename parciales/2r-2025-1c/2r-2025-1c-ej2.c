#include "2r-2025-1c-ej2.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct list_node
{
    elemType head;
    struct list_node * tail;
};

typedef struct list_node * Tlist;

struct mostPopularCDT {
    Tlist list;
    Tlist iterator;
    size_t size;
    compare_function_t cmp;
};

mostPopularADT newMostPopular(compare_function_t cmp)
{
    mostPopularADT tad = malloc(sizeof(struct mostPopularCDT));

    tad->list = NULL;
    tad->iterator = NULL;
    tad->size = 0;
    tad->cmp = cmp;

    return tad;
}

static void free_list_rec(Tlist list)
{
    if (list == NULL)
    {
        return;
    }
    free_list_rec(list->tail);
    free(list);
}

void freeMostPopular(mostPopularADT tad)
{
    free_list_rec(tad->list);
    free(tad);
}

static Tlist add_list_rec(Tlist list, elemType elem, char * added, compare_function_t cmp)
{
    if (list == NULL)
    {
        Tlist new_node = malloc(sizeof(*new_node));

        new_node->head = elem;
        new_node->tail = list;
        *added = 1;
        return new_node;
    }
    if (cmp(elem, list->head) != 0)
    {
        list->tail = add_list_rec(list->tail, elem, added, cmp);
    }
    return list; // si c == 0 no se agrega
}

unsigned int add(mostPopularADT tad, elemType elem)
{
    char added = 0;
    tad->list = add_list_rec(tad->list, elem, &added, tad->cmp);
    tad->size += added;
    return added;
}

unsigned int size(const mostPopularADT tad)
{
    return tad->size;
}

void toBegin(mostPopularADT tad)
{
    tad->iterator = tad->list;
}

int hasNext(const mostPopularADT tad)
{
    return tad->iterator != NULL;
}

elemType next(mostPopularADT tad)
{
    assert(hasNext(tad)); // si no hay siguiente corto ejecución

    elemType elem = tad->iterator->head;
    tad->iterator = tad->iterator->tail;
    return elem;
}

static Tlist get_node_rec(Tlist list, elemType elem, Tlist * aux, compare_function_t cmp)
{
    if (list == NULL)
    {
        *aux = NULL;
        return list;
    }
    if (cmp(elem, list->head) == 0)
    {
        *aux = list;
        return list->tail;
    }
    list->tail = get_node_rec(list->tail, elem, aux, cmp);
    return list;
}

int exist(mostPopularADT tad, elemType elem)
{
    Tlist aux = NULL;
    tad->list = get_node_rec(tad->list, elem, &aux, tad->cmp);
    if (aux == NULL)
    {
        return 0; // no existe
    }
    aux->tail = tad->list; // lo ubica al principio
    tad->list = aux;
    return 1;
}
