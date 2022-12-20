/* Day 17, part 1 = 3206 */

#include "tunnel.h"

int main() {
    struct Tunnel *tunnel = getTunnel();

    if (tunnel) {
        dropRocks(tunnel, 2022);

        printf("%ld", tunnel->top);

        freeTunnel(tunnel);
    }

    return 0;
}
