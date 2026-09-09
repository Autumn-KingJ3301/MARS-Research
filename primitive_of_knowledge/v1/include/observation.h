#ifndef OBSERVATION_H
#define OBSERVATION_H

#define MAX_COMPONENTS 32

typedef struct
{
    /* data */
    int size;
    double value[MAX_COMPONENTS];
} Observation;

#endif
