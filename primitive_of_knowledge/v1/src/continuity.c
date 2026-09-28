#include <math.h>
#include "continuity.h"

Continuity continuity(TimelinePoint before, TimelinePoint after,
                      const Transformation *allowed, size_t count,
                      ContinuityPolicy policy)
{
    Continuity result = { .match = { .residual = INFINITY } };
    if (!isfinite(before.time) || !isfinite(after.time) ||
        after.time <= before.time ||
        !isfinite(policy.max_gap) || policy.max_gap <= 0) return result;
    result.elapsed = after.time - before.time;
    if (!isfinite(result.elapsed)) return result;
    result.match = invariance(before.observation, after.observation,
                              allowed, count, policy.epsilon);
    result.valid = result.match.valid;
    result.continuous = result.valid && result.elapsed <= policy.max_gap &&
                        result.match.matches > 0;
    return result;
}
