/* Day 3, part 1 = 7428 */

#include <stdio.h>
#include <string.h>
#include "priority.h"

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char rucksack[64];
        char pocket1[32];
        char pocket2[32];
        char *item;
        int prioritySum = 0;

        while (fgets(rucksack, sizeof(rucksack), inputFile)) {
            int pocketSize = strlen(rucksack) / 2;
            *pocket1 = *pocket2 = '\0';

            strncat(pocket1, rucksack, pocketSize);
            strncat(pocket2, rucksack + pocketSize, pocketSize);

            item = pocket1;

            while (item) {
                if (strchr(pocket2, *item)) {
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
