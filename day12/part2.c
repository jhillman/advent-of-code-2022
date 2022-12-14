/* Day 12, part 2 = 388 */

#include "elevation.h"

int main() {
    struct ElevationData *data = getElevationData();

    if (data) {
        struct Location *starts = NULL;
        int startCount = 0;

        for (int y = 0; y < data->height; y++) {
            for (int x = 0; x < data->width; x++) {
                if (data->values[y][x] == 'a') {
                    ++startCount;

                    if (starts) {
                        starts = (struct Location *)realloc(starts, (startCount + 1) * sizeof(struct Location));
                    } else {
                        starts = (struct Location *)malloc((startCount + 1) * sizeof(struct Location));
                    }

                    starts[startCount++] = (struct Location){ x, y, 0 };
                }
            }
        }

        int steps = fewestSteps(data, data->end, starts, startCount, false);

        free(starts);
        freeElevationData(data);

        printf("%d", steps);
    }

    return 0;
}
