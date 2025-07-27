#include "1p-2023-2c.h"
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
    // EJERCICIO 1 - Tests para elimina()
    
    // Test del ejemplo del PDF
    char mat1[6][COLS_EJ1] = {
        {'L', '#', 'B', 'B', '#', 'L'},  // Palíndromo
        {'3', '1', 'r', 'R', '1', '3'},  // NO es palíndromo ('r' != 'R')
        {'3', '2', 'S', 'S', '2', '3'},  // Palíndromo
        {'R', 'L', 'A', 'H', 'N', 'N'},  // NO es palíndromo
        {'W', 'A', 'O', 'Y', 'U', 'T'},  // NO es palíndromo
        {'Q', 'S', 'G', 'S', 'M', 'A'}   // NO es palíndromo
    };
    
    // Solo las filas 0 y 2 son palíndromos, así que deberían quedar 4 filas
    assert(elimina(mat1, 6) == 4);

    // Verificar que las filas palíndromo fueron eliminadas (filas 0 y 2)
    // La matriz debería quedar: fila 1, 3, 4, 5 movidas hacia arriba
    assert(mat1[0][0] == '3' && mat1[0][1] == '1'); // Era la fila 1
    assert(mat1[1][0] == 'R' && mat1[1][1] == 'L'); // Era la fila 3
    assert(mat1[2][0] == 'W' && mat1[2][1] == 'A'); // Era la fila 4
    assert(mat1[3][0] == 'Q' && mat1[3][1] == 'S'); // Era la fila 5
    
    // Test con matriz sin palíndromos
    char mat2[3][COLS_EJ1] = {
        {'A', 'B', 'C', 'D', 'E', 'F'},
        {'G', 'H', 'I', 'J', 'K', 'L'},
        {'M', 'N', 'O', 'P', 'Q', 'R'}
    };
    
    assert(elimina(mat2, 3) == 3);
    
    // Test con todas las filas palíndromo
    char mat3[2][COLS_EJ1] = {
        {'A', 'B', 'C', 'C', 'B', 'A'},
        {'X', 'Y', 'Z', 'Z', 'Y', 'X'}
    };
    
    assert(elimina(mat3, 2) == 0);
    
    puts("OK! - EJ1");
    
    // ===========================================================================================
    // EJERCICIO 2 - Tests para bordes()
    
    // Test del ejemplo del PDF con M=6
    int mat_ej2[M_EJ2][M_EJ2] = {
        {1, 1, 1, 1, 1, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 2, 3, 3, 2, 1},
        {1, 2, 3, 3, 2, 1},
        {1, 2, 2, 2, 2, 1},
        {1, 1, 1, 1, 1, 1}
    };
    
    int sumas[M_EJ2/2];
    bordes(mat_ej2, sumas);
    
    // Según el ejemplo del PDF: borde 1 suma 20, borde 2 suma 24, borde 3 suma 12
    assert(sumas[0] == 20); // Primer borde (exterior): 20 unos
    assert(sumas[1] == 24); // Segundo borde: 12 doses * 2 = 24
    assert(sumas[2] == 12); // Tercer borde (centro): 4 treses * 3 = 12
    
    puts("OK! - EJ2");
    
    // ===========================================================================================
    // EJERCICIO 3 - Tests para anagrama()
    
    // Tests del ejemplo del PDF
    char * s = "anagrama";
    
    assert(anagrama(s, "amar gana"));
    assert(anagrama("enrique", "quieren"));
    assert(anagrama(s, s));
    assert(anagrama("", ""));
    assert(anagrama("amar gana", s));
    assert(anagrama("", ""));
    assert(anagrama("a gentleman", "elegant man"));
    
    assert(anagrama("a", "") == 0);
    assert(anagrama("mar", "amar") == 0);
    
    // Tests adicionales
    assert(anagrama("listen", "silent"));
    assert(anagrama("evil", "vile"));
    assert(anagrama("a", "a"));
    assert(anagrama("abc", "bca"));
    assert(anagrama("abc", "def") == 0);
    assert(anagrama("aab", "abb") == 0);
    
    puts("OK! - EJ3");
    
    return 0;
}


