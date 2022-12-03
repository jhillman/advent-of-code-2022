/* Day 3, part 1 = 7428 */

#include <stdio.h>
#include <string.h>
#include "priority.h"

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char rucksack[64];
        char compartment1[32];
        char compartment2[32];
        char *item;
        int prioritySum = 0;

        while (fgets(rucksack, sizeof(rucksack), inputFile)) {
            int compartmentSize = strlen(rucksack) / 2;
            *compartment1 = *compartment2 = '\0';

            strncat(compartment1, rucksack, compartmentSize);
            strncat(compartment2, rucksack + compartmentSize, compartmentSize);

            item = compartment1;

            while (item) {
                if (strchr(compartment2, *item)) {
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
