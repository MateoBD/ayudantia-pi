#include "1p-2023-2c.h"

#include <stdlib.h>
#include <ctype.h>

// =========================
// EJ1 - elimina()
// =========================

static int es_capicua(char fil[])
{
    char ok = 1;
    for (int i = 0; i < COLS_EJ1 / 2 && ok; i++)
    {
        ok = (fil[i] == fil[COLS_EJ1 - 1 - i]);
    }
    return ok;
}

static void copy_fil(char dest[], char src[])
{
    for (int i = 0; i < COLS_EJ1; i++)
    {
        dest[i] = src[i];
    }
}

// planteo un "elimina ceros" con las filas
int elimina(char mat[][COLS_EJ1], int fils)
{
    int write_idx = 0;
    for (int read_idx = 0; read_idx < fils; read_idx++)
    {
        if (!es_capicua(mat[read_idx]))
        {
            copy_fil(mat[write_idx++], mat[read_idx]);
        }
    }
    return write_idx;
}

// =========================
// EJ2 - bordes()
// =========================

static int calcular_suma_borde_fils(int mat[][COLS_EJ1], int borde)
{
    int suma = 0;
    for (int i = borde; i < M_EJ2 - borde; i++)
    {
        suma += mat[borde][i];
        suma += mat[M_EJ2 - 1 - borde][i];
    }
    return suma;
}

static int calcular_suma_borde_cols(int mat[][COLS_EJ1], int borde)
{
    int suma = 0;
    for (int i = borde + 1; i < M_EJ2 - borde - 1; i++)
    {
        suma += mat[i][borde];
        suma += mat[i][M_EJ2 - 1 - borde];
    }
    return suma;
}

static int calcular_suma_borde(int mat[][COLS_EJ1], int borde)
{
    
    return calcular_suma_borde_fils(mat, borde) + calcular_suma_borde_cols(mat, borde);
}

void bordes(int mat[][M_EJ2], int sumas[])
{
    for (int i = 0; i < M_EJ2 / 2; i++)
    {
        sumas[i] = calcular_suma_borde(mat, i);
    }
}

// =========================
// EJ3 - anagrama()
// =========================

#define LETRAS ('Z' - 'A' + 1)
#define CHAR_TO_IDX(c) ((unsigned int)(toupper(s[i]) - 'A'))    // el (unsigned int) es por un warning, no es necesario

static void sumar_apariciones(int vec_ap[], char * s)
{
    for (size_t i = 0; s[i] != '\0'; i++)
    {
        if (isalpha(s[i]))
        {
            vec_ap[CHAR_TO_IDX(s[i])]++;
        }
    }
}

static int validar_apariciones(int vec_ap[], char * s)
{
    int ok = 1;
    for (size_t i = 0; s[i] != '\0' && ok; i++)
    {
        if (isalpha(s[i]))
        {
            ok = (vec_ap[CHAR_TO_IDX(s[i])] > 0);    // si en algun momento vec_ap es <= 0 salgo
            vec_ap[CHAR_TO_IDX(s[i])]--;
        }
    }
    for (size_t i = 0; i < LETRAS && ok; i++)
    {
        ok = (vec_ap[i] == 0);
    }
    return ok;
}

int anagrama(char * s1, char * s2)
{
    int vec_ap[LETRAS] = {0};
    sumar_apariciones(vec_ap, s1);
    return validar_apariciones(vec_ap, s2);
}
