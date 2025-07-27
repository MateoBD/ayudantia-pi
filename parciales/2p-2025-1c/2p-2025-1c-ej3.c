#include "2p-2025-1c-ej3.h"

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

static TList newNode(uint8_t num)
{
    TList new_node = malloc(sizeof(*new_node));
    new_node->head = num;
    new_node->tail = NULL;
    return new_node;
}

TList toDigits(uint64_t num)
{
    if (num / 10 == 0)
    {
        TList new_node = newNode(num);
        return new_node;
    }

    TList list = newNode(num % 10);
    list->tail = toDigits(num / 10);
    return list;
}

// Function to print the list (for testing)
void printList(TList list)
{
    printf("Digits: ");
    while (list != NULL)
    {
        printf("%d ", list->head);
        list = list->tail;
    }
    printf("\n");
}

// Function to free the list
void freeList(TList list)
{
    while (list != NULL)
    {
        TList temp = list;
        list = list->tail;
        free(temp);
    }
}
