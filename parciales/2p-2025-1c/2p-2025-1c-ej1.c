#include "2p-2025-1c-ej1.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define CANT_CARRERAS 26

struct node
{
    struct courseData head;
    struct node * tail;
};

typedef struct node * TList;

typedef struct
{
    TList materias;
    size_t cant_materias;
    size_t cant_alumnos;
    TList it;
} Tcarrera;

struct coursesCDT
{
    Tcarrera carreras[CANT_CARRERAS];
};

coursesADT newCourses(void)
{
    coursesADT new = calloc(1, sizeof(*new));
    return new;
}

static void freeListRec(TList list)
{
    if (list == NULL)
    {
        return;
    }
    freeListRec(list->tail);
    free(list->head.name);
    free(list);
}

void freeCourses(coursesADT course)
{
    for (size_t i = 0; i < CANT_CARRERAS; i++)
    {
        freeListRec(course->carreras[i].materias);
    }
    free(course);
}

static TList createNewNode(int courseCode, const char * courseName, unsigned int students)
{
    TList new_node = malloc(sizeof(*new_node));
    new_node->head = (struct courseData) {
        .code = courseCode,
        .students = students,
    };
    new_node->head.name = malloc((strlen(courseName) + 1) * sizeof(char));
    strcpy(new_node->head.name, courseName);
    new_node->tail = NULL;
    return new_node;
}

// funcion de comparacion que desempata por codigo si el nombre es igual
static int my_cmp_func(int courseCode1, const char * courseName1, int courseCode2, const char * courseName2)
{
    int c = strcmp(courseName1, courseName2);
    if (c == 0)
    {
        c = courseCode1 - courseCode2;
    }
    return c;
}

static TList addListRec(TList list, int courseCode, const char * courseName, unsigned int students, int * added)
{
    int c;
    if (list == NULL || (c = my_cmp_func(courseCode, courseName, list->head.code, list->head.name)) < 0)
    {
        *added = 1;
        TList new_node = createNewNode(courseCode, courseName, students);
        new_node->tail = list;
        return new_node;
    }
    if (c == 0)
    {
        return list;
    }
    list->tail = addListRec(list->tail, courseCode, courseName, students, added);
    return list;
}

int addCourse(coursesADT course, char degree, int courseCode, const char * courseName, unsigned int students)
{
    if (!isalpha(degree))
    {
        return 0;
    }

    int added = 0;
    course->carreras[toupper(degree) - 'A'].materias = addListRec(course->carreras[toupper(degree) - 'A'].materias, courseCode, courseName, students, &added);
    course->carreras[toupper(degree) - 'A'].cant_materias += added;
    course->carreras[toupper(degree) - 'A'].cant_alumnos += (added) ? students : 0;
    return added;
}

size_t courses(const coursesADT course, char degree)
{
    if (!isalpha(degree))
    {
        return 0;
    }
    return course->carreras[toupper(degree) - 'A'].cant_materias;
}

size_t students(const coursesADT course, char degree)
{
    if (!isalpha(degree))
    {
        return 0;
    }
    return course->carreras[toupper(degree) - 'A'].cant_alumnos;
}

void toBeginByDegree(coursesADT course, char degree)
{
    if (!isalpha(degree))
    {
        return;
    }
    course->carreras[toupper(degree) - 'A'].it = course->carreras[toupper(degree) - 'A'].materias;
}

int nextCourse(coursesADT course, char degree, struct courseData * data)
{
    if (!isalpha(degree))
    {
        return 0;
    }
    if (course->carreras[toupper(degree) - 'A'].it == NULL)
    {
        return 0;
    }
    *data = (struct courseData) {
        .name = malloc((strlen(course->carreras[toupper(degree) - 'A'].it->head.name) + 1) * sizeof(char)),
        .code = course->carreras[toupper(degree) - 'A'].it->head.code,
        .students = course->carreras[toupper(degree) - 'A'].it->head.students,
    };
    strcpy(data->name, course->carreras[toupper(degree) - 'A'].it->head.name);
    course->carreras[toupper(degree) - 'A'].it = course->carreras[toupper(degree) - 'A'].it->tail;
    return 1;
}


