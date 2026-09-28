#include "change.h"
#include "difference.h"

ChangeTimeline change(Timeline timeline)
{
    ChangeTimeline result;
    result.count = 0;

    if (timeline.count < 2 || timeline.count > MAX_COMPONENTS)
        return result;

    for (int i = 0; i + 1 < timeline.count; i++)
    {
        TimelinePoint current = timeline.points[i];
        TimelinePoint next = timeline.points[i + 1];

        if (next.time <= current.time)
            continue;

        ChangePoint c;
        c.from_time = current.time;
        c.to_time = next.time;
        c.differences = difference(current.observation, next.observation);

        result.items[result.count++] = c;
    }

    return result;
}
