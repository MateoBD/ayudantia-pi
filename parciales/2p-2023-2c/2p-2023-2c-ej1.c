#include "2p-2023-2c-ej1.h"

#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

#define DAYS_MAX 366

#define IS_VALID_DAY(d) (0 < (d) && (d) <= DAYS_MAX)

struct list_node
{
    char * head;    // nombre de la persona
    struct list_node * tail;
};

typedef struct list_node * Tlist;

typedef struct tickets_day
{
    Tlist first; // cada dia contiene una lista de nombres ordenada alfabeticamente
    size_t amount_tickets;
    Tlist iterator;
} TticketsDay;

struct museumTicketCDT
{
    TticketsDay year[DAYS_MAX];
    size_t total_amount_tickets;
};


museumTicketADT newMuseumTicket(void)
{
    museumTicketADT new_museum = calloc(1, sizeof(*new_museum)); // se inicializa todo el arreglo con ceros
    return new_museum;
}

static Tlist add_ticket_rec(Tlist list, const char * elem, char * added)
{
    int c;
    if (list == NULL || (c = strcasecmp(elem, list->head)) < 0) // strcasecmp() no es case sensitive (ver ejemplos de "john")
    {
        Tlist new_node = malloc(sizeof(*new_node));

        // a continuación guardo una COPIA del nombre,
        // en este caso también sería correcto igualar punteros de esta forma:
        // new_node->head = elem;
        new_node->head = malloc((strlen(elem) + 1) * sizeof(char)); // se asume que los nombres son cortos
        strcpy(new_node->head, elem);
        new_node->tail = list;
        *added = 1;
        return new_node;
    }
    if (c > 0) // hay que agregarlo mas tarde
    {
        list->tail = add_ticket_rec(list->tail, elem, added);
    }
    return list; // si c == 0 no se agrega
}

int addTicket(museumTicketADT museumTicketADT, size_t dayOfYear, const char * visitor)
{
    if (!IS_VALID_DAY(dayOfYear))
    {
        return 0;
    }
    char added = 0;
    museumTicketADT->year[dayOfYear].first = add_ticket_rec(museumTicketADT->year[dayOfYear].first, visitor, &added);
    museumTicketADT->year[dayOfYear].amount_tickets += added;
    museumTicketADT->total_amount_tickets += added;
    return added ? museumTicketADT->year[dayOfYear].amount_tickets : 0;
}

int dayTickets(const museumTicketADT museumTicketADT, size_t dayOfYear)
{
    if (!IS_VALID_DAY(dayOfYear))
    {
        return -1;
    }
    return museumTicketADT->year[dayOfYear].amount_tickets;
}

int yearTickets(const museumTicketADT museumTicketADT)
{
    return museumTicketADT->total_amount_tickets;
}

void toBeginByDay(museumTicketADT museumTicketADT, size_t dayOfYear)
{
    if (!IS_VALID_DAY(dayOfYear))
    {
        return;
    }
    museumTicketADT->year[dayOfYear].iterator = museumTicketADT->year[dayOfYear].first;
}

size_t hasNextByDay(museumTicketADT museumTicketADT, size_t dayOfYear)
{
    if (!IS_VALID_DAY(dayOfYear))
    {
        return 0;
    }
    return (museumTicketADT->year[dayOfYear].iterator != NULL);
}

char * nextByDay(museumTicketADT museumTicketADT, size_t dayOfYear)
{
    assert(hasNextByDay(museumTicketADT, dayOfYear));
    char * to_return = museumTicketADT->year[dayOfYear].iterator->head;
    museumTicketADT->year[dayOfYear].iterator = museumTicketADT->year[dayOfYear].iterator->tail;
    return to_return;
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

void freeMuseumTicket(museumTicketADT museumTicketADT)
{
    for (int i = 0; i < DAYS_MAX; i++)
    {
        free_list_rec(museumTicketADT->year[i].first); // libero TODAS las listas
    }
    free(museumTicketADT);
}
