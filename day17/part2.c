/* Day 17, part 1 = 1602881844347 */

#include "tunnel.h"

int main() {
    struct Tunnel *tunnel = getTunnel();

    if (tunnel) {
        long targetRockCount = 1000000000000;
        int tunnelStateCapacity = 1000;
        struct TunnelState *tunnelStates = (struct TunnelState *)malloc(tunnelStateCapacity * sizeof(struct TunnelState));
        int tunnelStateCount = 0;
        int tunnelStateIndex;
        int maxTops[TUNNEL_WIDTH] = { 0 };

        while (tunnel->rockCount < targetRockCount) {
            dropRocks(tunnel, 1);

            struct TunnelState tunnelState = { tunnel->top, tunnel->rockCount, tunnel->rockType, tunnel->gustIndex };

            for (int i = tunnel->rock.bottom; i <= tunnel->top; i++) {
                for (int j = 0; j < TUNNEL_WIDTH; j++) {
                    if (tunnel->tunnel[i] & (1 << (TUNNEL_WIDTH - j - 1))) {
                        maxTops[j] = i + 1;
                    }
                }
            }

            for (int i = 0; i < TUNNEL_WIDTH; i++) {
                tunnelState.relativeHeights[i] = maxTops[i] - *maxTops;
            }

            if ((tunnelStateIndex = binarySearchStates(tunnelState, tunnelStates, 0, tunnelStateCount - 1)) != -1) {
                long patternHeight = tunnel->top - tunnelStates[tunnelStateIndex].tunnelTop;
                long patternRockCount = tunnel->rockCount - tunnelStates[tunnelStateIndex].rockCount;
                long patternCycles = (targetRockCount - tunnelStates[tunnelStateIndex].rockCount) / patternRockCount;
                long remainingRocks = (targetRockCount - tunnelStates[tunnelStateIndex].rockCount) - (patternCycles * patternRockCount);

                dropRocks(tunnel, remainingRocks);

                printf("%ld", tunnel->top + ((patternCycles - 1) * patternHeight));

                tunnel->rockCount = targetRockCount;
            } else {
                tunnelStates[tunnelStateCount++] = tunnelState;
                qsort(tunnelStates, tunnelStateCount, sizeof(struct TunnelState), compare);
            }

            if (tunnelStateCount == tunnelStateCapacity) {
                tunnelStateCapacity += 1000;

                tunnelStates = (struct TunnelState *)realloc(tunnelStates, tunnelStateCapacity * sizeof(struct TunnelState));
            }
        }

        freeTunnel(tunnel);
    }

    return 0;
}
