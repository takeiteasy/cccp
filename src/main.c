#define PAUL_IMPLEMENTATION
#include "cccp.h"

extern int WindowOpen(int w, int h, const char *title, CCCP_WINDOW_FLAGS flags);
extern int WindowPoll(void);
extern void WindowClose(void);

int main(int argc, char *argv[]) {
    if (!WindowOpen(800, 600, "CCCP", WINDOW_RESIZABLE)) {
        fprintf(stderr, "Failed to open window!\n");
        return 1;
    }

    CCCP_Surface buffer = bitmap_empty(800, 600, rgb(0, 255, 0));
    
    while (WindowPoll()) {
        CCCP_RenderSurface(buffer);
    }
    WindowClose();
    return 0;
}