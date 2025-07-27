#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "2p-2023-2c-ej1.h"
#include "2p-2023-2c-ej2.h"
#include "2p-2023-2c-ej3.h"

int main(void)
{
    // Reserva los recursos para administrar las ventas de tickets
    museumTicketADT museum = newMuseumTicket();

    // Se registra un ticket para que John visite el museo el día 4 del año
    // Y retorna 1 porque es la cantidad de tickets para ese día
    assert(addTicket(museum, 4, "John") == 1);
    // Los siguientes fallan porque John ya cuenta con un ticket para el día 4 del año
    assert(addTicket(museum, 4, "John") == 0);
    assert(addTicket(museum, 4, "JOHN") == 0);
    assert(addTicket(museum, 4, "john") == 0);

    // Se registra un ticket para que John visite el museo el día 360 del año
    assert(addTicket(museum, 360, "John") == 1);

    // Falla porque el día del año es igual a 0
    assert(addTicket(museum, 0, "Katherine") == 0);
    // Falla porque el día del año es mayor a 366
    assert(addTicket(museum, 367, "Katherine") == 0);

    // Se registra un ticket para que Paul visite el museo el día 4 del año
    // Y retorna 2 porque es la cantidad de tickets para ese día
    assert(addTicket(museum, 4, "Paul") == 2);
    assert(addTicket(museum, 4, "Ariel") == 3);

    assert(addTicket(museum, 360, "Brenda") == 2);

    // Se inicializa el iterador para el día 4 del año
    toBeginByDay(museum, 4);
    // Quedan visitantes por recorrer para el día 4 del año
    assert(hasNextByDay(museum, 4) == 1);
    // Se obtiene el primer visitante para el día 4 del año en orden alfabético

    
    assert(strcmp(nextByDay(museum, 4), "Ariel") == 0);

    toBeginByDay(museum, 360);
    // Se obtiene el primer visitante para el día 360 del año en orden alfabético
    assert(hasNextByDay(museum, 360) == 1);
    assert(strcmp(nextByDay(museum, 360), "Brenda") == 0);

    assert(hasNextByDay(museum, 4) == 1);
    // Se obtiene el segundo visitante para el día 4 del año en orden alfabético
    assert(strcmp(nextByDay(museum, 4), "John") == 0);
    assert(hasNextByDay(museum, 360) == 1);
    // Se obtiene el segundo visitante para el día 360 del año en orden alfabético
    assert(strcmp(nextByDay(museum, 360), "John") == 0);

    assert(hasNextByDay(museum, 4) == 1);
    assert(strcmp(nextByDay(museum, 4), "Paul") == 0);
    // No quedan más visitantes por recorrer para el día 4 del año
    assert(hasNextByDay(museum, 4) == 0);
    // No quedan más visitantes por recorrer para el día 360 del año
    assert(hasNextByDay(museum, 360) == 0);

    // Se obtiene la cantidad de tickets para el día 4 del año
    assert(dayTickets(museum, 4) == 3);
    assert(dayTickets(museum, 360) == 2);
    assert(dayTickets(museum, 15) == 0);

    // Se obtiene la cantidad total de tickets (todos los días del año)
    assert(yearTickets(museum) == 5);

    // Libera los recursos utilizados para administrar las ventas de tickets
    freeMuseumTicket(museum);

    puts("OK! - EJ1");

    // ===========================================================================================

    landmarkADT lm = newLandmark((compare_function_t) strcmp);

    assert(landmarkCount(lm)==0);

    landmarkType * v = landmarks(lm);
    assert(v==NULL);

    size_t dim;
    v = landmarksBetween(lm, 0, 300, &dim);
    assert(v==NULL && dim==0);

    addLandmark(lm, 50, "Atalaya");
    addLandmark(lm, 70, "YPF abandonada");
    addLandmark(lm, 99, "El estadio del Chelsea");
    assert(landmarkCount(lm)==1);

    addLandmark(lm, 650, "Restos de un OVNI");

    addLandmark(lm, 350, "Pulpería de 1800");

    addLandmark(lm, 200, "Otra pulpería");

    v = landmarksBetween(lm, 0, 299, &dim);
    assert(dim==2);
    assert(strcmp(v[0], "El estadio del Chelsea")==0);
    assert(strcmp(v[1], "Otra pulpería")==0);
    free(v);

    v = landmarksBetween(lm, 100, 199, &dim);
    assert(v==NULL && dim==0);

    // El siguiente ciclo imprime:
    //   El estadio del Chelsea
    //   Otra pulpería
    //   Pulpería de 1800
    //   Restos de un OVNI
    v = landmarks(lm);
    for(int i=0; i < landmarkCount(lm); i++) {
        puts(v[i]);
    }
    free(v);

    assert(distance(lm, "Atalaya")==-1);
    assert(distance(lm, "El estadio del Chelsea")==0);
    assert(distance(lm, "Restos de un OVNI")==600);

    for(int i=600; i<=699; i++)
        assert(hasLandmark(lm, i));

    for(int i=0; i<99; i++)
        assert(hasLandmark(lm, i));

    for(int i=100; i<=199; i++)
        assert(!hasLandmark(lm, i));

    freeLandmark(lm);

    puts("OK! - Ej2");

    // ===========================================================================================

    // Test para contarGrupos con strings
    assert(contarGrupos("", 'a') == 0);
    assert(contarGrupos("a", 'a') == 1);
    assert(contarGrupos("aa", 'a') == 1);
    assert(contarGrupos("aaa", 'a') == 1);
    assert(contarGrupos("aba", 'a') == 2);
    assert(contarGrupos("abaa", 'a') == 2);
    assert(contarGrupos("aabaa", 'a') == 2);
    assert(contarGrupos("hello", 'l') == 1);
    assert(contarGrupos("helloworld", 'l') == 2);
    assert(contarGrupos("xyz", 'a') == 0);

    // Test para countGroups con listas
    TList emptyList = NULL;
    assert(countGroups(emptyList, 'a') == 0);

    // Lista con un solo elemento
    TList oneElement = malloc(sizeof(struct node));
    oneElement->head = 'a';
    oneElement->tail = NULL;
    assert(countGroups(oneElement, 'a') == 1);
    assert(countGroups(oneElement, 'b') == 0);

    // Lista: a->b->a
    TList list1 = malloc(sizeof(struct node));
    list1->head = 'a';
    list1->tail = malloc(sizeof(struct node));
    list1->tail->head = 'b';
    list1->tail->tail = malloc(sizeof(struct node));
    list1->tail->tail->head = 'a';
    list1->tail->tail->tail = NULL;
    assert(countGroups(list1, 'a') == 2);

    // Lista: a->a->b->a->a
    TList list2 = malloc(sizeof(struct node));
    list2->head = 'a';
    list2->tail = malloc(sizeof(struct node));
    list2->tail->head = 'a';
    list2->tail->tail = malloc(sizeof(struct node));
    list2->tail->tail->head = 'b';
    list2->tail->tail->tail = malloc(sizeof(struct node));
    list2->tail->tail->tail->head = 'a';
    list2->tail->tail->tail->tail = malloc(sizeof(struct node));
    list2->tail->tail->tail->tail->head = 'a';
    list2->tail->tail->tail->tail->tail = NULL;
    assert(countGroups(list2, 'a') == 2);

    // Liberamos memoria
    free(oneElement);
    free(list1->tail->tail);
    free(list1->tail);
    free(list1);
    free(list2->tail->tail->tail->tail);
    free(list2->tail->tail->tail);
    free(list2->tail->tail);
    free(list2->tail);
    free(list2);

    puts("OK! - Ej3");

    return 0;
}
