#include <stdio.h>
#include <math.h>
#include "observation.h"

double euclidean_distance(Observation x, Observation y)
{
     double sum = 0.0;

    for (int i = 0; i < x.size; i++) {
        double diff = x.value[i] - y.value[i];
        sum += diff * diff;
    }

    return sqrt(sum);
}

double distance(Observation x, Observation y)
{
    return euclidean_distance(x, y);
}

int is_distinct(Observation x, Observation y, double threshold)
{
    return distance(x, y) > threshold;
}