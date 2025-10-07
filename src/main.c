#define PAUL_IMPLEMENTATION
#include "cccp.h"

extern int WindowOpen(int w, int h, const char *title, CCCP_WindowFlags flags);
extern int WindowPoll(void);
extern void WindowClose(void);

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH 640
#endif
#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT 480
#endif
#ifndef WINDOW_TITLE
#define WINDOW_TITLE "CCCP"
#endif
#ifndef CLEAR_COLOR
#define CLEAR_COLOR rgb(0, 0, 0)
#endif
#ifndef TARGET_FPS
#define TARGET_FPS 60
#endif

#if defined(PLATFORM_WINDOWS)
#include <Windows.h>
#include <io.h>
#define F_OK 0
#define access _access
#include "getopt_win32.h"
#ifndef _MSC_VER
#pragma comment(lib, "Psapi.lib")
#endif
#define DLFCN_IMPLEMENTATION
#include "dlfcn_win32.h"
#else // PLATFORM_POSIX
#include <getopt.h>
#define _BSD_SOURCE // usleep()
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dlfcn.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static struct {
#if defined(PLATFORM_WINDOWS)
    FILETIME writeTime;
#else
    ino_t handleID;
#endif
    void *handle;
    CCCP_State *state;
    CCCP_Scene *scene;
    CCCP_Surface buffer;
    struct {
        unsigned int width;
        unsigned int height;
        const char *title;
        CCCP_WindowFlags flags;
        char *path;
    } args;
} state;

static struct option long_options[] = {
    {"width", required_argument, NULL, 'w'},
    {"height", required_argument, NULL, 'h'},
    {"title", required_argument, NULL, 't'},
    {"resizable", no_argument, NULL, 'r'},
    {"top", no_argument, NULL, 'a'},
    {"usage", no_argument, NULL, 'u'},
    {"path", required_argument, NULL, 'p'},
    {NULL, 0, NULL, 0}
};

static void usage(void) {
    puts(" usage: cccp [path to dylib] [options]");
    puts("");
    puts(" cccp  Copyright (C) 2024  George Watson");
    puts(" This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.");
    puts(" This is free software, and you are welcome to redistribute it");
    puts(" under certain conditions; type `show c' for details.");
    puts("");
    puts("  Options:");
    puts("      -w/--width     Window width [default: 640]");
    puts("      -h/--height    Window height [default: 480]");
    puts("      -t/--title     Window title [default: \"fwp\"]");
    puts("      -r/--resizable Enable resizable window");
    puts("      -a/--top       Enable window always on top");
    puts("      -u/--usage     Display this message");
}

#ifdef _WIN32
static FILETIME Win32GetLastWriteTime(char* path) {
    FILETIME time;
    WIN32_FILE_ATTRIBUTE_DATA data;

    if (GetFileAttributesEx(path, GetFileExInfoStandard, &data))
        time = data.ftLastWriteTime;

    return time;
}
#endif

static int ShouldReloadLibrary(void) {
#ifdef _WIN32
    FILETIME newTime = Win32GetLastWriteTime(state.args.path);
    int result = CompareFileTime(&newTime, &state.writeTime);
    if (result)
        state.writeTime = newTime;
    return result;
#else
    struct stat attr;
    int result = !stat(state.args.path, &attr) && state.handleID != attr.st_ino;
    if (result)
        state.handleID = attr.st_ino;
    return result;
#endif
}

#ifdef _WIN32
char* RemoveExt(char* path) {
    char *ret = malloc(strlen(path) + 1);
    if (!ret)
        return NULL;
    strcpy(ret, path);
    char *ext = strrchr(ret, '.');
    if (ext)
        *ext = '\0';
    return ret;
}
#endif

static int ReloadLibrary(const char *path) {
    if (!ShouldReloadLibrary())
        return 1;

    if (state.handle) {
        if (state.scene->unload)
            state.scene->unload(state.state);
        dlclose(state.handle);
    }

#if defined(PLATFORM_WINDOWS)
    size_t newPathSize = strlen(path) + 4;
    char *newPath = malloc(sizeof(char) * newPathSize);
    char *noExt = RemoveExt(path);
    sprintf(newPath, "%s.tmp.dll", noExt);
    CopyFile(path, newPath, 0);
    handle = dlopen(newPath, RTLD_NOW);
    free(newPath);
    free(noExt);
    if (!state.handle)
#else
    if (!(state.handle = dlopen(path, RTLD_NOW)))
#endif
        goto BAIL;
    if (!(state.scene = dlsym(state.handle, "scene")))
        goto BAIL;
    if (!state.state) {
        if (state.scene->windowWidth > 0 && state.scene->windowHeight > 0)
            CCCP_SetWindowSize(state.scene->windowWidth, state.scene->windowHeight);
        if (state.scene->windowTitle)
            CCCP_SetWindowTitle(state.scene->windowTitle);
        if (!(state.state = state.scene->init(state.buffer)))
            goto BAIL;
    } else {
        if (state.scene->windowWidth > 0 && state.scene->windowHeight > 0)
            CCCP_SetWindowSize(state.scene->windowWidth, state.scene->windowHeight);
        if (state.scene->windowTitle)
            CCCP_SetWindowTitle(state.scene->windowTitle);
        if (state.scene->reload)
            state.scene->reload(state.state);
    }
    return 1;

BAIL:
    if (state.handle)
        dlclose(state.handle);
    state.handle = NULL;
#if defined(PLATFORM_WINDOWS)
    memset(&state.writeTime, 0, sizeof(FILETIME));
#else
    state.handleID = 0;
#endif
    return 0;
}

#define pbInputCallback(E)                    \
    if (state.scene->event)                   \
        state.scene->event(state.state, &(E)) \

static void pbInputKeyboard(void *userdata, int key, int modifier, int isDown) {
    CCCP_Event e = {
        .type = KeyboardEvent,
        .keyboard = {
            .key = key,
            .down = isDown
        },
        .modifier = modifier
    };
    pbInputCallback(e);
}

static void pbInputMouseButton(void *userdata, int button, int modifier, int isDown) {
    CCCP_Event e = {
        .type = MouseButtonEvent,
        .mouse = {
            .button = button,
            .down = isDown
        },
        .modifier = modifier
    };
    pbInputCallback(e);
}

static void pbInputMouseMove(void *userdata, int x, int y, float dx, float dy) {
    CCCP_Event e = {
        .type = MouseMoveEvent,
        .mouse = {
            .position = {
                .x = x,
                .y = y,
                .dx = dx,
                .dy = dy
            }
        }
    };
    pbInputCallback(e);
}

static void pbInputMouseScroll(void *userdata, float dx, float dy, int modifier) {
    CCCP_Event e = {
        .type = MouseScrollEvent,
        .mouse = {
            .wheel = {
                .dx = dx,
                .dy = dy
            }
        }
    };
    pbInputCallback(e);
}

static void pbInputFocus(void *userdata, int isFocused) {
    CCCP_Event e = {
        .type = FocusEvent,
        .window = {
            .focused = isFocused
        }
    };
    pbInputCallback(e);
}

static void pbInputResized(void *userdata, int w, int h) {
    CCCP_Event e = {
        .type = ResizedEvent,
        .window = {
            .size = {
                .width = w,
                .height = h
            }
        }
    };
    pbInputCallback(e);
}

static void pbInputClosed(void *userdata) {
    CCCP_Event e = {
        .type = ClosedEvent,
        .window = {
            .closed = true
        }
    };
    pbInputCallback(e);
}

int main(int argc, char *argv[]) {
    extern char* optarg;
    extern int optopt;
    extern int optind;
    int opt;
    while ((opt = getopt_long(argc, argv, ":w:h:t:uar", long_options, NULL)) != -1) {
        switch (opt) {
            case 'w':
                state.args.width = atoi(optarg);
                break;
            case 'h':
                state.args.height = atoi(optarg);
                break;
            case 't':
                state.args.title = optarg;
                break;
            case 'r':
                state.args.flags |= WINDOW_RESIZABLE;
                break;
            case 'a':
                state.args.flags |= WINDOW_ALWAYS_ON_TOP;
                break;
            case ':':
                printf("ERROR: \"-%c\" requires an value!\n", optopt);
                usage();
                return 0;
            case '?':
                printf("ERROR: Unknown argument \"-%c\"\n", optopt);
                usage();
                return 0;
            case 'u':
                usage();
                return 1;
            default:
                usage();
                return 0;
        }
    }

    if (optind >= argc) {
        puts("ERROR: No path to dynamic library provided");
        usage();
        return 0;
    } else
        state.args.path = argv[optind];
    
    if (state.args.path) {
#if !defined(PLATFORM_WINDOWS)
        if (state.args.path[0] != '.' || state.args.path[1] != '/') {
            char *tmp = malloc(strlen(state.args.path) + 2 * sizeof(char));
            sprintf(tmp, "./%s", state.args.path);
            state.args.path = tmp;
        } else
            state.args.path = strdup(state.args.path);
#endif
    }

    if (access(state.args.path, F_OK)) {
        printf("ERROR: No file found at path \"%s\"\n", state.args.path);
        return 0;
    }

    if (!state.args.width)
        state.args.width = WINDOW_WIDTH;
    if (!state.args.height)
        state.args.height = WINDOW_HEIGHT;
    if (!state.args.title)
        state.args.title = WINDOW_TITLE;

    if (!WindowOpen(800, 600, "CCCP", WINDOW_RESIZABLE)) {
        fprintf(stderr, "Failed to open window!\n");
        return 1;
    }

    if (!(state.buffer = CCCP_NewSurface(state.args.width, state.args.height, rgb(0, 0, 0))))
        return 0;

    if (!ReloadLibrary(state.args.path))
        return 0;

#define X(NAME, _) pbInput##NAME,
    CCCP_SetCallbacks(CCCP_CALLBACKS NULL);
#undef X

    while (WindowPoll()) {
        CCCP_ClearSurface(state.buffer, state.scene->clearColor);
        if (!ReloadLibrary(state.args.path))
            break;
        if (!state.scene->tick(state.state, state.buffer, 0.f))
            break;
        CCCP_RenderSurface(state.buffer);
    }
    state.scene->deinit(state.state);
    if (state.handle)
        dlclose(state.handle);
    CCCP_DestroySurface(state.buffer);
#if !defined(PLATFORM_WINDOWS)
    free(state.args.path);
#endif
    WindowClose();
    return 0;
}