#ifndef CONTINUITY_H
#define CONTINUITY_H

#include "change.h"
#include "invariance.h"

typedef struct {
    double epsilon;
    double max_gap;
} ContinuityPolicy;

typedef struct {
    int valid;
    int continuous;
    double elapsed;
    Invariance match;
} Continuity;

/* Pairwise sampled continuity, not mathematical continuity or identity proof.
 * Caller supplies transformations admissible for this interval. Motion or other
 * domain constraints belong in that choice, not inside this primitive. */
Continuity continuity(TimelinePoint before, TimelinePoint after,
                      const Transformation *allowed, size_t count,
                      ContinuityPolicy policy);

#endif
