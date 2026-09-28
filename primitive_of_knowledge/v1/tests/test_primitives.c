#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "continuity.h"

static int offset(const Observation *source, Observation *result, const void *context)
{
    *result = *source;
    for (int i = 0; i < result->size; ++i)
        result->value[i] += *(const double *)context;
    return 1;
}

static int failed(const Observation *source, Observation *result, const void *context)
{
    (void)source; (void)result; (void)context;
    return 0;
}

int main(void)
{
    double zero = 0, one = 1;
    Transformation allowed[] = {{offset, &zero}, {offset, &one}};
    Observation a = {.size = 3, .value = {1, 3, 5}};
    Observation b = {.size = 3, .value = {2, 4, 6}};
    Invariance match = invariance(a, b, allowed, 2, 0);
    assert(match.valid && match.matches == 1 && match.best_index == 1 && match.residual == 0);
    assert(invariance(a, b, allowed, 1, 0).matches == 0);
    b.value[2] += 0.5;
    assert(invariance(a, b, allowed, 2, 0.5).matches == 1);
    assert(invariance(a, b, allowed, 2, 0.49).matches == 0);
    assert(invariance(a, a, allowed, 2, 2).matches == 2); /* Ambiguity retained. */
    assert(!invariance(a, b, NULL, 0, 0).valid);
    assert(!invariance(a, b, allowed, 2, -1).valid);
    assert(!invariance(a, b, allowed, 2, NAN).valid);
    Transformation broken[] = {{offset, &zero}, {failed, NULL}};
    assert(!invariance(a, a, broken, 2, 0).valid);
    b.size = 2;
    assert(!invariance(a, b, allowed, 2, 0).valid);
    b = a; b.value[0] = INFINITY;
    assert(!invariance(a, b, allowed, 2, 0).valid);
    b = a; b.size = MAX_COMPONENTS + 1;
    assert(!invariance(a, b, allowed, 2, 0).valid);
    b.size = 0;
    assert(!invariance(a, b, allowed, 2, 0).valid);

    TimelinePoint first = {.time = 0, .observation = a};
    TimelinePoint next = {.time = 1, .observation = a};
    ContinuityPolicy policy = {.epsilon = 0, .max_gap = 1};
    assert(continuity(first, next, allowed, 2, policy).continuous);
    next.time = 2;
    Continuity gap = continuity(first, next, allowed, 2, policy);
    assert(gap.valid && !gap.continuous && gap.match.matches == 1);
    next.time = 0;
    assert(!continuity(first, next, allowed, 2, policy).valid);
    next.time = -1;
    assert(!continuity(first, next, allowed, 2, policy).valid);
    next.time = NAN;
    assert(!continuity(first, next, allowed, 2, policy).valid);
    next.time = 1; next.observation.value[2] += 3;
    assert(!continuity(first, next, allowed, 2, policy).continuous);
    policy.max_gap = 0;
    assert(!continuity(first, next, allowed, 2, policy).valid);

    Timeline timeline = {0};
    assert(change(timeline).count == 0);
    timeline.count = 1; timeline.points[0] = first;
    assert(change(timeline).count == 0);
    timeline.count = MAX_COMPONENTS;
    for (int i = 0; i < timeline.count; ++i) {
        timeline.points[i].time = i;
        timeline.points[i].observation = a;
    }
    assert(change(timeline).count == MAX_COMPONENTS - 1);
    puts("All primitive tests passed.");
    return 0;
}
