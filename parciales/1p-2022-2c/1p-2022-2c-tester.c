#include "1p-2022-2c.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(void) {
    // ===========================================================================================
    // EJERCICIO 1 - Tests para ejer1()
    
    // Test del ejemplo del PDF que debe retornar 1
    int mat1[N_EJ1][N_EJ1] = {
        {3, 4, 1, 2},
        {8, 7, 6, 5},
        {9, 10, 11, 12},
        {15, 16, 13, 14}
    };

    assert(ejer1(mat1) == 1);
    
    // Test que debe retornar 0 (repite el 1 en la primera fila y no está el 4)
    int mat2[N_EJ1][N_EJ1] = {
        {3, 1, 1, 2},
        {8, 7, 6, 5},
        {9, 10, 11, 12},
        {15, 16, 13, 14}
    };
    assert(ejer1(mat2) == 0);
    
    // Test que debe retornar 0 (está el 11 en la última fila, y no está el 14)
    int mat3[N_EJ1][N_EJ1] = {
        {3, 1, 4, 2},
        {8, 7, 6, 5},
        {9, 10, 11, 12},
        {15, 16, 13, 11}
    };
    assert(ejer1(mat3) == 0);
    
    
    puts("OK! - EJ1");
    
    // ===========================================================================================
    // EJERCICIO 2 - Tests para palEnMat()
    
    // Matriz del ejemplo del PDF
    char mat[N_EJ2][N_EJ2] = {
        {'L', 'O', 'B', 'R', 'A', 'Z'},
        {'F', 'H', 'R', 'G', 'O', 'R'},
        {'C', 'O', 'S', 'A', 'D', 'A'},
        {'R', 'L', 'A', 'H', 'N', 'N'},
        {'W', 'A', 'O', 'Y', 'U', 'T'},
        {'Q', 'S', 'G', 'S', 'M', 'A'}
    };
    
    // Tests que deben retornar 1
    assert(palEnMat(mat, 5, 1, "SAL") == 1);    // fila 5, columna 1
    assert(palEnMat(mat, 2, 0, "COSA") == 1);   // fila 2, columna 0
    assert(palEnMat(mat, 2, 0, "CHB") == 1);    // fila 2, columna 0
    assert(palEnMat(mat, 2, 0, "CLOS") == 1);   // fila 2, columna 0
    assert(palEnMat(mat, 2, 0, "") == 1);       // string vacío
    assert(palEnMat(mat, 2, 0, "C") == 1);      // fila 2, columna 0
    
    // Tests que deben retornar 0
    assert(palEnMat(mat, 5, 1, "sal") == 0);     // case sensitive
    assert(palEnMat(mat, 5, 1, "SALA") == 0);    // no se encuentra
    assert(palEnMat(mat, 2, 0, "COSADAS") == 0); // muy largo
    assert(palEnMat(mat, 6, 0, "C") == 0);       // fila fuera de rango
    
    
    puts("OK! - EJ2");
    
    // ===========================================================================================
    // EJERCICIO 3 - Tests para factoreo()
    
    int factores1[] = {2, 2, 2, 3, 3, 4, 5, 5, 6, 6, 6, 6, 7, -1};
    long resultado = factoreo(factores1);
    assert(resultado == 65318400);
    assert(factores1[0] == 2);
    assert(factores1[1] == 3);
    assert(factores1[2] == 4);
    assert(factores1[3] == 5);
    assert(factores1[4] == 6);
    assert(factores1[5] == 7);
    assert(factores1[6] == -1);
    
    int factores2[] = {2, -1};
    resultado = factoreo(factores2);
    assert(resultado == 2);
    assert(factores2[0] == 2);
    assert(factores2[1] == -1);
    
    int factores3[] = {11, 11, 13, -1};
    resultado = factoreo(factores3);
    assert(resultado == 1573); // 11 * 11 * 13
    assert(factores3[0] == 11);
    assert(factores3[1] == 13);
    assert(factores3[2] == -1);
    
    int factores4[] = {-1};
    resultado = factoreo(factores4);
    assert(resultado == 0);
    assert(factores4[0] == -1);
    
    int factores5[] = {1, -1};
    resultado = factoreo(factores5);
    assert(resultado == 1);
    assert(factores5[0] == 1);
    assert(factores5[1] == -1);
    
    
    puts("OK! - EJ3");
    
    return 0;
}


