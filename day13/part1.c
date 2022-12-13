/* Day 13, part 1 = 5825 */

#include "packets.h"

int main() {
    int packetCount;
    struct ListItem *packets = getPackets(&packetCount);

    if (packets) {
        int indicesSum = 0;
        int index = 0;

        for (int i = 0; i < packetCount; i += 2) {
            ++index;

            if (compare(packets[i], packets[i + 1]) == LEFT) {
                indicesSum += index;
            }
        }

        freeList(packets);

        printf("%d", indicesSum);
    }

    return 0;
}
