#ifndef INVARIANCE_H
#define INVARIANCE_H

#include <stddef.h>
#include "observation.h"

/* Return nonzero on success. Implementations must respect MAX_COMPONENTS.
 * Context is caller-owned and can describe any transformation parameters. */
typedef int (*TransformFunction)(const Observation *source,
                                 Observation *result, const void *context);
typedef struct {
    TransformFunction apply;
    const void *context;
} Transformation;

typedef struct {
    int valid;
    size_t matches;     /* Number of candidates with residual <= epsilon. */
    size_t best_index;  /* Index in supplied candidates; meaningful if valid. */
    double residual;
} Invariance;

int observation_valid(Observation observation);
/* Compares after with transformed versions of before using Euclidean distance.
 * No transformation, including identity, is implicitly supplied.
 * Invalid input or any failed transformation invalidates the whole comparison. */
Invariance invariance(Observation before, Observation after,
                      const Transformation *allowed, size_t count, double epsilon);

#endif
