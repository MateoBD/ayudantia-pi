#include "1p-2022-1c.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void print_matrix(char mat[][COLS_EJ1], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < COLS_EJ1; j++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    // ===========================================================================================
    // EJERCICIO 1 - Tests para diffSim()
    
    // Test del ejemplo del PDF
    int m1[6][COLS_EJ1] = {
        {1, 2, 3, 4, -1},
        {3, 4, 5, -1, 0},
        {10, 15, 20, -1, 0},
        {-1, 0, 0, 0, 0},
        {-1, 0, 0, 0, 0},
        {5, 6, 7, -1, 0}
    };
    
    int m2[6][COLS_EJ1] = {
        {1, 2, 5, 6, -1},
        {-1, 0, 0, 0, 0},
        {15, -1, 0, 0, 0},
        {1, 2, 3, 4, -1},
        {-1, 0, 0, 0, 0},
        {1, 2, 5, 6, -1}
    };
    
    int m3[6][COLS_EJ1];
    
    diffSim(m1, m2, m3, 6);
    
    // Verificar resultado esperado según el PDF
    // Fila 0: diferencia simétrica de {1,2,3,4} y {1,2,5,6} = {3,4,5,6}
    assert(m3[0][0] == 3 && m3[0][1] == 4 && m3[0][2] == 5 && m3[0][3] == 6 && m3[0][4] == -1);
    
    // Fila 1: diferencia simétrica de {3,4,5} y {} = {3,4,5}
    assert(m3[1][0] == 3 && m3[1][1] == 4 && m3[1][2] == 5 && m3[1][3] == -1);
    
    // Fila 2: diferencia simétrica de {10,15,20} y {15} = {10,20}
    assert(m3[2][0] == 10 && m3[2][1] == 20 && m3[2][2] == -1);
    
    // Fila 3: diferencia simétrica de {} y {1,2,3,4} = {1,2,3,4}
    assert(m3[3][0] == 1 && m3[3][1] == 2 && m3[3][2] == 3 && m3[3][3] == 4 && m3[3][4] == -1);
    
    // Fila 4: diferencia simétrica de {} y {} = {}
    assert(m3[4][0] == -1);
    
    // Fila 5: diferencia simétrica de {5,6,7} y {1,2,5,6} = {1,2,7}
    assert(m3[5][0] == 1 && m3[5][1] == 2 && m3[5][2] == 7 && m3[5][3] == -1);

    puts("OK! - EJ1");
    
    // ===========================================================================================
    // EJERCICIO 2 - Tests para eliminaVoc()

    // Tests del ejemplo del PDF
    char str1[] = "hola mundo";
    eliminaVoc(str1);
    assert(strcmp(str1, "hl mnd") == 0);
    
    char str2[] = "hola a todo el mundo";
    eliminaVoc(str2);

    assert(strcmp(str2, "hl a td l mnd") == 0);
    
    char str3[] = "xyz";
    eliminaVoc(str3);
    assert(strcmp(str3, "xyz") == 0); // Sin cambios
    
    char str4[] = "aholoaaa";
    eliminaVoc(str4);

    assert(strcmp(str4, "hlaaa") == 0);
    
    char str5[] = "";
    eliminaVoc(str5);
    assert(strcmp(str5, "") == 0);
    
    char str6[] = "aa eo iu oa uo";
    eliminaVoc(str6);
    assert(strcmp(str6, "aa eo iu oa uo") == 0); // Sin cambios
    
    char str7[] = "pa po pi po pu";
    eliminaVoc(str7);
    assert(strcmp(str7, "p p p p p") == 0);
    
    char str8[] = "aeiou";
    eliminaVoc(str8);
    assert(strcmp(str8, "aeiou") == 0); // Sin cambios, todas consecutivas
    
    char str9[] = "a,e,i,o,u";
    eliminaVoc(str9);
    assert(strcmp(str9, "a,e,i,o,u") == 0); // Sin cambios
    
    puts("OK! - EJ2");
    
    // ===========================================================================================
    // EJERCICIO 3 - Tests para secuenciaAsc()
    
    // Test del ejemplo del PDF
    int v1[] = {1, 1, 3, 4, 4, 7, 10, 9, 11};
    int comienzo, longitud;
    
    secuenciaAsc(v1, 9, &comienzo, &longitud);
    assert(comienzo == 1 && longitud == 3); // Secuencia {1,3,4} desde índice 1
    
    // Test con vector vacío
    secuenciaAsc(NULL, 0, &comienzo, &longitud);
    assert(comienzo == 0 && longitud == 0);
    
    // Test con vectores del ejemplo
    int v2[] = {3};
    secuenciaAsc(v2, 1, &comienzo, &longitud);
    assert(comienzo == 0 && longitud == 1);
    
    int v3[] = {2, 2, 2};
    secuenciaAsc(v3, 3, &comienzo, &longitud);
    assert(comienzo == 0 && longitud == 1);
    
    int v4[] = {3, 2, 1, 0, -1};
    secuenciaAsc(v4, 5, &comienzo, &longitud);
    assert(comienzo == 0 && longitud == 1);
    
    int v5[] = {1, 2, 3, 4, 5, 7, 10, 90, 111};
    secuenciaAsc(v5, 9, &comienzo, &longitud);
    assert(comienzo == 0 && longitud == 9); // Toda la secuencia es ascendente
    
    // Test adicional: múltiples secuencias, debe elegir la primera más larga
    int v6[] = {1, 2, 5, 3, 4, 5, 6, 7};
    secuenciaAsc(v6, 8, &comienzo, &longitud);
    assert(comienzo == 3 && longitud == 5); // Secuencia {3,4,5,6,7} desde índice 3
    
    puts("OK! - EJ3");
    
    return 0;
}


