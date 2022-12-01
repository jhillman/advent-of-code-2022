/* Day 1, part 1 = 66306 */

#include <stdio.h>
#include <string.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char line[8];
        int elfCalories = 0;
        int calories = 0;
        int maxCalories = 0;

        while (fgets(line, sizeof(line), inputFile)) {
            if (strlen(line) == 1) {
                if (elfCalories > maxCalories) {
                    maxCalories = elfCalories;
                }

                elfCalories = 0;
            } else {
                sscanf(line, "%d", &calories);

                elfCalories += calories;
            }
        }

        if (elfCalories > maxCalories) {
            maxCalories = elfCalories;
        }

        fclose(inputFile);

        printf("%d", maxCalories);
    }

    return 0;
}
