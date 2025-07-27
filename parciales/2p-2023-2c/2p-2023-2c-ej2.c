#include "2p-2023-2c-ej2.h"
#include <stdlib.h>

#define LANDMARK_DISTANCE 100

typedef struct landmark_t
{
    landmarkType elem;
    char occupied;
} landmark_t;

struct landmarkCDT
{
    landmark_t * arr_landmark;
    size_t size;    // cantidad real de landmarks
    size_t dim;     // dimensión total del arreglo
    compare_function_t cmp;
};


landmarkADT newLandmark(compare_function_t cmp)
{
    landmarkADT new_landmarks = malloc(sizeof(*new_landmarks));
    new_landmarks->arr_landmark = NULL;
    new_landmarks->dim = 0;
    new_landmarks->size = 0;
    new_landmarks->cmp = cmp;
    return new_landmarks;
}

void addLandmark(landmarkADT landmark, size_t meters, landmarkType site)
{
    size_t idx = meters / LANDMARK_DISTANCE;
    if (idx >= landmark->dim)
    {
        landmark->arr_landmark = realloc(landmark->arr_landmark, (idx + 1) * sizeof(*landmark->arr_landmark));  // (idx + 1) es nuestra nueva dimensión
        for (size_t i = landmark->dim; i < idx + 1; i++)
        {
            landmark->arr_landmark[i].occupied = 0;
        }
        landmark->dim = idx + 1;
    }

    landmark->size += !(landmark->arr_landmark[idx].occupied); // sumo 1 a size si no estaba ocupado
    landmark->arr_landmark[idx].elem = site;
    landmark->arr_landmark[idx].occupied = 1;
}

int hasLandmark(const landmarkADT landmark, size_t meters)
{
    size_t idx = meters / LANDMARK_DISTANCE;
    if (idx >= landmark->dim)
    {
        return 0;
    }
    return landmark->arr_landmark[idx].occupied;
}

int distance(const landmarkADT landmark, landmarkType site)
{
    size_t idx = 0;
    char found = 0;
    while (idx < landmark->dim && !found)
    {
        if (landmark->arr_landmark[idx].occupied)
        {
            found = landmark->cmp(landmark->arr_landmark[idx].elem, site) == 0;
        }
        idx++;
    }

    if (!found)
    {
        return -1;
    }

    return (idx - 1) * LANDMARK_DISTANCE;
}

size_t landmarkCount(const landmarkADT landmark)
{
    return landmark->size;
}

landmarkType * landmarks(const landmarkADT landmark)
{
    size_t dim;
    return landmarksBetween(landmark, 0, landmark->dim * LANDMARK_DISTANCE, &dim);
}

#define REALLOC_BLOCK 10
#include <stdio.h>

landmarkType * landmarksBetween(const landmarkADT landmark, size_t from, size_t to, size_t *dim)
{
    size_t idx_from = from / LANDMARK_DISTANCE, idx_to = to / LANDMARK_DISTANCE;

    if (from > to || landmark->size == 0)
    {
        *dim = 0;
        return NULL;
    }

    landmarkType * to_ret = NULL;
    size_t write_idx = 0;

    for (size_t read_idx = idx_from; read_idx <= idx_to && read_idx < landmark->dim; read_idx++)
    {
        if (landmark->arr_landmark[read_idx].occupied)
        {
            if (write_idx % REALLOC_BLOCK == 0)
            {
                to_ret = realloc(to_ret, (write_idx + REALLOC_BLOCK) * sizeof(*to_ret));
            }
            to_ret[write_idx++] = landmark->arr_landmark[read_idx].elem;
        }
    }

    if (write_idx > 0)
    {
        to_ret = realloc(to_ret, write_idx * sizeof(*to_ret));
    }
    *dim = write_idx;
    return to_ret;
}

void freeLandmark(landmarkADT landmark)
{
    free(landmark->arr_landmark);
    free(landmark);
}
