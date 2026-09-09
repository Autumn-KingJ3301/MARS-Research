#include "difference.h"

DifferenceSet difference(Observation x, Observation y){
    // This assumes size of x = y
    DifferenceSet delta;
    delta.count = 0;

    for (int i = 0; i < x.size; i++)
    {
        /* code */
        if(x.value[i] != y.value[i]){
            delta.items[delta.count].index = i;
            delta.items[delta.count].x_value = x.value[i];
            delta.items[delta.count].y_value = y.value[i];
            delta.count++;
        }
    }
    
    return delta;
}

