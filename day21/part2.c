/* Day 21, part 2 = 3592056845086 */

#include "monkeys.h"

int main() {
    int monkeyCount;
    struct Monkey *monkeys = getMonkeys(&monkeyCount, "humn");

    if (monkeys) {
        findMonkey("root", monkeys, monkeyCount)->operation.operator = '=';

        playGame(monkeys, monkeyCount);

        char *currentMonkeyName = findMonkey("root", monkeys, monkeyCount)->name;
        char *leftMonkeyName;
        char *rightMonkeyName;
        long humanNumber = 0;

        while (strcmp(currentMonkeyName, "humn") != 0) {
            struct Monkey *monkey = findMonkey(currentMonkeyName, monkeys, monkeyCount);
            leftMonkeyName = monkey->operation.leftMonkeyName;
            rightMonkeyName = monkey->operation.rightMonkeyName;

            struct Monkey *leftMonkey = findMonkey(leftMonkeyName, monkeys, monkeyCount);
            struct Monkey *rightMonkey = findMonkey(rightMonkeyName, monkeys, monkeyCount);

            switch (monkey->operation.operator) {
            case '=':
                if (leftMonkey && leftMonkey->number) {
                    humanNumber = *leftMonkey->number;
                    currentMonkeyName = rightMonkeyName;
                } else if (rightMonkey && rightMonkey->number) {
                    humanNumber = *rightMonkey->number;
                    currentMonkeyName = leftMonkeyName;
                }
                break;
            case '+':
                if (leftMonkey && leftMonkey->number) {
                    humanNumber = humanNumber - *leftMonkey->number;
                    currentMonkeyName = rightMonkeyName;
                } else if (rightMonkey && rightMonkey->number) {
                    humanNumber = humanNumber - *rightMonkey->number;
                    currentMonkeyName = leftMonkeyName;
                }
                break;
            case '-':
                if (leftMonkey && leftMonkey->number) {
                    humanNumber = *leftMonkey->number - humanNumber;
                    currentMonkeyName = rightMonkeyName;
                } else if (rightMonkey && rightMonkey->number) {
                    humanNumber = humanNumber + *rightMonkey->number;
                    currentMonkeyName = leftMonkeyName;
                }
                break;
            case '*':
                if (leftMonkey && leftMonkey->number) {
                    humanNumber = humanNumber / *leftMonkey->number;
                    currentMonkeyName = rightMonkeyName;
                } else if (rightMonkey && rightMonkey->number) {
                    humanNumber = humanNumber / *rightMonkey->number;
                    currentMonkeyName = leftMonkeyName;
                }
                break;
            case '/':
                if (leftMonkey && leftMonkey->number) {
                    humanNumber = *leftMonkey->number / humanNumber;
                    currentMonkeyName = rightMonkeyName;
                } else if (rightMonkey && rightMonkey->number) {
                    humanNumber = humanNumber * *rightMonkey->number;
                    currentMonkeyName = leftMonkeyName;
                }
                break;
            }
        }

        freeMonkeys(monkeys, monkeyCount);

        printf("%ld", humanNumber);
    }

    return 0;
}
