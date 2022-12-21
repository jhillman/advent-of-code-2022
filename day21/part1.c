/* Day 21, part 1 = 194058098264286 */

#include "monkeys.h"

int main() {
    int monkeyCount;
    struct Monkey *monkeys = getMonkeys(&monkeyCount, NULL);

    if (monkeys) {
        playGame(monkeys, monkeyCount);

        long rootNumber = *findMonkey("root", monkeys, monkeyCount)->number;

        freeMonkeys(monkeys, monkeyCount);

        printf("%ld", rootNumber);
    }

    return 0;
}
