/* Day 24, part 2 = 861 */

#include "valley.h"

int main() {
    struct ValleyData *data = getValleyData();

    if (data) {
        int firstTrip = fewestMinutes(data, 0, data->start, data->end);
        int secondTrip = fewestMinutes(data, firstTrip, data->end, data->start);
        int thirdTrip = fewestMinutes(data, firstTrip + secondTrip, data->start, data->end);

        freeValleyData(data);

        printf("%d", firstTrip + secondTrip + thirdTrip);
    }

    return 0;
}
