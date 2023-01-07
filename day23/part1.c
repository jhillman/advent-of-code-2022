/* Day 23, part 1 = 3766 */

#include "grove.h"

int main() {
    struct GroveData *data = getGroveData();

    if (data) {
        for (int i = 0; i < 10; i++) {
            moveElves(data);
        }

        int freeSpace = 0;

        for (int y = data->minElfY; y <= data->maxElfY; y++) {
            for (int x = data->minElfX; x <= data->maxElfX; x++) {
                if (data->grove[y][x] == '.') {
                    ++freeSpace;
                }
            }
        }

        freeGroveData(data);

        printf("%d", freeSpace);
    }

    return 0;
}
