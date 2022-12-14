/* Day 14, part 2 = 27936 */

#include "cave.h"

int main() {
    struct Cave *cave = getCave(true);

    if (cave) {
        int grainCount = pourSand(cave);

        freeCave(cave);

        printf("%d", grainCount);
    }

    return 0;
}
