#include "1p-2024-1c.h"

#include <stdlib.h>
#include <ctype.h>

// =========================
// EJ1 - firstN()
// =========================

#define CHARS 256

void firstN(unsigned char vec[], int dim, unsigned int n, int * new_dim, int * deleted)
{
    size_t apariciones[CHARS] = {0};
    int write_idx = 0;
    *deleted = 0;
    for (int read_idx = 0; read_idx < dim; read_idx++)
    {
        if (apariciones[CHARS] < n)
        {
            vec[write_idx++] = vec[read_idx];
        }
        else
        {
            (*deleted)++;
        }
    }
    *new_dim = write_idx;
    return;
}

// =========================
// EJ2 - nQueens()
// =========================

#define DIRS_EJ2 4

#define EN_RANGO_EJ2(x, y, n) (0 <= (x) && (x) < n && 0 <= (y) && (y) < n) 

static int check_dir(int n, char mat[][n], signed char dir[], size_t fil, size_t col)
{
    if (!EN_RANGO_EJ2(fil, col, n))
    {
        return 0;
    }
    fil += dir[0];
    col += dir[1];
    while (EN_RANGO_EJ2(fil, col, n))
    {
        if (mat[fil][col] == '1')
        {
            return 0;
        }
    }
    return 1;
}

static int check_queens(int n, char mat[][n], size_t fil, size_t col)
{
    signed char vec_dir[DIRS_EJ2][2] = {
        { 1 -1},
        { 1, 0},
        { 1, 1},
        { 0, 1}
    };
    char todo_ok = 1;
    for (int i = 0; i < DIRS_EJ2 && todo_ok; i++)
    {
        todo_ok = check_dir(n, mat, vec_dir[i], fil, col);
    }
    return todo_ok;
}

int nQueens(int n, char mat[][n])
{
    char todo_ok = 1;
    for (int i = 0; i < n && todo_ok; i++)
    {
        for (int j = 0; j < n && todo_ok; j++)
        {
            if (mat[i][j] == '1')
            {
                todo_ok = check_queens(n, mat, i, j);
            }
        }
    }
    return todo_ok;
}

// =========================
// EJ3 - isWordLadder()
// =========================

static int compare_words(const char s1[], const char s2[], int len, int * change_pos)
{
    *change_pos = -1;
    int todo_ok = 1;
    for (int i = 0; i < len && todo_ok; i++)
    {
        if (toupper(s1[i]) != toupper(s2[i]))
        {
            if (*change_pos != -1)  // si ya habia un cambio retorno 0
            {
                todo_ok = 0;
            }
            else
            {
                *change_pos = i;
            }
        }
    }
    return (todo_ok && *change_pos != -1);  // si no hubo cambios (*change_pos == -1) retorno 0
}

int isWordLadder(int fils, int cols, char mat[][cols])
{
    if (fils <= 1)
    {
        return 1;
    }
    int todo_ok = 1;
    int last_change_pos = -1;  // me guardo la ultima posicion de cambio
    for (int i = 1; i < fils && todo_ok; i++)
    {
        int change_pos;
        todo_ok = compare_words(mat[i-1], mat[i], cols, &change_pos);
        todo_ok = (todo_ok && change_pos != last_change_pos);
        last_change_pos = change_pos;
    }
    return todo_ok;
}
