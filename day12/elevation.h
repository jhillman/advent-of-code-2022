#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STEPS 10000000

struct Location {
    int x;
    int y;
    int steps;
};

struct ElevationData {
    int width;
    int height;

    struct Location start;
    struct Location end;

    char **values;
};

bool equal(struct Location a, struct Location b) {
    return a.x == b.x && a.y == b.y;
}

struct LocationQueue {
    struct Location *data;
    int capacity;
    int size;
};

void swap(struct Location *a, struct Location *b) {
    struct Location temp = *b;

    *b = *a;
    *a = temp;
}   

void heapify(struct LocationQueue *queue, int index) {
    if (queue->size > 1) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < queue->size && queue->data[left].steps < queue->data[smallest].steps) {
            smallest = left;
        }

        if (right < queue->size && queue->data[right].steps < queue->data[smallest].steps) {
            smallest = right;
        }

        if (smallest != index) {
            swap(&queue->data[index], &queue->data[smallest]);
            heapify(queue, smallest);
        }
    }
}

void enqueue(struct LocationQueue *queue, struct Location location) {
    if (queue->capacity == 0) {
        queue->capacity = 1000;
        queue->data = (struct Location *)malloc(queue->capacity * sizeof(struct Location));
    } else if (queue->size == queue->capacity) {
        queue->capacity += 1000;
        queue->data = (struct Location *)realloc(queue->data, queue->capacity * sizeof(struct Location));
    }

    queue->data[queue->size++] = location;

    for (int i = queue->size / 2 - 1; i >= 0; i--) {
        heapify(queue, i);
    }
}

struct Location dequeue(struct LocationQueue *queue) {
    struct Location location = *queue->data;

    --queue->size;

    memcpy(queue->data, queue->data + 1, queue->size * sizeof(struct Location));

    for (int i = queue->size / 2 - 1; i >= 0; i--) {
        heapify(queue, i);
    }

    return location;
}

void clear(struct LocationQueue *queue) {
    while(queue->size) {
        dequeue(queue);
    }    
}

int fewestSteps(struct ElevationData *data, struct Location start) {
    int **cumulativeSteps = (int **)malloc(data->height * sizeof(int *));

    for (int y = 0; y < data->height; y++) {
        cumulativeSteps[y] = (int *)calloc(data->width, sizeof(int));

        for (int x = 0; x < data->width; x++) {
            cumulativeSteps[y][x] = MAX_STEPS;
        }
    }

    struct LocationQueue *queue = (struct LocationQueue *)calloc(1, sizeof(struct Location *));

    int xDeltas[] = {-1, 0, 1, 0};
    int yDeltas[] = {0, 1, 0, -1};

    enqueue(queue, start);

    cumulativeSteps[start.y][start.x] = 0;

    while (queue->size) {
        struct Location location = dequeue(queue);

        if (equal(location, data->end)) {
            break;
        }

        for (int i = 0; i < 4; i++) {
            int x = location.x + xDeltas[i];
            int y = location.y + yDeltas[i];

            if (!(x >= 0 && x < data->width && y >= 0 && y < data->height)) {
                continue;
            }

            if (data->values[y][x] - data->values[location.y][location.x] <= 1) {
                int steps = cumulativeSteps[location.y][location.x] + 1;

                if (cumulativeSteps[y][x] > steps) {
                    cumulativeSteps[y][x] = steps;

                    enqueue(queue, (struct Location){ x, y, steps });
                }
            }
        }
    }

    int steps = cumulativeSteps[data->end.y][data->end.x];

    for (int y = 0; y < data->height; y++) {
        // for (int x = 0; x < data->width; x++) {
        //     printf("%4d", cumulativeSteps[y][x]);
        // }

        // printf("\n");

        free(cumulativeSteps[y]);
    }

    free(cumulativeSteps);

    free(queue->data);
    free(queue);

    return steps;
}

struct ElevationData *getElevationData() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        struct ElevationData *data = (struct ElevationData *)calloc(1, sizeof(struct ElevationData));

        char c = fgetc(inputFile);

        while (!feof(inputFile)) {
            if (c == '\n') {
                ++data->height;
            }

            if (!data->height) {
                ++data->width;
            }

            c = fgetc(inputFile);
        }

        ++data->height;

        fseek(inputFile, 0, SEEK_SET);

        data->values = (char **)calloc(data->height, sizeof(char *));

        for (int y = 0; y < data->height; y++) {
            data->values[y] = (char *)calloc(data->width, sizeof(char));

            for (int x = 0; x < data->width; x++) {
                char elevation = fgetc(inputFile);
                
                if (elevation == 'S') {
                    data->start = (struct Location){ x, y, 0 };
                    data->values[y][x] = 'z';
                } else if (elevation == 'E') {
                    data->end = (struct Location){ x, y, 0 };
                    data->values[y][x] = 'z';
                } else {
                    data->values[y][x] = elevation;
                }
            }

            fgetc(inputFile);
        }

        fclose(inputFile);

        return data;
    }

    return NULL;
}

void freeElevationData(struct ElevationData *data) {
    for (int y = 0; y < data->height; y++) {
        free(data->values[y]);
    }

    free(data->values);
    free(data);
}
