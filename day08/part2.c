/* Day 8, part 2 = 287040 */

#include "trees.h"

int main() {
    int width;
    int height;
    int **treeHeights = getTreeHeights(&width, &height);

    if (treeHeights) {
        int maxScenicScore = 0;

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                int treeHeight = treeHeights[y][x];
                int upDistance = 0;
                int downDistance = 0;
                int leftDistance = 0;
                int rightDistance = 0;

                // up
                for (int yCheck = y - 1; yCheck >= 0; yCheck--) {
                    ++upDistance;

                    if (treeHeights[yCheck][x] >= treeHeight) {
                        break;
                    }
                }

                // down
                for (int yCheck = y + 1; yCheck < height; yCheck++) {
                    ++downDistance;

                    if (treeHeights[yCheck][x] >= treeHeight) {
                        break;
                    }
                }

                // left
                for (int xCheck = x - 1; xCheck >= 0; xCheck--) {
                    ++leftDistance;

                    if (treeHeights[y][xCheck] >= treeHeight) {
                        break;
                    }
                }

                // right
                for (int xCheck = x + 1; xCheck < width; xCheck++) {
                    ++rightDistance;

                    if (treeHeights[y][xCheck] >= treeHeight) {
                        break;
                    }
                }

                int scenicScore = upDistance * downDistance * leftDistance * rightDistance;

                if (scenicScore > maxScenicScore) {
                    maxScenicScore = scenicScore;
                }
            }
        }

        for (int y = 0; y < height; y++) {
            free(treeHeights[y]);
        }

        free(treeHeights);

        printf("%d", maxScenicScore);
    }

    return 0;
}
