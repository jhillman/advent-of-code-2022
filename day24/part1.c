/* Day 24, part 1 = 288 */

#include "valley.h"

int main() {
    struct ValleyData *data = getValleyData();

    if (data) {
        int minutes = fewestMinutes(data, 0, data->start, data->end);

        freeValleyData(data);

        printf("%d", minutes);
    }

    return 0;
}
