/* Day 12, part 1 = 394 */

#include "elevation.h"

int main() {
    struct ElevationData *data = getElevationData();

    if (data) {
        int steps = fewestSteps(data, data->start);

        freeElevationData(data);

        printf("%d", steps);
    }

    return 0;
}
