#ifndef CCCP_H
#define CCCP_H
#if defined(__cplusplus)
extern "C" {
#endif

#include "paul/paul_color.h"
#include "paul/paul_bitmap.h"
#include "paul/paul_math.h"
#include "paul/paul_threads.h"

typedef enum {
    WINDOW_RESIZABLE          = 1 << 0,
    WINDOW_FULLSCREEN         = 1 << 1,
    WINDOW_FULLSCREEN_DESKTOP = 1 << 2,
    WINDOW_BORDERLESS         = 1 << 3,
    WINDOW_ALWAYS_ON_TOP      = 1 << 4
} CCCP_WINDOW_FLAGS;

typedef enum {
    KEY_PAD0=128,KEY_PAD1,KEY_PAD2,KEY_PAD3,KEY_PAD4,KEY_PAD5,KEY_PAD6,KEY_PAD7,
    KEY_PAD8,KEY_PAD9,KEY_PADMUL,KEY_PADADD,KEY_PADENTER,KEY_PADSUB,KEY_PADDOT,
    KEY_PADDIV,KEY_F1,KEY_F2,KEY_F3,KEY_F4,KEY_F5,KEY_F6,KEY_F7,KEY_F8,KEY_F9,
    KEY_F10,KEY_F11,KEY_F12,KEY_BACKSPACE,KEY_TAB,KEY_RETURN,KEY_SHIFT,
    KEY_CONTROL,KEY_ALT,KEY_PAUSE,KEY_CAPSLOCK,KEY_ESCAPE,KEY_SPACE,KEY_PAGEUP,
    KEY_PAGEDN,KEY_END,KEY_HOME,KEY_LEFT,KEY_UP,KEY_RIGHT,KEY_DOWN,KEY_INSERT,
    KEY_DELETE,KEY_LWIN,KEY_RWIN,KEY_NUMLOCK,KEY_SCROLL,KEY_LSHIFT,KEY_RSHIFT,
    KEY_LCONTROL,KEY_RCONTROL,KEY_LALT,KEY_RALT,KEY_SEMICOLON,KEY_EQUALS,
    KEY_COMMA,KEY_MINUS,KEY_DOT,KEY_SLASH,KEY_BACKTICK,KEY_LSQUARE,
    KEY_BACKSLASH,KEY_RSQUARE,KEY_TICK
} CCCP_KEY;

typedef enum {
    KEY_MOD_SHIFT     = 1 << 0,
    KEY_MOD_CONTROL   = 1 << 1,
    KEY_MOD_ALT       = 1 << 2,
    KEY_MOD_SUPER     = 1 << 3,
    KEY_MOD_CAPS_LOCK = 1 << 4,
    KEY_MOD_NUM_LOCK  = 1 << 5
} CCCP_MODIFIER_KEY;

#define CCCP_CALLBACKS                               \
    X(Keyboard,     (void*, int, int, int))          \
    X(MouseButton,  (void*, int, int, int))          \
    X(MouseMove,    (void*, int, int, float, float)) \
    X(MouseScroll,  (void*, float, float, int))      \
    X(Resized,      (void*, int, int))               \
    X(Focus,        (void*, int))                    \
    X(Closed,       (void*))

typedef struct CCCP_State CCCP_State;

typedef enum {
#define X(NAME, ARGS) NAME##Event,
    CCCP_CALLBACKS
#undef X
} CCCP_EVENT_TYPE;

typedef struct {
    struct {
        int button;
        int down;
        struct {
            unsigned int x, y;
            float dx, dy;
        } position;
        struct {
            float dx, dy;
        } wheel;
    } mouse;
    struct {
        CCCP_KEY key;
        int down;
    } keyboard;
    CCCP_MODIFIER_KEY modifier;
    struct {
        int focused, closed;
        struct {
            unsigned int width, height;
        } size;
    } window;
    CCCP_EVENT_TYPE type;
} CCCP_Event;

typedef bitmap_t CCCP_Surface;

typedef struct {
    int windowWidth;
    int windowHeight;
    const char *windowTitle;
    CCCP_State*(*init)(CCCP_Surface);
    void(*deinit)(CCCP_State*);
    void(*reload)(CCCP_State*);
    void(*unload)(CCCP_State*);
    int(*event)(CCCP_State*, CCCP_Event*);
    int(*tick)(CCCP_State*, CCCP_Surface, double);
} CCCP_Scene;

void CCCP_RenderSurface(CCCP_Surface buffer);
void CCCP_GetUserdata(void *userdata);

void CCCP_SetWindowTitle(const char *title);
void CCCP_GetWindowSize(unsigned int *w, unsigned int *h);
void CCCP_SetWindowSize(unsigned int w, unsigned int h);
void CCCP_GetMousePosition(int *x, int *y);

#define X(NAME, ARGS) \
    void(*NAME##Callback)ARGS,
void CCCP_SetCallbacks(CCCP_CALLBACKS void *userdata);
#undef X
#define X(NAME, ARGS) \
    void CCCP_Set##NAME##Callback(void(*NAME##Callback)ARGS);
CCCP_CALLBACKS
#undef X

#ifdef __cplusplus
}
#endif
#endif // CCCP_H