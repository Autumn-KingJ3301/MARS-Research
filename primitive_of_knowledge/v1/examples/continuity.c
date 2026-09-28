#include <stdio.h>
#include "continuity.h"
#include "distinction.h"

/* Example-only transformation: preserve relative values under a common offset.
 * Replace this callback with transformations appropriate to your research. */
static int offset(const Observation *source, Observation *result, const void *context)
{
    *result = *source;
    for (int i = 0; i < result->size; ++i)
        result->value[i] += *(const double *)context;
    return 1;
}

int main(void)
{
    double offsets[] = {0, 1};
    Transformation allowed[] = {{offset, &offsets[0]}, {offset, &offsets[1]}};
    TimelinePoint before = {.time = 0, .observation = {.size = 3, .value = {1, 3, 5}}};
    TimelinePoint after = {.time = 1, .observation = {.size = 3, .value = {2, 4, 6}}};
    ContinuityPolicy policy = {.epsilon = 0.01, .max_gap = 1};
    Continuity link = continuity(before, after, allowed, 2, policy);
    printf("Raw difference: %.3f\n", distance(before.observation, after.observation));
    printf("Match under supplied transformations: %s; residual: %.3f\n",
           link.match.matches ? "yes" : "no", link.match.residual);
    printf("Continuity within time limit: %s\n", link.continuous ? "yes" : "no");
    after.time = 3;
    link = continuity(before, after, allowed, 2, policy);
    printf("Same match after excessive gap: %s\n", link.continuous ? "yes" : "no");
    return 0;
}
