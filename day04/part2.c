/* Day 4, part 2 = 779 */

#include "sectionrange.h"

bool testSectionRanges(struct SectionRange sectionRange1, struct SectionRange sectionRange2) {
    return sectionRange1.min >= sectionRange2.min && sectionRange1.min <= sectionRange2.max ||
           sectionRange2.min >= sectionRange1.min && sectionRange2.min <= sectionRange1.max;
}

int main() {
    printf("%d", checkSectionAssignments());

    return 0;
}
