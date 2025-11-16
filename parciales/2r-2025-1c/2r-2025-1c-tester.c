#include "2r-2025-1c-ej1.h"
#include "2r-2025-1c-ej2.h"
#include "2r-2025-1c-ej3.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

static void free_list_rec(TList list)
{
    if (list == NULL)
    {
        return;
    }
    free_list_rec(list->tail);
    free(list->person);
    free(list);
}

static void print_list_rec(TList list)
{
    if (list == NULL)
    {
        printf("NULL\n");
        return;
    }
    printf("{\"%s,%d\"} -> ", list->person, list->popularity);
    print_list_rec(list->tail);
}

// funcion de comparacion para evitar un warning (usar strcmp es lo mismo)
int mystrcmp(char * s1, char * s2)
{
    return strcmp(s1, s2);
}

int main(void) {
    // ===========================================================================================
    // EJERCICIO 1
    
    busDriverADT adt = newBusDriverADT();
    assert(busLinesCount(adt) == 0); // Inicialmente no hay líneas

    // Agregamos líneas nuevas
    assert(newBusLine(adt, 60) == 1);
    assert(newBusLine(adt, 168) == 1);
    assert(newBusLine(adt, 60) == 0); // ya estaba

    assert(busLinesCount(adt) == 2);
    assert(driversCount(adt, 60) == 0);
    assert(driversCount(adt, 999) == 0); // línea inexistente
    assert(driversCount(adt, 19) == 0);  // línea inexistente

    // Agregamos choferes a la línea 60: Carlos, Ana y Bruno
    addDriver(adt, 60, "Carlos");
    char auxName[20] = "Ana";
    addDriver(adt, 60, auxName);
    strcpy(auxName, "Bruno");
    addDriver(adt, 60, auxName);
    addDriver(adt, 60, "Ana"); // repetido, no se agrega

    assert(driversCount(adt, 60) == 3);

    // Agregamos chofer a otra línea
    addDriver(adt, 168, "Diana");
    assert(driversCount(adt, 168) == 1);

    // No debería hacer nada si la línea no existe
    addDriver(adt, 9, "Pedro");
    assert(driversCount(adt, 9) == 0);

    // Verificamos orden alfabético de choferes línea 60: Ana, Bruno, Carlos
    char ** names = drivers(adt, 60);
    assert(names != NULL);
    assert(strcmp(names[0], "Ana") == 0);
    assert(strcmp(names[1], "Bruno") == 0);
    assert(strcmp(names[2], "Carlos") == 0);
    free(names[0]); free(names[1]); free(names[2]);
    free(names);

    // Verificamos choferes de línea inexistente
    assert(drivers(adt, 1234) == NULL);
    assert(drivers(adt, 15) == NULL);

    // Quitamos un chofer de la línea 60
    removeDriver(adt, 60, "Bruno");
    assert(driversCount(adt, 60) == 2);

    // Intentamos quitar chofer inexistente o en línea inexistente
    removeDriver(adt, 60, "Juan"); // no está
    removeDriver(adt, 99, "Ana");  // línea no existe

    // Verificamos choferes actuales en 60: Ana, Carlos
    names = drivers(adt, 60);
    assert(names != NULL);
    assert(strcmp(names[0], "Ana") == 0);
    assert(strcmp(names[1], "Carlos") == 0);
    free(names[0]); free(names[1]);
    free(names);

    freeBusDriverADT(adt);
    
    puts("OK! - EJ1");
    
    // ===========================================================================================
    // EJERCICIO 2

    mostPopularADT tad = newMostPopular(mystrcmp);
    assert(size(tad) == 0); // Al principio, está vacío

    // Agregamos elementos
    assert(add(tad, "perro") == 1);
    assert(add(tad, "gato") == 1);
    assert(add(tad, "loro") == 1);
    assert(add(tad, "gato") == 0); // ya estaba

    assert(size(tad) == 3);

    // Verificamos el orden: perro, gato, loro
    const char * expected1[] = {"perro", "gato", "loro"};
    toBegin(tad);
    for (int i = 0; i < 3; i++) {
        assert(hasNext(tad));
        const char * elem = next(tad);
        assert(strcmp(elem, expected1[i]) == 0);
    }
    assert(!hasNext(tad));

    // Consultamos "gato" → debe pasar al principio
    int ok = exist(tad, "gato");
    assert(ok == 1);

    // Verificamos nuevo orden: gato, perro, loro
    const char * expected2[] = {"gato", "perro", "loro"};
    toBegin(tad);
    for (int i = 0; i < 3; i++) {
        assert(hasNext(tad));
        const char * elem = next(tad);
        assert(strcmp(elem, expected2[i]) == 0);
    }
    assert(!hasNext(tad));

    // consulta de uno que no está → 0
    assert(exist(tad, "pez") == 0);

    // Consultamos "loro" → pasa al principio
    ok = exist(tad, "loro");
    assert(ok == 1);

    // Nuevo orden: loro, gato, perro
    const char * expected3[] = {"loro", "gato", "perro"};
    toBegin(tad);
    for (int i = 0; i < 3; i++) {
        assert(hasNext(tad));
        const char * elem = next(tad);
        assert(strcmp(elem, expected3[i]) == 0);
    }
    assert(!hasNext(tad));

    freeMostPopular(tad);
    
    puts("OK! - EJ2");
    
    // ===========================================================================================
    // EJERCICIO 3
    
    TList myList = NULL;                  // NULL
    print_list_rec(myList);
    myList = upPop(myList, "Cato", 5);    // {"Cato",5} -> NULL
    print_list_rec(myList);
    myList = upPop(myList, "Paco", 3);    // {"Cato",5} -> {"Paco",3} -> NULL
    print_list_rec(myList);
    myList = upPop(myList, "Mon", 4);     // {"Cato",5} -> {"Mon",4} -> {"Paco",3} -> NULL
    print_list_rec(myList);
    myList = upPop(myList, "Cato", 1);    // {"Cato",6} -> {"Mon",4} -> {"Paco",3} -> NULL
    print_list_rec(myList);
    myList = upPop(myList, "Mon", 2);     // {"Cato",6} -> {"Mon",6} -> {"Paco",3} -> NULL
    print_list_rec(myList);
    myList = upPop(myList, "Paco", 2);    // {"Cato",6} -> {"Mon",6} -> {"Paco",5} -> NULL
    print_list_rec(myList);
    myList = upPop(myList, "Paco", 2);    // {"Paco",7} -> {"Cato",6} -> {"Mon",6} -> NULL
    print_list_rec(myList);
    myList = upPop(myList, "Mon", 1);     // {"Paco",7} -> {"Mon",7} -> {"Cato",6} -> NULL
    print_list_rec(myList);

    // Se agrega otro (PACO no es lo mismo que Paco)
    myList = upPop(myList, "PACO", 7);    // {"Paco",7} -> {"Mon",7} -> {"PACO",7} -> {"Cato",6} -> NULL
    print_list_rec(myList);

    myList = upPop(myList, "Cato", 8);    // {"Cato",14} -> {"Paco",7} -> {"Mon",7} -> {"PACO",7} -> NULL
    print_list_rec(myList);

    // TODO Liberar la lista
    free_list_rec(myList);
    
    puts("OK! - EJ3");
    
    return 0;
}


