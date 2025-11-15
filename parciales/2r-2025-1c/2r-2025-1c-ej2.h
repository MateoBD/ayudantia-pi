#ifndef _2R_2025_1C_EJ2
#define _2R_2025_1C_EJ1

#include <stdlib.h>

typedef struct mostPopularCDT * mostPopularADT;

// Tipo de elemento a insertar
typedef char * elemType;

// Funcion de comparacion
typedef int (*compare_function_t)(elemType e1, elemType e2);

/* Retorna un nuevo conjunto de elementos genéricos. */
mostPopularADT newMostPopular(compare_function_t cmp);

/* Libera todos los recursos del TAD */ 
void freeMostPopular(mostPopularADT tad); // NO IMPLEMENTAR

/* Inserta un elemento si no está. Lo inserta al final.
** Retorna 1 si lo agregó, 0 si no.
*/
unsigned int add(mostPopularADT tad, elemType elem); // NO IMPLEMENTAR

/* Retorna la cantidad de elementos que hay en la colección */
unsigned int size(const mostPopularADT tad); // NO IMPLEMENTAR

/* Se ubica al principio del conjunto, para poder iterar sobre el mismo */
void toBegin(mostPopularADT tad);

/* Retorna 1 si hay un elemento siguiente en el iterador, 0 si no */
int hasNext(const mostPopularADT tad);

/* Retorna el siguiente elemento. Si no hay siguiente elemento, aborta */
elemType next(mostPopularADT tad);

/* Retorna 1 si el elemento está en la colección, 0 si no está
** Si el elemento estaba lo ubica al principio.
*/
int exist(mostPopularADT tad, elemType elem);


#endif // _2R_2025_1C_EJ1
