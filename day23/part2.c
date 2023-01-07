/* Day 23, part 2 = 954 */

#include "grove.h"

int main() {
    struct GroveData *data = getGroveData();

    if (data) {
        int rounds = 0;

        do {
            ++rounds;
        } while (moveElves(data) > 0);

        freeGroveData(data);

        printf("%d", rounds);
    }

    return 0;
}
