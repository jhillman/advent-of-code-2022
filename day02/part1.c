/* Day 2, part 1 = 13052 */

#include <stdio.h>
#include "moves.h"

int main() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        char opponentMove;
        char myMove;
        int score = 0;

        while (fscanf(inputFile, "%c %c\n", &opponentMove, &myMove) == 2) {
            score += moveScore(myMove, 'X');
            score += (myMove == winningMove(opponentMove, 'X') ? 6 : (myMove == sameMove(opponentMove, 'X') ? 3 : 0));
        }

        fclose(inputFile);

        printf("%d", score);
    }

    return 0;
}
