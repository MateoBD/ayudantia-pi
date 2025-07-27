#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "2p-2025-1c-ej1.h"
#include "2p-2025-1c-ej2.h"
#include "2p-2025-1c-ej3.h"

int cmp_int(int a, int b)
{
    return a - b;
}

int main(void) {
    coursesADT course = newCourses();
    // No es válida la carrera '2', sólo letras
    assert(addCourse(course, '2', 10, "Economia", 90)==0);
    assert(students(course, 's')==0); // Aún no hay cursos para la carrera 'S'
    assert(students(course, 'S')==0);
    assert(students(course, '*')==0); // carrera inválida

    // Dos materias con el mismo nombre pero distinto código
    assert(addCourse(course, 'S', 10, "Economia", 90)==1);
    assert(addCourse(course, 'S', 5, "Economia", 20)==1);
    assert(students(course, 's')==110);

    // Ya existe "Economia" con el código 10
    assert(addCourse(course, 'S', 10, "Economia", 20)==0);
    // "Economia" con código 10 pero para otra carrera, es válido
    assert(addCourse(course, 'X', 10, "Economia", 90)==1);

    // Si bien no debería pasar que tenga el mismo código que "Economia",
    // el TAD no lo valida
    assert(addCourse(course, 's', 10, "Programacion Imperativa", 40)==1);
    assert(students(course, 'S')==150);

    char s[100] = "Optativa 1";
    assert(addCourse(course, 'S', 400, s, 0)==1); // Agregamos "Optativa 1", sin alumnos
    strcpy(s, "Optativa regalada"); // No afecta
    assert(addCourse(course, 'S', 110, s, 120)==1);

    toBeginByDegree(course, 'S');
    struct courseData aux;
    assert(nextCourse(course, 'S', &aux)==1);
    assert(aux.code == 5 && aux.students == 20 && strcmp(aux.name, "Economia")==0);
    free(aux.name);
    assert(nextCourse(course, 'S', &aux)==1);
    assert(aux.code == 10 && strcmp(aux.name, "Economia")==0);
    free(aux.name);
    assert(nextCourse(course, 'S', &aux)==1);
    assert(strcmp(aux.name, "Optativa 1")==0);
    free(aux.name);
    assert(nextCourse(course, 'S', &aux)==1);
    assert(strcmp(aux.name, "Optativa regalada")==0);
    free(aux.name);
    assert(nextCourse(course, 'S', &aux)==1);
    assert(strcmp(aux.name, "Programacion Imperativa")==0);
    free(aux.name);
    assert(nextCourse(course, 'S', &aux)==0);

    assert(courses(course, 'S')==5); assert(courses(course, 's')==5);
    assert(courses(course, 'T')==0); assert(courses(course, '?')==0);

    freeCourses(course);
    puts("OK! - EJ1");

    // ===========================================================================================
    
    busADT buses = newBusADT(cmp_int);
    
    assert(busSize(buses)==0);
    int aux2;
    assert(busInfo(buses, 104, &aux2)==0);
    
    busSet(buses, 104, 1040); // A la línea 140 se le asocia el entero 1040
    busSetIfAbsent(buses, 104, 500); // No hace nada porque la línea 140 ya tiene info
    
    assert(busInfo(buses, 104, &aux2)==1);
    assert(aux2==1040);
    assert(busSize(buses)==1);
    
    busSetIfAbsent(buses, 29, 10); // Lo agrega pues no había línea 29
    assert(busSize(buses)==2);
    assert(busInfo(buses, 103, &aux2)==0);
    assert(busInfo(buses, 28, &aux2)==0);
    
    freeBusADT(buses);
    
    buses = newBusADT(cmp_int);
    
    // Test con ADT vacío
    size_t dim;
    int *codes = busCodes(buses, 100, &dim);
    assert(codes == NULL);
    assert(dim == 0);
    
    // Agregar algunas líneas con diferentes info
    busSet(buses, 104, 1000);
    busSet(buses, 29, 500);
    busSet(buses, 152, 1000);  // Mismo info que 104
    busSet(buses, 67, 750);
    busSet(buses, 88, 1000);   // Mismo info que 104 y 152
    
    // Buscar info que no existe
    codes = busCodes(buses, 999, &dim);
    assert(codes == NULL);
    assert(dim == 0);
    
    // Buscar info que existe en una sola línea
    codes = busCodes(buses, 500, &dim);
    assert(codes != NULL);
    assert(dim == 1);
    assert(codes[0] == 29);
    free(codes);
    
    // Buscar info que existe en múltiples líneas
    codes = busCodes(buses, 1000, &dim);
    assert(codes != NULL);
    assert(dim == 3);
    // Los códigos deberían estar ordenados (dependiendo de la implementación)
    // Verificamos que están los tres números
    int found104 = 0, found152 = 0, found88 = 0;
    for(size_t i = 0; i < dim; i++) 
    {
        if(codes[i] == 104) found104 = 1;
        else if(codes[i] == 152) found152 = 1;
        else if(codes[i] == 88) found88 = 1;
    }
    assert(found104 && found152 && found88);
    free(codes);
    
        freeBusADT(buses);
    puts("OK! - EJ2");

    // ===========================================================================================
    // EJERCICIO 3 - Tests para toDigits()
    
    // Test con número de un dígito
    TList digits = toDigits(5);
    assert(digits != NULL);
    assert(digits->head == 5);
    assert(digits->tail == NULL);
    freeList(digits);
    
    // Test con cero
    digits = toDigits(0);
    assert(digits != NULL);
    assert(digits->head == 0);
    assert(digits->tail == NULL);
    freeList(digits);
    
    // Test con número de múltiples dígitos (123 -> 3, 2, 1)
    digits = toDigits(123);
    assert(digits != NULL);
    assert(digits->head == 3);  // Unidades primero
    assert(digits->tail != NULL);
    assert(digits->tail->head == 2);  // Decenas
    assert(digits->tail->tail != NULL);
    assert(digits->tail->tail->head == 1);  // Centenas
    assert(digits->tail->tail->tail == NULL);
    freeList(digits);
    
    // Test con número grande
    digits = toDigits(987654);
    assert(digits != NULL);
    assert(digits->head == 4);  // Último dígito primero
    TList current = digits;
    int expected[] = {4, 5, 6, 7, 8, 9};
    for(int i = 0; i < 6; i++) {
        assert(current != NULL);
        assert(current->head == expected[i]);
        current = current->tail;
    }
    assert(current == NULL);
    freeList(digits);
    
    puts("OK! - EJ3");

    return 0;
}