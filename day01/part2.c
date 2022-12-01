/* Day 1, part 2 = 195292 */

#include <stdio.h>
#include <string.h>

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char line[8];
        int elfCalories = 0;
        int calories = 0;
        int maxCalories[] = { 0, 0, 0 };

        while (fgets(line, sizeof(line), inputFile)) {
            if (strlen(line) == 1) {
                for (int i = 0; i < 3; i++) {
                    if (elfCalories > maxCalories[i]) {
                        maxCalories[i] = elfCalories;
                        break;
                    }
                }

                elfCalories = 0;
            } else {
                sscanf(line, "%d", &calories);

                elfCalories += calories;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (elfCalories > maxCalories[i]) {
                maxCalories[i] = elfCalories;
                break;
            }
        }

        fclose(inputFile);

        printf("%d", maxCalories[0] + maxCalories[1] + maxCalories[2]);
    }

    return 0;
}
