#ifndef _2P_2025_1C_EJ2
#define _2P_2025_1C_EJ1

#include <stdlib.h>

typedef struct busCDT * busADT; 

typedef int elemType;

// funció de comparación
typedef int (*compare_function_t)(elemType e1, elemType e2);

busADT newBusADT(compare_function_t cmp);

void freeBusADT(busADT adt);
/**
* Registra la información info para la línea de colectivos busNumber. * Si ya existe, se reemplaza.
*/
void busSet(busADT adt, unsigned int busNumber, elemType info);
/**
* Registra la información info para la línea de colectivos busNumber sólo si no existe. * Si ya existe, no hace nada.
*/
void busSetIfAbsent(busADT adt, unsigned int busNumber, elemType info);
/**
* Si existe una línea de colectivos con el número busNumber retorna 1 y deja en *info * una copia de la info asociada. Si no existe retorna cero y no modifica *info
*/
int busInfo(const busADT adt, unsigned int busNumber, elemType * info);
/**
* Elimina una línea de colectivos. Si no existe no hace nada */
void removeBus(busADT adt, unsigned int busNumber);
/**
* Retorna la cantidad de líneas de colectivo que se registraron */
size_t busSize(const busADT adt);
/**
* Retorna un vector con todos los números de líneas de colectivos que tienen esa info * asociada. Si no hay ningún colectivo con esa info retorna NULL y deja *dim en cero */
int * busCodes(const busADT adt, elemType info, size_t * dim);

#endif // _2P_2025_1C_EJ1
