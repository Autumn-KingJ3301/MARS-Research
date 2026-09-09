#ifndef DIFFERENCE_H
#define DIFFERENCE_H

#include "observation.h"

typedef struct
{
    /* data */
    int index;
    double x_value;
    double y_value;

} Difference;

typedef struct{
    int count;
    Difference items[MAX_COMPONENTS];
} DifferenceSet;

DifferenceSet difference(Observation x, Observation y);

#endif
