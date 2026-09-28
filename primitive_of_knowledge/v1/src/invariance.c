#include <math.h>
#include "invariance.h"

int observation_valid(Observation observation)
{
    if (observation.size < 1 || observation.size > MAX_COMPONENTS) return 0;
    for (int i = 0; i < observation.size; ++i)
        if (!isfinite(observation.value[i])) return 0;
    return 1;
}

Invariance invariance(Observation before, Observation after,
                      const Transformation *allowed, size_t count, double epsilon)
{
    Invariance invalid = { .residual = INFINITY };
    Invariance result = invalid;
    if (!observation_valid(before) || !observation_valid(after) ||
        before.size != after.size || allowed == NULL || count == 0 ||
        !isfinite(epsilon) || epsilon < 0) return invalid;
    for (size_t k = 0; k < count; ++k) {
        Observation transformed = {0};
        if (allowed[k].apply == NULL ||
            !allowed[k].apply(&before, &transformed, allowed[k].context) ||
            !observation_valid(transformed) || transformed.size != after.size)
            return invalid;
        double residual = 0;
        for (int i = 0; i < after.size; ++i)
            residual = hypot(residual, transformed.value[i] - after.value[i]);
        if (!isfinite(residual)) return invalid;
        if (k == 0 || residual < result.residual) {
            result.residual = residual;
            result.best_index = k;
        }
        if (residual <= epsilon) ++result.matches;
    }
    result.valid = 1;
    return result;
}
