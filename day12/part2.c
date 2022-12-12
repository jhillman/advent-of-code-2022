/* Day 12, part 2 = 388 */

#include "elevation.h"

int main() {
    struct ElevationData *data = getElevationData();

    if (data) {
        int pathSteps = MAX_STEPS;

        for (int y = 0; y < data->height; y++) {
            for (int x = 0; x < data->width; x++) {
                if (data->values[y][x] == 'a') {
                    int steps = fewestSteps(data, (struct Location){ x, y, 0 });

                    if (steps < pathSteps) {
                        pathSteps = steps;
                    }
                }
            }
        }

        freeElevationData(data);

        printf("%d", pathSteps);
    }

    return 0;
}
