#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GRID_SIZE 600

struct Position {
    int x;
    int y;
};

void moveHead(struct Position *head, char direction) {
    switch (direction) {
    case 'U':
        --head->y;
        break;
    case 'D':
        ++head->y;
        break;
    case 'L':
        --head->x;
        break;
    case 'R':
        ++head->x;
        break;
    }
}

void moveTail(struct Position *head, struct Position *tail) {
    int deltaX = head->x - tail->x;
    int deltaY = head->y - tail->y;

    if (abs(deltaX) > 1 || abs(deltaY) > 1) {
        if (deltaX < 0) {
            --tail->x;
        } else if (deltaX > 0) {
            ++tail->x;
        }

        if (deltaY < 0) {
            --tail->y;
        } else if (deltaY > 0) {
            ++tail->y;
        }
    }
}

int countTailPositions(int knotCount) {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        struct Position *rope = (struct Position *)calloc(knotCount, sizeof(struct Position));
        struct Position *tail = &rope[knotCount - 1];

        bool **grid = (bool **)malloc(GRID_SIZE * sizeof(bool *));

        for (int y = 0; y < GRID_SIZE; y++) {
            grid[y] = (bool *)calloc(GRID_SIZE, sizeof(bool));
        }

        int gridOffset = GRID_SIZE / 2;
        grid[gridOffset][gridOffset] = true;

        char direction;
        int distance;
        char nl;

        while (fscanf(inputFile, "%c %d%c", &direction, &distance, &nl) >= 2) {
            for (int i = 0; i < distance; i++) {
                moveHead(rope, direction);

                for (int j = 0; j < knotCount - 1; j++) {
                    moveTail(rope + j, rope + j + 1);
                }

                grid[tail->y + gridOffset][tail->x + gridOffset] = true;
            }
        }

        fclose(inputFile);

        int tailPositionCount = 0;

        for (int y = 0; y < GRID_SIZE; y++) {
            for (int x = 0; x < GRID_SIZE; x++) {
                if (grid[y][x]) {
                    ++tailPositionCount;
                }
            }

            free(grid[y]);
        }

        free(grid);
        free(rope);

        return tailPositionCount;
    }

    return 0;
}
