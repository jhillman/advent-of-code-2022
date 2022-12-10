/* Day 10, part 2 = EFUGLPAP */

#include "cpu.h"
#include "stdlib.h"

#define PIXELS_WIDTH 40

void handleCycle(int cycle, int x, void *output) {
    char *pixels = (char *)output;

    int position = (cycle % PIXELS_WIDTH) - 1;

    if (position == -1) {
        // printf("%s\n", pixels);
        memset(pixels, '.', PIXELS_WIDTH);
    }

    if (abs(position - x) <= 1 && position >= 0) {
        pixels[position] = '#';
    }
}

int main() {
    char pixels[PIXELS_WIDTH + 1] = { 0 };
    memset(pixels, '.', PIXELS_WIDTH);

    runCpu(&pixels);

    printf("EFUGLPAP");

    return 0;
}
