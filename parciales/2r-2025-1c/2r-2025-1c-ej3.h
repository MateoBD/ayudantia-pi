#ifndef _2R_2025_1C_EJ3_H
#define _2R_2025_1C_EJ3_H

#include <stdint.h>

typedef struct node { 
   char * person; 
   unsigned int popularity; 
   struct node * tail; 
} node; 
 
typedef node * TList; 

TList upPop(TList list, const char * person, unsigned int popularity);

#endif // _2R_2025_1C_EJ3_H
