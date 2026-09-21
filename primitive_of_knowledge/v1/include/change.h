#ifndef CHANGE_H
#define CHANGE_H

#include "observation.h"
#include "difference.h"

typedef struct TimelinePoint{
    double time;
    Observation observation;
} TimelinePoint;

typedef struct Timeline{
    int count;
    TimelinePoint points[MAX_COMPONENTS];
} Timeline;

typedef struct ChangePoint
{
   double from_time;
   double to_time;
   DifferenceSet differences;
} ChangePoint;

typedef struct ChangeTimeline
{
    int count;
    ChangePoint items[MAX_COMPONENTS - 1];
} ChangeTimeline;

#endif