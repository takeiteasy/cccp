#ifndef CCCP_H
#define CCCP_H
#if defined(__cplusplus)
extern "C" {
#endif

#include "paul_color.h"
#include "paul_bitmap.h"
#include "paul_math.h"
#include "paul_threads.h"
#include "paul_os.h"
#include "raudio.h"

typedef enum {
    WINDOW_RESIZABLE          = 1 << 0,
    WINDOW_FULLSCREEN         = 1 << 1,
    WINDOW_FULLSCREEN_DESKTOP = 1 << 2,
    WINDOW_BORDERLESS         = 1 << 3,
    WINDOW_ALWAYS_ON_TOP      = 1 << 4
} CCCP_WindowFlags;

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
} CCCP_Key;

typedef enum {
    KEY_MOD_SHIFT     = 1 << 0,
    KEY_MOD_CONTROL   = 1 << 1,
    KEY_MOD_ALT       = 1 << 2,
    KEY_MOD_SUPER     = 1 << 3,
    KEY_MOD_CAPS_LOCK = 1 << 4,
    KEY_MOD_NUM_LOCK  = 1 << 5
} CCCP_ModifierKey;

#define CCCP_CALLBACKS                               \
    X(Keyboard,     (void*, int, int, int))          \
    X(MouseButton,  (void*, int, int, int))          \
    X(MouseMove,    (void*, int, int, float, float)) \
    X(MouseScroll,  (void*, float, float, int))      \
    X(Resized,      (void*, int, int))               \
    X(Focus,        (void*, int))

typedef struct CCCP_State CCCP_State;

typedef enum {
#define X(NAME, ARGS) NAME##Event,
    CCCP_CALLBACKS
#undef X
} CCCP_EventType;

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
        CCCP_Key key;
        int down;
    } keyboard;
    CCCP_ModifierKey modifier;
    struct {
        int focused, closed;
        struct {
            unsigned int width, height;
        } size;
    } window;
    CCCP_EventType type;
} CCCP_Event;

typedef bitmap_t CCCP_Surface;
typedef color_t CCCP_Color;

// Shader function type: (fragcoord, resolution, time, userdata) -> color
typedef vec4(*CCCP_ShaderFunc)(vec2, vec2, float, void*);

typedef struct {
    CCCP_ShaderFunc func;
    thrd_pool_t *pool;
} CCCP_Shader;

typedef Wave CCCP_Wave;
typedef AudioStream CCCP_AudioStream;
typedef Sound CCCP_Sound;
typedef Music CCCP_Music;
typedef struct CCCP_AudioContext CCCP_AudioContext;

typedef struct {
    int windowWidth;
    int windowHeight;
    const char *windowTitle;
    color_t clearColor;
    int targetFPS;
    CCCP_State*(*init)(CCCP_Surface);
    void(*deinit)(CCCP_State*);
    void(*reload)(CCCP_State*);
    void(*unload)(CCCP_State*);
    int(*event)(CCCP_State*, CCCP_Event*);
    int(*tick)(CCCP_State*, CCCP_Surface, CCCP_AudioContext*, double);
} CCCP_Scene;

CCCP_Surface CCCP_NewSurface(unsigned int w, unsigned int h, color_t clearColor);
CCCP_Surface CCCP_SurfaceFromMemory(const void* data, int width, int height, bitmap_format_t format);
CCCP_Surface CCCP_SurfaceFromFile(const char* filename);
CCCP_Surface CCCP_CopySurface(CCCP_Surface surface);
void CCCP_DestroySurface(CCCP_Surface surface);
int CCCP_SurfaceWidth(CCCP_Surface surface);
int CCCP_SurfaceHeight(CCCP_Surface surface);

void CCCP_ClearSurface(CCCP_Surface surface, color_t clearColor);

bool CCCP_SetPixel(CCCP_Surface surface, int x, int y, color_t color);
color_t CCCP_GetPixel(CCCP_Surface surface, int x, int y);

void CCCP_BlitSurface(CCCP_Surface dest, CCCP_Surface src, int x, int y);
void CCCP_BlitSurfaceRect(CCCP_Surface dest, CCCP_Surface src, int srcX, int srcY, int srcW, int srcH, int destX, int destY);

void CCCP_DrawLine(CCCP_Surface surface, int x1, int y1, int x2, int y2, color_t color);
void CCCP_DrawRect(CCCP_Surface surface, int x, int y, int w, int h, color_t color, bool filled);
void CCCP_DrawCircle(CCCP_Surface surface, int x, int y, int radius, color_t color, bool filled);
void CCCP_DrawTriangle(CCCP_Surface surface, int x1, int y1, int x2, int y2, int x3, int y3, color_t color, bool filled);

CCCP_Surface CCCP_ResizeSurface(CCCP_Surface surface, unsigned int w, unsigned int h);
CCCP_Surface CCCP_RotateSurface(CCCP_Surface surface, float angle);
CCCP_Surface CCCP_FlipSurface(CCCP_Surface surface, bool horizontal, bool vertical);
CCCP_Surface CCCP_ClipSurface(CCCP_Surface surface, int x, int y, int w, int h);

CCCP_Shader CCCP_NewShader(CCCP_ShaderFunc func, int numThreads);
void CCCP_DestroyShader(CCCP_Shader shader);
void CCCP_ApplyShader(CCCP_Surface surface, CCCP_Shader shader, void* userdata);

// TODO: rAudio wrappers

#ifdef __cplusplus
}
#endif
#endif // CCCP_H