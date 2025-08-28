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
    
    unsigned char v[] = {1, 2, 1, 3, 1, 4, 5, 2};
    int dim, del;
    firstN(v, 8, 3, &dim, &del); // dim es 8, del es 0, v no cambia
    firstN(v, 8, 8, &dim, &del); // dim es 8, del es 0, v no cambia
    firstN(v, 8, 4, &dim, &del); // dim es 8, del es 0, v no cambia
    firstN(v, 8, 1, &dim, &del); // dim=5, del=3, v = {1, 2, 3, 4, 5};

    unsigned char w[] = {1, 2, 1, 3, 1, 4, 5, 2};
    firstN(w, 8, 0, &dim, &del); // dim=0, del=8, w = {}

    unsigned char t[] = {1, 2, 1, 3, 1, 4, 5, 2};
    firstN(t, 8, 2, &dim, &del); // dim=7, del=1, t = {1, 2, 1, 3, 4, 5, 2}

    puts("OK! - EJ1");
    
    // ===========================================================================================
    // EJERCICIO 2 - Tests para eliminaVoc()

    char board[][8] = {
        {'0', '0', '0', '1', '0', '0', '0', '0'},
        {'0', '0', '1', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0', '0', '0'},
        {'0', '1', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '1', '0'},
        {'1', '0', '0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '1', '0', '0'},
        {'0', '0', '0', '0', '0', '0', '0', '1'}
    };

    // por ejemplo, hay tres reinas en la columna 4 y dos en la fila 6
    assert(nQueens(8, board) == 0);

    char board2[][6] = {
        {'0', '0', '1', '0', '0', '0'},
        {'1', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '1', '0', '0'},
        {'0', '1', '0', '0', '0', '1'},
        {'0', '0', '0', '0', '1', '0'},
        {'1', '0', '1', '0', '0', '0'}
    };
    // Hay 6 reinas y no se atacan, retorna true
    assert(nQueens(6, board2));

    char board3[][6] = {
        {'0', '0', '1', '0', '0', '0'},
        {'1', '0', '0', '0', '1', '0'},
        {'0', '1', '0', '0', '0', '1'},
        {'0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0'},
        {'0', '0', '0', '0', '0', '0'}
    };
    // Las reinas en (1,0) y (2,1) se amenazan en forma diagonal
    assert(nQueens(6, board3) == 0);

    char board4[][6] = {
        {'0', '0', '0', '1', '0', '0'},
        {'0', '0', '0', '0', '0', '0'},
        {'0', '1', '0', '0', '1', '0'},
        {'1', '0', '0', '0', '0', '1'},
        {'0', '0', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '1', '0'}
    };
    // No se amenazan pero hay menos de 6 reinas
    assert(nQueens(6, board4) == 0);

    // No hay solución para tableros de dimensión 2 o 3
    char board5[2][2] = {{'0'}};
    assert(nQueens(2, board5) == 0);
    char board6[3][3] = {{'0'}};
    assert(nQueens(3, board6) == 0);

    // En un tablero de 1x1 debe haber una reina
    char board1[][1] = {{'1'}};
    assert(nQueens(1, board1));
    
    puts("OK! - EJ2");
    
    // ===========================================================================================
    // EJERCICIO 3 - Tests para secuenciaAsc()
    
    char wordMatrix[][4] = {
        {'T', 'e', 'S', 't'},
        {'b', 'e', 'S', 'T'},
        {'B', 'E', 'S', 'o'},
        {'B', 'E', 'S', 'A'}
    };
    // Considerando todas las filas no es en la escalera
    // pues los últimos dos cambios son en la última letra
    assert(!isWordLadder(4, 4, wordMatrix));
    // Considerando una sola fila es escalera
    assert(isWordLadder(1, 4, wordMatrix) == 1);
    // Considerando las tres primeras filas es escalera
    assert(isWordLadder(3, 4, wordMatrix) == 1);

    char wordMatrix2[][3] = {
        {'T', 'e', 'S'},
        {'t', 'b', 'e'},
        {'S', 'b', 'E'},
        {'B', 'b', 'e'}
    };
    // TeS -> Tbe cambian dos letras
    assert(!isWordLadder(4, 3, wordMatrix2));

    char wordMatrix3[][3] = {
        {'a', 'm', 'o'},
        {'a', 'r', 'o'},
        {'o', 's', 'a'}
    };
    // aro -> osa cambian tres letras
    assert(!isWordLadder(3, 3, wordMatrix3));
    
    puts("OK! - EJ3");
    
    return 0;
}


