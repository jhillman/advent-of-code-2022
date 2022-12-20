/* Day 17, part 1 = 1602881844347 */

#include "cavern.h"

int main() {
    struct Cavern *cavern = getCavern();

    if (cavern) {
        long targetRockCount = 1000000000000;
        int cavernStateCapacity = 1000;
        struct CavernState *cavernStates = (struct CavernState *)malloc(cavernStateCapacity * sizeof(struct CavernState));
        int cavernStateCount = 0;
        int cavernStateIndex;
        int maxTops[CAVERN_WIDTH] = { 0 };

        while (cavern->rockCount < targetRockCount) {
            dropRocks(cavern, 1);

            struct CavernState cavernState = { cavern->top, cavern->rockCount, cavern->gustIndex };

            for (int i = cavern->rock.bottom; i <= cavern->top; i++) {
                for (int j = 0; j < CAVERN_WIDTH; j++) {
                    if (cavern->cavern[i] & (1 << (CAVERN_WIDTH - j - 1))) {
                        maxTops[j] = i + 1;
                    }
                }
            }

            for (int i = 0; i < CAVERN_WIDTH; i++) {
                cavernState.relativeHeights[i] = maxTops[i] - *maxTops;
            }

            if ((cavernStateIndex = binarySearchStates(cavernState, cavernStates, 0, cavernStateCount - 1)) != -1) {
                long patternHeight = cavern->top - cavernStates[cavernStateIndex].cavernTop;
                long patternRockCount = cavern->rockCount - cavernStates[cavernStateIndex].rockCount;
                long patternCycles = (targetRockCount - cavernStates[cavernStateIndex].rockCount) / patternRockCount;
                long remainingRocks = (targetRockCount - cavernStates[cavernStateIndex].rockCount) - (patternCycles * patternRockCount);

                dropRocks(cavern, remainingRocks);

                printf("%ld", cavern->top + ((patternCycles - 1) * patternHeight));

                cavern->rockCount = targetRockCount;
            } else {
                cavernStates[cavernStateCount++] = cavernState;
                qsort(cavernStates, cavernStateCount, sizeof(struct CavernState), compare);
            }

            if (cavernStateCount == cavernStateCapacity) {
                cavernStateCapacity += 1000;

                cavernStates = (struct CavernState *)realloc(cavernStates, cavernStateCapacity * sizeof(struct CavernState));
            }
        }

        freeCavern(cavern);
    }

    return 0;
}
