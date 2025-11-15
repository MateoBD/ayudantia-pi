#include "2r-2025-1c-ej1.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct list_node
{
    char * head;    // nombre del chofer
    struct list_node * tail;
};

typedef struct list_node * Tlist;

typedef struct bus_line
{
    Tlist dirvers;
    size_t count_drivers;
    char occupied;
} TbusLine;

struct busDriverADT 
{
    TbusLine * bus_lines;
    size_t size;
    size_t dim;
};

busDriverADT newBusDriverADT()
{
    busDriverADT new_bus_driver_adt = calloc(1, sizeof(*new_bus_driver_adt));
    return new_bus_driver_adt;
}

static void free_list_rec(Tlist list)
{
    if (list == NULL)
    {
        return;
    }
    free_list_rec(list->tail);
    free(list->head); // reservé espacio para el nombre, pues es una COPIA
    free(list);
}

void freeBusDriverADT(busDriverADT adt)
{
    for (int i = 0; i < adt->dim; i++)
    {
        if (adt->bus_lines[i].occupied)
        {
            free_list_rec(adt->bus_lines[i].dirvers);
        }
    }
    free(adt->bus_lines);
    free(adt);
}

int newBusLine(busDriverADT adt, unsigned int busLine)
{
    if (busLine >= adt->dim)
    {
        adt->bus_lines = realloc(adt->bus_lines, (busLine + 1) * sizeof(*(adt->bus_lines)));
        for (int i = adt->dim; i < busLine + 1; i++)
        {
            adt->bus_lines[i].occupied = 0;
        }
        adt->dim = busLine + 1;
    }
    int occupied = adt->bus_lines[busLine].occupied; // me guardo si estaba ocupado de antes

    adt->bus_lines[busLine].dirvers = NULL;
    adt->bus_lines[busLine].count_drivers = 0;
    adt->bus_lines[busLine].occupied = 1;

    adt->size += !occupied; // aumento si no estaba ocupado
    return !occupied;
}

int busLinesCount(const busDriverADT adt)
{
    return adt->size;
}

int driversCount(const busDriverADT adt, unsigned int busLine)
{
    if (busLine >= adt->dim || !adt->bus_lines[busLine].occupied)
    {
        return 0;
    }
    return adt->bus_lines[busLine].count_drivers;
}

#define REALLOC_BLOCK 10

char ** drivers(const busDriverADT adt, unsigned int busLine)
{
    if (busLine >= adt->dim || !adt->bus_lines[busLine].occupied)
    {
        return 0;
    }
    char ** to_return = NULL;
    int write_idx = 0;
    for (Tlist it = adt->bus_lines[busLine].dirvers; it != NULL; it = it->tail)
    {
        if (write_idx % REALLOC_BLOCK == 0)
        {
            to_return = realloc(to_return, (write_idx + REALLOC_BLOCK) * sizeof(*to_return));
        }
        // strdup() crea una COPIA del nombre
        // lo hago pues en el tester se liberan los char* de drivers
        to_return[write_idx++] = strdup(it->head);
    }
    to_return = realloc(to_return, write_idx * sizeof(*to_return));
    return to_return;
}

static Tlist add_driver_rec(Tlist list, const char * elem, char * added)
{
    int c;
    if (list == NULL || (c = strcmp(elem, list->head)) < 0)
    {
        Tlist new_node = malloc(sizeof(*new_node));

        new_node->head = strdup(elem);
        new_node->tail = list;
        *added = 1;
        return new_node;
    }
    if (c > 0) // hay que agregarlo mas tarde
    {
        list->tail = add_driver_rec(list->tail, elem, added);
    }
    return list; // si c == 0 no se agrega
}

void addDriver(busDriverADT adt, unsigned int busLine, const char * driver)
{
    if (busLine >= adt->dim || !adt->bus_lines[busLine].occupied)
    {
        return;
    }
    char added = 0;
    adt->bus_lines[busLine].dirvers = add_driver_rec(adt->bus_lines[busLine].dirvers, driver, &added);
    adt->bus_lines[busLine].count_drivers += added;
}

static Tlist remove_driver_rec(Tlist list, const char * elem, char * removed)
{
    int c;
    if (list == NULL || (c = strcmp(elem, list->head)) < 0)
    {
        *removed = 0;
        return list;
    }
    if (c == 0)
    {
        Tlist tail = list->tail;
        free(list->head);
        free(list);
        *removed = 1;
        return tail;
    }
    list->tail = remove_driver_rec(list->tail, elem, removed);
    return list;
}

void removeDriver(busDriverADT adt, unsigned int busLine, const char * driver)
{
    if (busLine >= adt->dim || !adt->bus_lines[busLine].occupied)
    {
        return;
    }
    char removed = 0;
    adt->bus_lines[busLine].dirvers = remove_driver_rec(adt->bus_lines[busLine].dirvers, driver, &removed);
    adt->bus_lines[busLine].count_drivers -= removed;
}
