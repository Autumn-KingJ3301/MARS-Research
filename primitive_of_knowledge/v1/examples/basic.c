#include <stdio.h>

#include "observation.h"
#include "difference.h"
#include "distinction.h"

int main(void)
{
    Observation x = {
        .size = 3,
        .value = {4.0, 8.0, 2.0}
    };

    Observation y = {
        .size = 3,
        .value = {4.0, 5.0, 2.0}
    };

    DifferenceSet delta = difference(x, y);

    printf("Difference count: %d\n", delta.count);

    for (int i = 0; i < delta.count; i++) {
        printf(
            "Index %d: %.2f != %.2f\n",
            delta.items[i].index,
            delta.items[i].x_value,
            delta.items[i].y_value
        );
    }

    double d = distance(x, y);
    double threshold = 2.0;

    printf("Distance: %.2f\n", d);

    printf(
        "Distinct: %s\n",
        is_distinct(x, y, threshold) ? "yes" : "no"
    );

    return 0;
}