#ifndef DISTINCTION_H
#define DISTINCTION_H

#include "observation.h"

// Magnitude of difference delta
double distance(Observation x, Observation y);

int is_distinct(Observation x, Observation y, double threshold);

#endif

