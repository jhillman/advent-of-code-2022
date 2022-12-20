/* Day 17, part 1 = 3206 */

#include "cavern.h"

int main() {
    struct Cavern *cavern = getCavern();

    if (cavern) {
        dropRocks(cavern, 2022);

        printf("%ld", cavern->top);

        freeCavern(cavern);
    }

    return 0;
}
