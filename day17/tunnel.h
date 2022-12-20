#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define min(a,b) ((a) < (b) ? (a) : (b))
#define max(a,b) ((a) > (b) ? (a) : (b))

#define TUNNEL_WIDTH 7

enum RockType {
    MINUS,
    PLUS,
    SHELF,
    LINE,
    BLOCK
};

struct Rock {
    int *state;
    int rowCount;
    long top;
    long left;
    long right;
    long bottom;
};

struct Tunnel {
    FILE *inputFile;
    int *tunnel;
    long tunnelHeight;
    long top;
    enum RockType rockType;
    struct Rock rock;
    int gustIndex;
    long rockCount;
};

int bitCount(int number) {
    int count = 0;
    
    for (int i = 0; i < TUNNEL_WIDTH; i++) {
        if (number & (1 << i)) {
            ++count;
        }
    }

    return count;
}

struct Rock addRock(struct Tunnel *tunnel) {
    int *state;

    switch (tunnel->rockType) {
    case MINUS:
        state = (int *)malloc(1 * sizeof(int));
        state[0] = tunnel->tunnel[tunnel->top + 3] = 0b0011110;

        return (struct Rock){
            state,
            1,
            tunnel->top + 3,
            2, 5,
            tunnel->top + 3
        };
    case PLUS:
        state = (int *)malloc(3 * sizeof(int));
        state[2] = tunnel->tunnel[tunnel->top + 5] = 0b0001000;
        state[1] = tunnel->tunnel[tunnel->top + 4] = 0b0011100;
        state[0] = tunnel->tunnel[tunnel->top + 3] = 0b0001000;

        return (struct Rock){
            state,
            3,
            tunnel->top + 5,
            2, 4,
            tunnel->top + 3
        };
    case SHELF:
        state = (int *)malloc(3 * sizeof(int));
        state[2] = tunnel->tunnel[tunnel->top + 5] = 0b0000100;
        state[1] = tunnel->tunnel[tunnel->top + 4] = 0b0000100;
        state[0] = tunnel->tunnel[tunnel->top + 3] = 0b0011100;

        return (struct Rock){
            state,
            3,
            tunnel->top + 5,
            2, 4,
            tunnel->top + 3
        };
    case LINE:
        state = (int *)malloc(4 * sizeof(int));
        state[3] = tunnel->tunnel[tunnel->top + 6] = 0b0010000;
        state[2] = tunnel->tunnel[tunnel->top + 5] = 0b0010000;
        state[1] = tunnel->tunnel[tunnel->top + 4] = 0b0010000;
        state[0] = tunnel->tunnel[tunnel->top + 3] = 0b0010000;

        return (struct Rock){
            state,
            4,
            tunnel->top + 6,
            2, 2,
            tunnel->top + 3
        };
    case BLOCK:
        state = (int *)malloc(2 * sizeof(int));
        state[1] = tunnel->tunnel[tunnel->top + 4] = 0b0011000;
        state[0] = tunnel->tunnel[tunnel->top + 3] = 0b0011000;

        return (struct Rock){
            state,
            2,
            tunnel->top + 4,
            2, 3,
            tunnel->top + 3
        };
        break;
    }
}

void printTunnel(struct Tunnel *tunnel) {
    for (int i = tunnel->top; i >= 0; i--) {
        printf("|");

        for (int j = TUNNEL_WIDTH - 1; j >= 0; j--) {
            if ((1 << j) & tunnel->tunnel[i]) {
                printf("#");
            } else {
                printf(".");
            }
        }

        printf("|\n");
    }

    printf("+");

    for (int i = 0; i < TUNNEL_WIDTH; i++) {
        printf("-");
    }

    printf("+\n");
}

void tryMoveLeft(struct Rock *rock, struct Tunnel *tunnel) {
    bool canMove = rock->left > 0;

    if (canMove && rock->bottom <= tunnel->top) {
        for (int i = 0; canMove && i < rock->rowCount; i++) {
            if (rock->bottom + i - 1 <= tunnel->top) {
                canMove = bitCount(tunnel->tunnel[rock->bottom + i]) == 
                    bitCount((tunnel->tunnel[rock->bottom + i] ^ rock->state[i]) | rock->state[i] << 1);
            }
        }        
    }

    if (canMove) {
        --rock->left;
        --rock->right;

        for (int i = 0; i < rock->rowCount; i++) {
            tunnel->tunnel[rock->bottom + i] ^= rock->state[i];
            tunnel->tunnel[rock->bottom + i] |= (rock->state[i] <<= 1);
        }
    }
}

void tryMoveRight(struct Rock *rock, struct Tunnel *tunnel) {
    bool canMove = rock->right < TUNNEL_WIDTH - 1;

    if (canMove && rock->bottom <= tunnel->top) {
        for (int i = 0; canMove && i < rock->rowCount; i++) {
            if (rock->bottom + i - 1 <= tunnel->top) {
                canMove = bitCount(tunnel->tunnel[rock->bottom + i]) == 
                    bitCount((tunnel->tunnel[rock->bottom + i] ^ rock->state[i]) | rock->state[i] >> 1);
            }
        }        
    }

    if (canMove) {
        ++rock->left;
        ++rock->right;

        for (int i = 0; i < rock->rowCount; i++) {
            tunnel->tunnel[rock->bottom + i] ^= rock->state[i];
            tunnel->tunnel[rock->bottom + i] |= (rock->state[i] >>= 1);
        }
    }
}

bool tryMoveDown(struct Rock *rock, struct Tunnel *tunnel) {
    bool canMove = rock->bottom > 0;

    if (canMove && rock->bottom <= tunnel->top + 1) {
        for (int i = 0; canMove && i < rock->rowCount; i++) {
            if (rock->bottom + i - 1 <= tunnel->top) {
                canMove = bitCount(tunnel->tunnel[rock->bottom + i - 1] ^ (i > 0 ? rock->state[i - 1] : 0)) + bitCount(rock->state[i]) == 
                    bitCount((tunnel->tunnel[rock->bottom + i - 1] ^ (i > 0 ? rock->state[i - 1] : 0)) | rock->state[i]);
            }
        }        
    }

    if (canMove) {
        for (int i = 0; i < rock->rowCount; i++) {
            tunnel->tunnel[rock->bottom + i] ^= rock->state[i];
            tunnel->tunnel[rock->bottom + i - 1] |= rock->state[i];
        }        

        --rock->top;
        --rock->bottom;
    }

    return canMove;
}

struct TunnelState {
    long tunnelTop;
    long rockCount;
    enum RockType fallingRockType;
    int gustIndex;
    int relativeHeights[TUNNEL_WIDTH];
};

int compareStates(struct TunnelState stateOne, struct TunnelState stateTwo) {
    int result = stateOne.fallingRockType - stateTwo.fallingRockType;

    if (result == 0) {
        result = stateOne.gustIndex - stateTwo.gustIndex;
    }

    for (int i = 0; result == 0 && i < TUNNEL_WIDTH; i++) {
        result = stateOne.relativeHeights[i] - stateTwo.relativeHeights[i];
    }

    return result;
}

int binarySearchStates(struct TunnelState tunnelState, struct TunnelState *tunnelStates, int low, int high) {
    if (low > high) {
        return -1;
    }

    int middle = low + ((high - low) / 2);

    int result = compareStates(tunnelStates[middle], tunnelState);

    if (result == 0) {
        return middle;
    } else if (result < 0) {
        return binarySearchStates(tunnelState, tunnelStates, low, middle - 1);
    } else {
        return binarySearchStates(tunnelState, tunnelStates, middle + 1, high);
    }
}

int compare(const void *a, const void *b) {
    return compareStates(*(struct TunnelState *)a, *(struct TunnelState *)b);
}

struct Tunnel *getTunnel() {
    FILE *inputFile = fopen("input.txt", "r");

    if (inputFile) {
        struct Tunnel *tunnel = (struct Tunnel *)calloc(1, sizeof(struct Tunnel));
        tunnel->inputFile = inputFile;
        tunnel->tunnelHeight = 1000;
        tunnel->tunnel = (int *)malloc(tunnel->tunnelHeight * sizeof(int));
        tunnel->rockType = MINUS;

        return tunnel;
    }

    return NULL;    
}

void freeTunnel(struct Tunnel *tunnel) {
    free(tunnel->tunnel);
    free(tunnel);
}

void dropRocks(struct Tunnel *tunnel, int targetRockCount) {
    int rockCount = 0;

    tunnel->rock = addRock(tunnel);

    while (rockCount < targetRockCount) {
        char gust = fgetc(tunnel->inputFile);

        if (feof(tunnel->inputFile)) {
            fseek(tunnel->inputFile, 0, SEEK_SET);

            gust = fgetc(tunnel->inputFile);

            tunnel->gustIndex = 0;
        }

        if (gust == '<') {
            tryMoveLeft(&tunnel->rock, tunnel);
        } else {
            tryMoveRight(&tunnel->rock, tunnel);
        }

        if (!tryMoveDown(&tunnel->rock, tunnel)) {
            tunnel->top = max(tunnel->top, tunnel->rock.bottom + tunnel->rock.rowCount);

            if (tunnel->rockType++ == BLOCK) {
                tunnel->rockType = MINUS;
            }

            if (tunnel->tunnelHeight - tunnel->top < 10) {
                tunnel->tunnelHeight += 1000;

                tunnel->tunnel = (int *)realloc(tunnel->tunnel, tunnel->tunnelHeight * sizeof(int));
                memset(tunnel->tunnel + tunnel->tunnelHeight - 1000, 0, 1000 * sizeof(int));
            }

            free(tunnel->rock.state);

            ++tunnel->rockCount;

            if (++rockCount < targetRockCount) {
                tunnel->rock = addRock(tunnel);
            }
        }

        ++tunnel->gustIndex;
    }
}
