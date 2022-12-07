/* Day 7, part 1 = 1517599 */

#include "filesystem.h"

void sumDirectoriesUnderLimit(struct Directory *directory, int limit, int *sum) {
    if (directory->totalSize <= limit) {
        *sum += directory->totalSize;
    }

    for (int i = 0; i < directory->directoryCount; i++) {
        sumDirectoriesUnderLimit(directory->directories[i], limit, sum);
    }
}

int main() {
    struct Directory *root = getRoot();

    if (root) {
        int sum = 0;
        sumDirectoriesUnderLimit(root, 100000, &sum);
        freeDirectory(root);

        printf("%d", sum);
    }

    return 0;
}
