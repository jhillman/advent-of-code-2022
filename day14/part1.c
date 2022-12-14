/* Day 14, part 1 = 1068 */

#include "cave.h"

int main() {
    struct Cave *cave = getCave(false);

    if (cave) {
        int grainCount = pourSand(cave);

        freeCave(cave);

        printf("%d", grainCount);
    }

    return 0;
}
