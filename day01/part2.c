/* Day 1, part 2 = 195292 */

#include "elfs.h"

int main() {
    int *elfCalories = readElfCalories();

    if (elfCalories) {
        printf("%d", elfCalories[0] + elfCalories[1] + elfCalories[2]);

        free(elfCalories);
    }

    return 0;
}