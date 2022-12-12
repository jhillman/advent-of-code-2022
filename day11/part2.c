/* Day 11, part 2 = 15305381442 */

#include "monkeys.h"

int main() {
    int monkeyCount;
    struct Monkey *monkeys = getMonkeys(&monkeyCount);

    if (monkeys) {
        printf("%ld", monkeyBusiness(monkeys, monkeyCount, 10000, TWO));

        freeMonkeys(monkeys, monkeyCount);
    }

    return 0;
}
