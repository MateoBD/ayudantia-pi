#include "1p-2022-2c.h"

#include <stdlib.h>
#include <ctype.h>

// =========================
// EJ1 - ejer1()
// =========================

#define EN_RANGO_EJ1(n) (1 <= (n) && (n) <= N_EJ1 * N_EJ1)

// vector de apariciones con N*N lugares
int ejer1(int mat[][N_EJ1])
{
    char vec_ap[N_EJ1 * N_EJ1] = {0};
    char ok = 1;
    for (int i = 0; i < N_EJ1 && ok; i++)
    {
        for (int j = 0; j < N_EJ1 && ok; j++)
        {
            if (!EN_RANGO_EJ1(mat[i][j]))
            {
                ok = 0;
            }
            else
            {
                vec_ap[mat[i][j] - 1]++;
                ok = (vec_ap[mat[i][j] - 1] == 1); // - 1 porque no tomamos al 0
            }
        }
    }
    return ok;
}

// =========================
// EJ2 - palEnMat()
// =========================

#define EN_RANGO_EJ2(i) (0 <= (i) && (i) < N_EJ2)

#define TOTAL_DIRS 8

static int pal_en_dir(char mat[][N_EJ2], int fil, int col, char * str, signed char dir[])
{
    if (!EN_RANGO_EJ2(fil) || !EN_RANGO_EJ2(col))
    {
        return 0;
    }
    fil += dir[0];
    col += dir[1];

    for (int i = 1; str[i] != '\0'; i++)
    {
        if (!EN_RANGO_EJ2(fil) || !EN_RANGO_EJ2(col) || mat[fil][col] != str[i])
        {
            return 0;
        }
        fil += dir[0];
        col += dir[1];
    }
    return 1;
}

int palEnMat(char mat[][N_EJ2], int fil, int col, char * str)
{
    if (!EN_RANGO_EJ2(fil) || !EN_RANGO_EJ2(col) || (str[0] != '\0' && mat[fil][col] != str[0]))
    {
        return 0;
    }

    if (str[0] == '\0')
    {
        return 1;
    }

    // usamos un vector de direcciones para poder recorrer la matriz
    signed char vec_dir[TOTAL_DIRS][2] = {
        { 1,  0},   // abajo
        { 1,  1},   // abajo-derecha
        { 0,  1},   // derecha
        {-1,  1},   // arriba-derecha
        {-1,  0},   // arriba
        {-1, -1},   // arriba-izquierda
        { 0, -1},   // izquierda
        { 1, -1},   // abajo-izquierda
    };


    for (int i = 0; i < TOTAL_DIRS; i++)
    {
        if (pal_en_dir(mat, fil, col, str, vec_dir[i]))
        {
            return 1;
        }
    }
    return 0;
}

// =========================
// EJ3 - anagrama()
// =========================

long factoreo(int factores[])
{
    if (factores[0] == -1)
    {
        return 0;
    }
    long res = 1;
    int write_idx = 0;
    for (int read_idx = 0; factores[read_idx] != -1; read_idx++)
    {
        res *= factores[read_idx];
        if (factores[read_idx] != factores[read_idx + 1])
        {
            factores[write_idx++] = factores[read_idx];
        }
    }
    factores[write_idx] = -1;
    return res;
}
