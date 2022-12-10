/* Day 10, part 1 = 15020 */

#include "cpu.h"

void handleCycle(int cycle, int x, void *output) {
    int *signalStrenthSum = (int *)output;

    switch (cycle) {
    case 20:
    case 60:
    case 100:
    case 140:
    case 180:
    case 220:
        *signalStrenthSum += cycle * x;
        break;
    }
}

int main() {
    int signalStrenthSum = 0;

    runCpu(&signalStrenthSum);

    printf("%d", signalStrenthSum);

    return 0;
}
