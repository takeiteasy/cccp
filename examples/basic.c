// Firstly include the cccp header, which contains everything we need
#include "cccp.h"
#include <stdlib.h> // malloc

// A CCCP_State should be defined in each scene. This structure can contain whatever variables and types you want, but it must be defined like this. Do not typedef the struct definition, as it is already typedef'd in cccp.h
struct CCCP_State {
    color_t clearColor;
};

static CCCP_State* init(CCCP_Surface framebuffer) {
    // Called once when the program first starts
    // You must always create an instance of your CCCP_State definition
    // It must be allocated on the stack, not the heap
    // This object will be be used to keep track of things between reloads
    CCCP_State *state = malloc(sizeof(CCCP_State));
    state->clearColor = rgb(255, 0, 0);
    // Return your CCCP_State so cccp can keep track of it
    return state;
}

static void deinit(CCCP_State *state) {
    // Only called when the program is exiting
    if (state)
        free(state);
}

static void reload(CCCP_State *state) {
    // Called when the dynamic has been updated + reloaded
    // Here we change the `clearColor` field in our state to blue
    // If you rebuild the library, the screen will chang from red
    // to blue! Magic!
    state->clearColor = rgb(0, 0, 255);
}

static void unload(CCCP_State *state) {
    // Called when dynamic library has been unloaded
}

static int event(CCCP_State *state, CCCP_Event *e) {
    // Called on window event
    return 1;
}

static int tick(CCCP_State *state, CCCP_Surface pbo, CCCP_AudioContext *audio, double delta) {
    // Called every frame, this is your update callback
    CCCP_ClearSurface(pbo, state->clearColor);
    CCCP_DrawRect(pbo, 50, 50, 50, 50, rgb(255, 255, 255), true);
    return 1;
}

// So cccp knows where your callbacks are a `scene` definition must be made
// The definition should be always be called scene. If the name changes cccp
// won't know where to look!
const CCCP_Scene scene = {
    .init = init,
    .deinit = deinit,
    .reload = reload,
    .unload = unload,
    .event = event,
    .tick = tick
};
