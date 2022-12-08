/* Day 8, part 1 = 1695 */

#include "trees.h"
#include <stdbool.h>

int main() {
    int width;
    int height;
    int **treeHeights = getTreeHeights(&width, &height);

    if (treeHeights) {
        int visible = width * 2 + (height - 2) * 2;

        for (int y = 1; y < height - 1; y++) {
            for (int x = 1; x < width - 1; x++) {
                int treeHeight = treeHeights[y][x];
                bool treeVisible = false;

                // up
                for (int yCheck = y - 1; yCheck >= 0; yCheck--) {
                    if (treeHeights[yCheck][x] >= treeHeight) {
                        break;
                    }

                    if (yCheck == 0) {
                        treeVisible = true;
                    }
                }

                // down
                for (int yCheck = y + 1; !treeVisible && yCheck < height; yCheck++) {
                    if (treeHeights[yCheck][x] >= treeHeight) {
                        break;
                    }

                    if (yCheck == height - 1) {
                        treeVisible = true;
                    }
                }

                // left
                for (int xCheck = x - 1; !treeVisible && xCheck >= 0; xCheck--) {
                    if (treeHeights[y][xCheck] >= treeHeight) {
                        break;
                    }

                    if (xCheck == 0) {
                        treeVisible = true;
                    }
                }

                // right
                for (int xCheck = x + 1; !treeVisible && xCheck < width; xCheck++) {
                    if (treeHeights[y][xCheck] >= treeHeight) {
                        break;
                    }

                    if (xCheck == width - 1) {
                        treeVisible = true;
                    }
                }

                if (treeVisible) {
                    ++visible;
                }
            }
        }

        for (int y = 0; y < height; y++) {
            free(treeHeights[y]);
        }

        free(treeHeights);

        printf("%d", visible);
    }

    return 0;
}
