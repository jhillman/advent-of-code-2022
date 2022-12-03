/* Day 1, part 1 = 66306 */

#include "elves.h"

int main() {
    int *elfCalories = readElfCalories();

    if (elfCalories) {
        printf("%d", *elfCalories);

        free(elfCalories);
    }

    return 0;
}
