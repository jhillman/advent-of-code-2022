/* Day 11, part 1 = 67830 */

#include "monkeys.h"

int main() {
    int monkeyCount;
    struct Monkey *monkeys = getMonkeys(&monkeyCount);

    if (monkeys) {
        printf("%ld", monkeyBusiness(monkeys, monkeyCount, 20, ONE));

        freeMonkeys(monkeys, monkeyCount);
    }

    return 0;
}
