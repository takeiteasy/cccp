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
    int thread_count; // 0 = use hardware concurrency
    thrd_pool_t *pool;
} CCCP_Shader;

typedef struct CCCP_HashEntry {
    const char* key;
    void* value;
    struct CCCP_HashEntry* next;
} CCCP_HashEntry;

typedef struct {
    CCCP_HashEntry** buckets;
    size_t capacity;
    size_t size;
    void(*free_callback)(void*);
} CCCP_HashTable;

typedef struct CCCP_AudioContext {
    float volume;
    CCCP_HashTable *waves;
    CCCP_HashTable *sounds;
    CCCP_HashTable *music;
} CCCP_AudioContext;

typedef struct {
    int windowWidth;
    int windowHeight;
    const char *windowTitle;
    color_t clearColor;
    int targetFPS;
    CCCP_State*(*init)(CCCP_Surface, CCCP_AudioContext*);
    void(*deinit)(CCCP_State*, CCCP_AudioContext*);
    void(*reload)(CCCP_State*, CCCP_AudioContext*);
    void(*unload)(CCCP_State*, CCCP_AudioContext*);
    int(*event)(CCCP_State*, CCCP_Event*, CCCP_AudioContext*);
    int(*tick)(CCCP_State*, CCCP_Surface, CCCP_AudioContext*, double);
} CCCP_Scene;

/* === SURFACES === */

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

CCCP_Surface CCCP_SurfaceFromPerlinNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);
CCCP_Surface CCCP_SurfaceFromSimplexNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);
CCCP_Surface CCCP_SurfaceFromWorleyNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);
CCCP_Surface CCCP_SurfaceFromValueNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);
CCCP_Surface CCCP_SurfaceFromWhiteNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);
CCCP_Surface CCCP_SurfaceFromFBMNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY, float lacunarity, float gain, int octaves);

CCCP_Surface CCCP_SurfaceFromHorizontalGradient(unsigned int width, unsigned int height, color_t startColor, color_t endColor);
CCCP_Surface CCCP_SurfaceFromVerticalGradient(unsigned int width, unsigned int height, color_t startColor, color_t endColor);
CCCP_Surface CCCP_SurfaceFromRadialGradient(unsigned int width, unsigned int height, color_t centerColor, color_t edgeColor);
CCCP_Surface CCCP_SurfaceFromDiagonalGradient(unsigned int width, unsigned int height, color_t startColor, color_t endColor);

CCCP_Surface CCCP_SurfaceFromCheckerboard(unsigned int width, unsigned int height, color_t color1, color_t color2, unsigned int squareSize);

CCCP_Surface CCCP_SurfaceFromHorizontalStripes(unsigned int width, unsigned int height, color_t color1, color_t color2, unsigned int stripeWidth);
CCCP_Surface CCCP_SurfaceFromVerticalStripes(unsigned int width, unsigned int height, color_t color1, color_t color2, unsigned int stripeWidth);
CCCP_Surface CCCP_SurfaceFromConcentricCircles(unsigned int width, unsigned int height, color_t centerColor, color_t edgeColor, unsigned int numRings);

CCCP_Shader CCCP_NewShader(CCCP_ShaderFunc func, int numThreads);
void CCCP_DestroyShader(CCCP_Shader *shader);
void CCCP_ApplyShader(CCCP_Surface surface, CCCP_Shader *shader, void* userdata);

/* === AUDIO === */

void CCCP_SetMasterVolume(CCCP_AudioContext* ctx, float volume);
float CCCP_GetMasterVolume(CCCP_AudioContext* ctx);

bool CCCP_NewWaveFromMemory(CCCP_AudioContext* ctx, const char* key, const void* data, int dataSize);
bool CCCP_NewWaveFromFile(CCCP_AudioContext* ctx, const char* key, const char* filename);
bool CCCP_DestroyWave(CCCP_AudioContext* ctx, const char* key);
bool CCCP_NewSoundFromWave(CCCP_AudioContext* ctx, const char* key, const char* waveKey);
bool CCCP_NewSoundFromFile(CCCP_AudioContext* ctx, const char* key, const char* filename);
bool CCCP_DestroySound(CCCP_AudioContext* ctx, const char* key);
bool CCCP_NewMusicFromMemory(CCCP_AudioContext* ctx, const char* key, const void* data, int dataSize);
bool CCCP_NewMusicFromFile(CCCP_AudioContext* ctx, const char* key, const char* filename);
bool CCCP_DestroyMusic(CCCP_AudioContext* ctx, const char* key);

void CCCP_UnloadAllWaves(CCCP_AudioContext* ctx);
void CCCP_UnloadAllSounds(CCCP_AudioContext* ctx);
void CCCP_UnloadAllMusic(CCCP_AudioContext* ctx);

bool CCCP_IsWaveReady(CCCP_AudioContext* ctx, const char* key);
bool CCCP_IsSoundReady(CCCP_AudioContext* ctx, const char* key);
bool CCCP_IsMusicReady(CCCP_AudioContext* ctx, const char* key);

void CCCP_UpdateSound(CCCP_AudioContext* ctx, const char* key, const void *data, int frameCount);
void CCCP_UpdateMusic(CCCP_AudioContext* ctx, const char* key, const void *data, int sampleCount);

void CCCP_PlaySound(CCCP_AudioContext* ctx, const char* key);
void CCCP_StopSound(CCCP_AudioContext* ctx, const char* key);
void CCCP_PauseSound(CCCP_AudioContext* ctx, const char* key);
void CCCP_ResumeSound(CCCP_AudioContext* ctx, const char* key);
bool CCCP_IsSoundPlaying(CCCP_AudioContext* ctx, const char* key);
void CCCP_SetSoundVolume(CCCP_AudioContext* ctx, const char* key, float volume);
float CCCP_GetSoundVolume(CCCP_AudioContext* ctx, const char* key);

void CCCP_PlayMusic(CCCP_AudioContext* ctx, const char* key);
void CCCP_StopMusic(CCCP_AudioContext* ctx, const char* key);
void CCCP_PauseMusic(CCCP_AudioContext* ctx, const char* key);
void CCCP_ResumeMusic(CCCP_AudioContext* ctx, const char* key);
bool CCCP_IsMusicPlaying(CCCP_AudioContext* ctx, const char* key);
void CCCP_SetMusicVolume(CCCP_AudioContext* ctx, const char* key, float volume);
float CCCP_GetMusicVolume(CCCP_AudioContext* ctx, const char* key);
void CCCP_SeekMusic(CCCP_AudioContext* ctx, const char* key, float position);
float CCCP_GetMusicTimeLength(CCCP_AudioContext* ctx, const char* key);
float CCCP_GetMusicTimePlayed(CCCP_AudioContext* ctx, const char* key);
void CCCP_SetMusicLooping(CCCP_AudioContext* ctx, const char* key, bool looping);
bool CCCP_IsMusicLooping(CCCP_AudioContext* ctx, const char* key);

/* === TIMER === */

typedef struct CCCP_Timer CCCP_Timer;

CCCP_Timer* CCCP_NewTimer(void);
void CCCP_DestroyTimer(CCCP_Timer* timer);
void CCCP_StartTimer(CCCP_Timer* timer);
void CCCP_StopTimer(CCCP_Timer* timer);
void CCCP_PauseTimer(CCCP_Timer* timer);
void CCCP_ResumeTimer(CCCP_Timer* timer);
double CCCP_GetElapsedTime(CCCP_Timer* timer);
void CCCP_Sleep(double seconds);

/* === HASH TABLE === */

CCCP_HashTable* CCCP_NewHashTable(size_t capacity);
void CCCP_DestroyHashTable(CCCP_HashTable* table);
int CCCP_HashTableInsert(CCCP_HashTable* table, const char* key, void* value);
void* CCCP_HashTableGet(CCCP_HashTable* table, const char* key);
int CCCP_HashTableRemove(CCCP_HashTable* table, const char* key);
size_t CCCP_HashTableSize(CCCP_HashTable* table);
void CCCP_HashTableClear(CCCP_HashTable* table);

#ifdef __cplusplus
}
#endif
#endif // CCCP_H