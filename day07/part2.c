/* Day 7, part 2 = 2481982 */

#include "filesystem.h"

void sizeBestDirectory(struct Directory *directory, int minDirectorySize, int *size) {
    if (directory->totalSize >= minDirectorySize && directory->totalSize < *size) {
        *size = directory->totalSize;
    }

    for (int i = 0; i < directory->directoryCount; i++) {
        sizeBestDirectory(directory->directories[i], minDirectorySize, size);
    }
}

int main() {
    struct Directory *root = getRoot();

    if (root) {
        int totalSpace = 70000000;
        int updateSpace = 30000000;
        int availableSpace = totalSpace - root->totalSize;
        int minDirectorySize = updateSpace - availableSpace;

        int size = root->totalSize;
        sizeBestDirectory(root, minDirectorySize, &size);
        freeDirectory(root);

        printf("%d", size);
    }

    return 0;
}
