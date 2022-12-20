/* Day 16, part 1 = 2114 */

#include "valves.h"

int main() {
    struct ValveData *data = getValveData();

    if (data) {
        struct ValveName one = { "AA", 'A', 'A' };
        bool flowingValves[26][26] = { false };
        int maxPressure = findMaxPressure(one, 30, flowingValves, data->valves, data->flowingValveNames, data->flowingValveCount, data->distances, 0, 0);

        freeValveData(data);

        printf("%d", maxPressure);
    }

    return 0;
}
