/* Day 3, part 2 = 2650 */

#include <stdio.h>
#include <string.h>
#include "priority.h"

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char rucksack1[64];
        char rucksack2[64];
        char rucksack3[64];
        char *item;
        int prioritySum = 0;

        while (fgets(rucksack1, sizeof(rucksack1), inputFile) && 
               fgets(rucksack2, sizeof(rucksack2), inputFile) && 
               fgets(rucksack3, sizeof(rucksack3), inputFile)) {
            item = rucksack1;

            while (item) {
                if (strchr(rucksack2, *item) && strchr(rucksack3, *item)) {
                    prioritySum += priority(*item);
                    break;
                }

                ++item;
            }
        }

        fclose(inputFile);

        printf("%d", prioritySum);
    }

    return 0;
}
