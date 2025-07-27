#ifndef _2P_2025_1C_EJ3_H
#define _2P_2025_1C_EJ3_H

#include <stdint.h>

typedef struct node
{
    int head;
    struct node *tail;
} node;

typedef node *TList;

/**
 * Convierte un número entero en una lista enlazada de sus dígitos.
 * Los dígitos se almacenan en orden inverso (unidades primero).
 * 
 * @param num El número a convertir
 * @return Una lista enlazada con los dígitos del número
 */
TList toDigits(uint64_t num);

/**
 * Imprime los elementos de la lista.
 * Función auxiliar para testing.
 * 
 * @param list La lista a imprimir
 */
void printList(TList list);

/**
 * Libera la memoria ocupada por la lista enlazada.
 * 
 * @param list La lista a liberar
 */
void freeList(TList list);

#endif // _2P_2025_1C_EJ3_H
