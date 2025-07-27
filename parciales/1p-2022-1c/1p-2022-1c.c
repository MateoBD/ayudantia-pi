#include "1p-2022-1c.h"

#include <ctype.h>

// =========================
// EJ1 - diffSim()
// =========================

static void diff_sim_fils(int f1[], int f2[], int res[])
{
    int write_idx = 0;
    int read1_idx = 0;
    int read2_idx = 0;
    while (f1[read1_idx] != -1 || f2[read2_idx] != -1)
    {
        if (f1[read1_idx] == -1 || (f2[read2_idx] != -1 && f1[read1_idx] > f2[read2_idx]))
        {
            res[write_idx++] = f2[read2_idx++];
        } 
        else if (f2[read2_idx] == -1 || f1[read1_idx] < f2[read2_idx])
        {
            res[write_idx++] = f1[read1_idx++];
        }
        else
        {
            read1_idx++;
            read2_idx++;
        }
    }
    res[write_idx] = -1;
}

void diffSim(int m1[][COLS_EJ1], int m2[][COLS_EJ1], int m3[][COLS_EJ1], int filas)
{
    for (int i = 0; i < filas; i++)
    {
        diff_sim_fils(m1[i], m2[i], m3[i]);
    }
}

// =========================
// EJ2 - eliminaVoc()
// =========================

#define ES_VOCAL(c) ((c) == 'A' || (c) == 'E' || (c) == 'I' || (c) == 'O' || (c) == 'U' || (c) == 'a' || (c) == 'e' || (c) == 'i' || (c) == 'o' || (c) == 'u')
#define ES_CONSONANTE(c) (isalpha(c) && !ES_VOCAL(c))

void eliminaVoc(char * str)
{
    int write_idx = 0;
    int read_idx = 0;
    char consonante_antes = 0;
    while (str[read_idx] != '\0')
    {
        if (!ES_VOCAL(str[read_idx]) || (!consonante_antes && !ES_CONSONANTE(str[read_idx + 1])))
        {
            str[write_idx++] = str[read_idx];
        }
        consonante_antes = ES_CONSONANTE(str[read_idx]);
        read_idx++;
    }
    str[write_idx] = '\0';
}

// =========================
// EJ3 - secuenciaAsc()
// =========================

void secuenciaAsc(int vec[], int dim, int * comienzo, int * longitud)
{
    *comienzo = 0;
    *longitud = (dim > 0);
    int current_com = 0;
    int current_long = 1;
    for (int i = 1; i < dim; i++)
    {
        if (vec[i - 1] < vec[i])
        {
            current_long++;
        }
        else
        {
            current_com = i;
            current_long = 1;
        }

        if (current_long > *longitud)
        {
            *comienzo = current_com;
            *longitud = current_long;
        }
    }
    
}
