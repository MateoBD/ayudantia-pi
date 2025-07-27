#include "2p-2025-1c-ej2.h"
#include <stdlib.h>

typedef struct bus_t
{
    char occupied;
    elemType info;
} bus_t;

struct busCDT
{
    bus_t * arr_bus;
    size_t size;    // cantidad real de buses
    size_t dim;     // dimensión total del arreglo
    compare_function_t cmp;
};


busADT newBusADT(compare_function_t cmp)
{
    busADT new_bus = malloc(sizeof(*new_bus));
    new_bus->arr_bus = NULL;
    new_bus->size = 0;
    new_bus->dim = 0;
    new_bus->cmp = cmp;
    return new_bus;
}

void freeBusADT(busADT adt)
{
    free(adt->arr_bus);
    free(adt);
}

// uso busNumber cómo índice del arreglo
void busSet(busADT adt, unsigned int busNumber, elemType info)
{
    // primero validamos si hay que agrandar el arreglo
    if (busNumber >= adt->dim)
    {
        adt->arr_bus = realloc(adt->arr_bus, (busNumber + 1) * sizeof(*(adt->arr_bus)));
        for (size_t i = adt->dim; i < busNumber + 1; i++)
        {
            adt->arr_bus[i].occupied = 0;   // importante siempre rellenar con ceros
        }
        adt->dim = busNumber + 1;
    }

    adt->size += !(adt->arr_bus[busNumber].occupied);   // sumo 1 si el lugar NO estaba ocupado de antes

    adt->arr_bus[busNumber].occupied = 1;
    adt->arr_bus[busNumber].info = info;
    return;
}

void busSetIfAbsent(busADT adt, unsigned int busNumber, elemType info)
{
    if (busNumber >= adt->dim || !(adt->arr_bus[busNumber].occupied))
    {
        busSet(adt, busNumber, info);
    }
    return;
}

int busInfo(const busADT adt, unsigned int busNumber, elemType * info)
{
    if (busNumber >= adt->dim || !(adt->arr_bus[busNumber].occupied))
    {
        return 0;
    }
    *info = adt->arr_bus[busNumber].info;
    return 1;
}

void removeBus(busADT adt, unsigned int busNumber)
{
    if (busNumber >= adt->dim || !(adt->arr_bus[busNumber].occupied))
    {
        return;
    }
    adt->arr_bus[busNumber].occupied = 0;
}

size_t busSize(const busADT adt)
{
    return adt->size;
}

#define CHUNK 10

int * busCodes(const busADT adt, elemType info, size_t * dim)
{
    size_t write_idx = 0;
    int * to_ret = NULL;
    for (size_t read_idx = 0; read_idx < adt->dim; read_idx++)
    {
        if (adt->arr_bus[read_idx].occupied && adt->cmp(adt->arr_bus[read_idx].info, info) == 0)
        {
            if (write_idx % CHUNK == 0)
            {
                to_ret = realloc(to_ret, (write_idx + CHUNK) * sizeof(*to_ret));
            }
            to_ret[write_idx++] = read_idx;
        }
    }
    if (write_idx == 0)
    {
        *dim = 0;
        return NULL;
    }
    to_ret = realloc(to_ret, write_idx * sizeof(*to_ret));
    *dim = write_idx;
    return to_ret;
}