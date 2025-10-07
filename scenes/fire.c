#include "cccp.h"
#include <stdlib.h> // malloc

#define BASE_HEIGHT 8
#define FIRE_INTENSITY 1.f
#define FIRE_HEIGHT 100

#define FIRE_PALLET_SIZE 7
static int FIRE_PALETTE[] = {
    -65536,
    -6807033,
    -331755,
    -410869,
    -489207,
    -1946157056,
    805306368
};

struct CCCP_State {
    int dummy;
};

static void DrawFireBase(CCCP_Surface *framebuffer) {
    for (int x = 0; x < framebuffer->width; x++)
        for (int y = 0; y < BASE_HEIGHT; y++)
            pbImagePSet(framebuffer, x, framebuffer->height - (y + 1), FIRE_PALETTE[0]);
}

static CCCP_State* init(CCCP_Surface *framebuffer) {
    CCCP_State *state = malloc(sizeof(CCCP_State));
    rngInit(0);
    DrawFireBase(framebuffer);
    return state;
}

static void deinit(CCCP_State *state) {
    if (state)
        free(state);
}

static void reload(CCCP_State *state) {

}

static void unload(CCCP_State *state) {

}

static int event(CCCP_State *state, CCCP_Event *e) {
    return 1;
}

static int tick(CCCP_State *state, CCCP_Surface *framebuffer, double delta) {
    DrawFireBase(framebuffer);
    for (int i = 0; i < framebuffer->width * FIRE_HEIGHT; i++) {
        int x = rngRandomIntRange(0, framebuffer->width);
        int y = framebuffer->height - rngRandomIntRange(0, FIRE_HEIGHT);
        int c = pbImagePGet(framebuffer, x, y);

        int pIdx = -1;
        for (int j = 0; j < FIRE_PALLET_SIZE; j++)
            if (FIRE_PALETTE[j] == c) {
                pIdx = j;
                break;
            }

        float r = rngRandomFloat();
        if (r <= FIRE_INTENSITY) {
            int nx = x + rngRandomIntRange(0, 3) - 1;
            pbImagePSet(framebuffer, nx, y - 1, c);
            pbImagePSet(framebuffer, x, y, pIdx < 0 || ++pIdx >= FIRE_PALLET_SIZE ? RGBA(0, 0, 0, 0) : FIRE_PALETTE[pIdx]);
        }
    }
    return 1;
}

const CCCP_Scene scene = {
    .windowWidth = 320,
    .windowHeight = 240,
    .windowTitle = "AHHHHH! FIRE!",
    .init = init,
    .deinit = deinit,
    .reload = reload,
    .unload = unload,
    .event = event,
    .tick = tick
};
