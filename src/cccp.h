/*
 CCCP - The C Create Coding Project

 Copyright (C) 2025 George Watson

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/*!
 @header cccp.h
 @copyright George Watson GPLv3
 @updated 2025-07-19
 @brief CCCP - The C Create Coding Project
 @discussion
    This header defines the core data structures and function prototypes for the CCCP project.
*/

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

/*!
 * @enum CCCP_WindowFlags
 * @brief Flags for configuring window properties.
 * @constant WINDOW_RESIZABLE Window can be resized by the user.
 * @constant WINDOW_FULLSCREEN Window is in fullscreen mode.
 * @constant WINDOW_FULLSCREEN_DESKTOP Window is in fullscreen desktop mode.
 * @constant WINDOW_BORDERLESS Window has no border.
 * @constant WINDOW_ALWAYS_ON_TOP Window stays on top of other windows.
 */
typedef enum {
    WINDOW_RESIZABLE          = 1 << 0,
    WINDOW_FULLSCREEN         = 1 << 1,
    WINDOW_FULLSCREEN_DESKTOP = 1 << 2,
    WINDOW_BORDERLESS         = 1 << 3,
    WINDOW_ALWAYS_ON_TOP      = 1 << 4
} CCCP_WindowFlags;

/*!
 * @enum CCCP_Key
 * @brief Key codes for keyboard input.
 * @constant KEY_PAD0 Numpad 0 key.
 * @constant KEY_PAD1 Numpad 1 key.
 * @constant KEY_PAD2 Numpad 2 key.
 * @constant KEY_PAD3 Numpad 3 key.
 * @constant KEY_PAD4 Numpad 4 key.
 * @constant KEY_PAD5 Numpad 5 key.
 * @constant KEY_PAD6 Numpad 6 key.
 * @constant KEY_PAD7 Numpad 7 key.
 * @constant KEY_PAD8 Numpad 8 key.
 * @constant KEY_PAD9 Numpad 9 key.
 * @constant KEY_PADMUL Numpad multiply key.
 * @constant KEY_PADADD Numpad add key.
 * @constant KEY_PADENTER Numpad enter key.
 * @constant KEY_PADSUB Numpad subtract key.
 * @constant KEY_PADDOT Numpad decimal point key.
 * @constant KEY_PADDIV Numpad divide key.
 * @constant KEY_F1 F1 function key.
 * @constant KEY_F2 F2 function key.
 * @constant KEY_F3 F3 function key.
 * @constant KEY_F4 F4 function key.
 * @constant KEY_F5 F5 function key.
 * @constant KEY_F6 F6 function key.
 * @constant KEY_F7 F7 function key.
 * @constant KEY_F8 F8 function key.
 * @constant KEY_F9 F9 function key.
 * @constant KEY_F10 F10 function key.
 * @constant KEY_F11 F11 function key.
 * @constant KEY_F12 F12 function key.
 * @constant KEY_BACKSPACE Backspace key.
 * @constant KEY_TAB Tab key.
 * @constant KEY_RETURN Return/Enter key.
 * @constant KEY_SHIFT Shift key.
 * @constant KEY_CONTROL Control key.
 * @constant KEY_ALT Alt key.
 * @constant KEY_PAUSE Pause key.
 * @constant KEY_CAPSLOCK Caps Lock key.
 * @constant KEY_ESCAPE Escape key.
 * @constant KEY_SPACE Spacebar key.
 * @constant KEY_PAGEUP Page Up key.
 * @constant KEY_PAGEDN Page Down key.
 * @constant KEY_END End key.
 * @constant KEY_HOME Home key.
 * @constant KEY_LEFT Left arrow key.
 * @constant KEY_UP Up arrow key.
 * @constant KEY_RIGHT Right arrow key.
 * @constant KEY_DOWN Down arrow key.
 * @constant KEY_INSERT Insert key.
 * @constant KEY_DELETE Delete key.
 * @constant KEY_LWIN Left Windows key.
 * @constant KEY_RWIN Right Windows key.
 * @constant KEY_NUMLOCK Num Lock key.
 * @constant KEY_SCROLL Scroll Lock key.
 * @constant KEY_LSHIFT Left Shift key.
 * @constant KEY_RSHIFT Right Shift key.
 * @constant KEY_LCONTROL Left Control key.
 * @constant KEY_RCONTROL Right Control key.
 * @constant KEY_LALT Left Alt key.
 * @constant KEY_RALT Right Alt key.
 * @constant KEY_SEMICOLON Semicolon key.
 * @constant KEY_EQUALS Equals key.
 * @constant KEY_COMMA Comma key.
 * @constant KEY_MINUS Minus key.
 * @constant KEY_DOT Period key.
 * @constant KEY_SLASH Slash key.
 * @constant KEY_BACKTICK Backtick key.
 * @constant KEY_LSQUARE Left square bracket key.
 * @constant KEY_BACKSLASH Backslash key.
 * @constant KEY_RSQUARE Right square bracket key.
 * @constant KEY_TICK Tick/Quote key.
 */
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

/*!
 * @enum CCCP_ModifierKey
 * @brief Modifier key flags for keyboard input.
 * @constant KEY_MOD_SHIFT Shift modifier key.
 * @constant KEY_MOD_CONTROL Control modifier key.
 * @constant KEY_MOD_ALT Alt modifier key.
 * @constant KEY_MOD_SUPER Super/Windows modifier key.
 * @constant KEY_MOD_CAPS_LOCK Caps Lock modifier.
 * @constant KEY_MOD_NUM_LOCK Num Lock modifier.
 */
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

/*!
 * @typedef CCCP_State
 * @brief Opaque type representing the application state.
 */
typedef struct CCCP_State CCCP_State;

/*!
 * @enum CCCP_EventType
 * @brief Types of events that can occur in the application.
 * @constant KeyboardEvent Keyboard input event.
 * @constant MouseButtonEvent Mouse button event.
 * @constant MouseMoveEvent Mouse movement event.
 * @constant MouseScrollEvent Mouse scroll event.
 * @constant ResizedEvent Window resize event.
 * @constant FocusEvent Window focus event.
 */
typedef enum {
#define X(NAME, ARGS) NAME##Event,
    CCCP_CALLBACKS
#undef X
} CCCP_EventType;

/*!
 * @struct CCCP_Event
 * @brief Represents an input event in the application.
 * @field mouse Mouse-related event data.
 * @field mouse.button Mouse button number.
 * @field mouse.down Whether the mouse button is pressed (1) or released (0).
 * @field mouse.position Mouse position coordinates.
 * @field mouse.position.x Mouse X coordinate.
 * @field mouse.position.y Mouse Y coordinate.
 * @field mouse.position.dx Mouse delta X.
 * @field mouse.position.dy Mouse delta Y.
 * @field mouse.wheel Mouse wheel scroll data.
 * @field mouse.wheel.dx Horizontal scroll delta.
 * @field mouse.wheel.dy Vertical scroll delta.
 * @field keyboard Keyboard-related event data.
 * @field keyboard.key The key that was pressed or released.
 * @field keyboard.down Whether the key is pressed (1) or released (0).
 * @field modifier Modifier keys that are currently pressed.
 * @field window Window-related event data.
 * @field window.focused Whether the window is focused (1) or not (0).
 * @field window.closed Whether the window is closed (1) or not (0).
 * @field window.size Window dimensions.
 * @field window.size.width Window width.
 * @field window.size.height Window height.
 * @field type The type of event.
 */
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

/*!
 * @typedef CCCP_ShaderFunc
 * @brief Function pointer type for shader functions.
 * @param fragcoord Fragment coordinates (vec2).
 * @param resolution Surface resolution (vec2).
 * @param time Current time (float).
 * @param userdata User-defined data pointer.
 * @return Color value (vec4).
 */
typedef vec4(*CCCP_ShaderFunc)(vec2, vec2, float, void*);

/*!
 * @struct CCCP_Shader
 * @brief Represents a shader for surface processing.
 * @field func Pointer to the shader function.
 * @field thread_count Number of threads to use (0 = use hardware concurrency).
 */
typedef struct {
    CCCP_ShaderFunc func;
    int thread_count; // 0 = use hardware concurrency
} CCCP_Shader;

/*!
 * @struct CCCP_HashEntry
 * @brief Represents an entry in a hash table.
 * @field key The key string.
 * @field value The value pointer.
 * @field next Pointer to the next entry in the chain.
 */
typedef struct CCCP_HashEntry {
    const char* key;
    void* value;
    struct CCCP_HashEntry* next;
} CCCP_HashEntry;

/*!
 * @struct CCCP_HashTable
 * @brief Represents a hash table data structure.
 * @field buckets Array of bucket pointers.
 * @field capacity Maximum number of buckets.
 * @field size Current number of entries.
 * @field free_callback Function to free values when destroying the table.
 */
typedef struct {
    CCCP_HashEntry** buckets;
    size_t capacity;
    size_t size;
    void(*free_callback)(void*);
} CCCP_HashTable;

/*!
 * @typedef CCCP_Font
 * @brief Opaque type representing a font.
 */
typedef struct CCCP_Font CCCP_Font;

/*!
 * @struct CCCP_AudioContext
 * @brief Context for managing audio resources.
 * @field volume Master volume level.
 * @field waves Hash table of wave resources.
 * @field sounds Hash table of sound resources.
 * @field music Hash table of music resources.
 */
typedef struct CCCP_AudioContext {
    float volume;
    CCCP_HashTable *waves;
    CCCP_HashTable *sounds;
    CCCP_HashTable *music;
} CCCP_AudioContext;

/*!
 * @struct CCCP_Scene
 * @brief Configuration structure for a scene in the application.
 * @field windowWidth Initial window width.
 * @field windowHeight Initial window height.
 * @field windowTitle Window title string.
 * @field clearColor Background clear color.
 * @field targetFPS Target frames per second.
 * @field init Function called to initialize the scene state.
 * @field deinit Function called to deinitialize the scene state.
 * @field reload Function called when the scene is reloaded.
 * @field unload Function called when the scene is unloaded.
 * @field event Function called to handle events.
 * @field tick Function called each frame to update the scene.
 */
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

/*!
 * @function CCCP_NewSurface
 * @brief Creates a new surface with the specified dimensions and clear color.
 * @param w Width of the surface.
 * @param h Height of the surface.
 * @param clearColor Initial clear color for the surface.
 * @return A new CCCP_Surface.
 */
CCCP_Surface CCCP_NewSurface(unsigned int w, unsigned int h, color_t clearColor);

/*!
 * @function CCCP_SurfaceFromMemory
 * @brief Creates a surface from raw pixel data in memory.
 * @param data Pointer to the pixel data.
 * @param width Width of the image.
 * @param height Height of the image.
 * @param format Format of the pixel data.
 * @return A new CCCP_Surface.
 */
CCCP_Surface CCCP_SurfaceFromMemory(const void* data, int width, int height, bitmap_format_t format);

/*!
 * @function CCCP_SurfaceFromFile
 * @brief Loads a surface from an image file.
 * @param filename Path to the image file.
 * @return A new CCCP_Surface, or NULL on failure.
 */
CCCP_Surface CCCP_SurfaceFromFile(const char* filename);

/*!
 * @function CCCP_CopySurface
 * @brief Creates a copy of an existing surface.
 * @param surface The surface to copy.
 * @return A new CCCP_Surface that is a copy of the input.
 */
CCCP_Surface CCCP_CopySurface(CCCP_Surface surface);

/*!
 * @function CCCP_DestroySurface
 * @brief Destroys a surface and frees its memory.
 * @param surface The surface to destroy.
 */
void CCCP_DestroySurface(CCCP_Surface surface);

/*!
 * @function CCCP_SurfaceWidth
 * @brief Gets the width of a surface.
 * @param surface The surface.
 * @return The width of the surface.
 */
int CCCP_SurfaceWidth(CCCP_Surface surface);

/*!
 * @function CCCP_SurfaceHeight
 * @brief Gets the height of a surface.
 * @param surface The surface.
 * @return The height of the surface.
 */
int CCCP_SurfaceHeight(CCCP_Surface surface);

/*!
 * @function CCCP_ClearSurface
 * @brief Clears the surface with the specified color.
 * @param surface The surface to clear.
 * @param clearColor The color to clear with.
 */
void CCCP_ClearSurface(CCCP_Surface surface, color_t clearColor);

/*!
 * @function CCCP_SetPixel
 * @brief Sets the color of a pixel at the specified coordinates.
 * @param surface The surface.
 * @param x X coordinate of the pixel.
 * @param y Y coordinate of the pixel.
 * @param color The color to set.
 * @return true if the pixel was set successfully, false otherwise.
 */
bool CCCP_SetPixel(CCCP_Surface surface, int x, int y, color_t color);

/*!
 * @function CCCP_GetPixel
 * @brief Gets the color of a pixel at the specified coordinates.
 * @param surface The surface.
 * @param x X coordinate of the pixel.
 * @param y Y coordinate of the pixel.
 * @return The color of the pixel.
 */
color_t CCCP_GetPixel(CCCP_Surface surface, int x, int y);

/*!
 * @function CCCP_BlitSurface
 * @brief Blits one surface onto another at the specified position.
 * @param dest The destination surface.
 * @param src The source surface.
 * @param x X coordinate on the destination surface.
 * @param y Y coordinate on the destination surface.
 */
void CCCP_BlitSurface(CCCP_Surface dest, CCCP_Surface src, int x, int y);

/*!
 * @function CCCP_BlitSurfaceRect
 * @brief Blits a rectangular region from one surface to another.
 * @param dest The destination surface.
 * @param src The source surface.
 * @param srcX X coordinate of the source rectangle.
 * @param srcY Y coordinate of the source rectangle.
 * @param srcW Width of the source rectangle.
 * @param srcH Height of the source rectangle.
 * @param destX X coordinate on the destination surface.
 * @param destY Y coordinate on the destination surface.
 */
void CCCP_BlitSurfaceRect(CCCP_Surface dest, CCCP_Surface src, int srcX, int srcY, int srcW, int srcH, int destX, int destY);

/*!
 * @function CCCP_DrawLine
 * @brief Draws a line between two points.
 * @param surface The surface to draw on.
 * @param x1 X coordinate of the start point.
 * @param y1 Y coordinate of the start point.
 * @param x2 X coordinate of the end point.
 * @param y2 Y coordinate of the end point.
 * @param color The color of the line.
 */
void CCCP_DrawLine(CCCP_Surface surface, int x1, int y1, int x2, int y2, color_t color);

/*!
 * @function CCCP_DrawRect
 * @brief Draws a rectangle.
 * @param surface The surface to draw on.
 * @param x X coordinate of the rectangle.
 * @param y Y coordinate of the rectangle.
 * @param w Width of the rectangle.
 * @param h Height of the rectangle.
 * @param color The color of the rectangle.
 * @param filled Whether the rectangle should be filled.
 */
void CCCP_DrawRect(CCCP_Surface surface, int x, int y, int w, int h, color_t color, bool filled);

/*!
 * @function CCCP_DrawCircle
 * @brief Draws a circle.
 * @param surface The surface to draw on.
 * @param x X coordinate of the circle center.
 * @param y Y coordinate of the circle center.
 * @param radius Radius of the circle.
 * @param color The color of the circle.
 * @param filled Whether the circle should be filled.
 */
void CCCP_DrawCircle(CCCP_Surface surface, int x, int y, int radius, color_t color, bool filled);

/*!
 * @function CCCP_DrawTriangle
 * @brief Draws a triangle.
 * @param surface The surface to draw on.
 * @param x1 X coordinate of the first vertex.
 * @param y1 Y coordinate of the first vertex.
 * @param x2 X coordinate of the second vertex.
 * @param y2 Y coordinate of the second vertex.
 * @param x3 X coordinate of the third vertex.
 * @param y3 Y coordinate of the third vertex.
 * @param color The color of the triangle.
 * @param filled Whether the triangle should be filled.
 */
void CCCP_DrawTriangle(CCCP_Surface surface, int x1, int y1, int x2, int y2, int x3, int y3, color_t color, bool filled);

/*!
 * @function CCCP_ResizeSurface
 * @brief Resizes a surface to new dimensions.
 * @param surface The surface to resize.
 * @param w New width.
 * @param h New height.
 * @return A new resized surface.
 */
CCCP_Surface CCCP_ResizeSurface(CCCP_Surface surface, unsigned int w, unsigned int h);

/*!
 * @function CCCP_RotateSurface
 * @brief Rotates a surface by the specified angle.
 * @param surface The surface to rotate.
 * @param angle Rotation angle in radians.
 * @return A new rotated surface.
 */
CCCP_Surface CCCP_RotateSurface(CCCP_Surface surface, float angle);

/*!
 * @function CCCP_FlipSurface
 * @brief Flips a surface horizontally and/or vertically.
 * @param surface The surface to flip.
 * @param horizontal Whether to flip horizontally.
 * @param vertical Whether to flip vertically.
 * @return A new flipped surface.
 */
CCCP_Surface CCCP_FlipSurface(CCCP_Surface surface, bool horizontal, bool vertical);

/*!
 * @function CCCP_ClipSurface
 * @brief Clips a surface to a rectangular region.
 * @param surface The surface to clip.
 * @param x X coordinate of the clip rectangle.
 * @param y Y coordinate of the clip rectangle.
 * @param w Width of the clip rectangle.
 * @param h Height of the clip rectangle.
 * @return A new clipped surface.
 */
CCCP_Surface CCCP_ClipSurface(CCCP_Surface surface, int x, int y, int w, int h);

/*!
 * @function CCCP_SurfaceFromPerlinNoise
 * @brief Creates a surface filled with Perlin noise.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param scale Scale of the noise.
 * @param offsetX X offset for the noise.
 * @param offsetY Y offset for the noise.
 * @return A new surface with Perlin noise.
 */
CCCP_Surface CCCP_SurfaceFromPerlinNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);

/*!
 * @function CCCP_SurfaceFromSimplexNoise
 * @brief Creates a surface filled with Simplex noise.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param scale Scale of the noise.
 * @param offsetX X offset for the noise.
 * @param offsetY Y offset for the noise.
 * @return A new surface with Simplex noise.
 */
CCCP_Surface CCCP_SurfaceFromSimplexNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);

/*!
 * @function CCCP_SurfaceFromWorleyNoise
 * @brief Creates a surface filled with Worley noise.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param scale Scale of the noise.
 * @param offsetX X offset for the noise.
 * @param offsetY Y offset for the noise.
 * @return A new surface with Worley noise.
 */
CCCP_Surface CCCP_SurfaceFromWorleyNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);

/*!
 * @function CCCP_SurfaceFromValueNoise
 * @brief Creates a surface filled with value noise.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param scale Scale of the noise.
 * @param offsetX X offset for the noise.
 * @param offsetY Y offset for the noise.
 * @return A new surface with value noise.
 */
CCCP_Surface CCCP_SurfaceFromValueNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);

/*!
 * @function CCCP_SurfaceFromWhiteNoise
 * @brief Creates a surface filled with white noise.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param scale Scale of the noise.
 * @param offsetX X offset for the noise.
 * @param offsetY Y offset for the noise.
 * @return A new surface with white noise.
 */
CCCP_Surface CCCP_SurfaceFromWhiteNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY);

/*!
 * @function CCCP_SurfaceFromFBMNoise
 * @brief Creates a surface filled with Fractional Brownian Motion noise.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param scale Scale of the noise.
 * @param offsetX X offset for the noise.
 * @param offsetY Y offset for the noise.
 * @param lacunarity Lacunarity parameter for FBM.
 * @param gain Gain parameter for FBM.
 * @param octaves Number of octaves for FBM.
 * @return A new surface with FBM noise.
 */
CCCP_Surface CCCP_SurfaceFromFBMNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY, float lacunarity, float gain, int octaves);

/*!
 * @function CCCP_SurfaceFromHorizontalGradient
 * @brief Creates a surface with a horizontal gradient.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param startColor Starting color of the gradient.
 * @param endColor Ending color of the gradient.
 * @return A new surface with horizontal gradient.
 */
CCCP_Surface CCCP_SurfaceFromHorizontalGradient(unsigned int width, unsigned int height, color_t startColor, color_t endColor);

/*!
 * @function CCCP_SurfaceFromVerticalGradient
 * @brief Creates a surface with a vertical gradient.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param startColor Starting color of the gradient.
 * @param endColor Ending color of the gradient.
 * @return A new surface with vertical gradient.
 */
CCCP_Surface CCCP_SurfaceFromVerticalGradient(unsigned int width, unsigned int height, color_t startColor, color_t endColor);

/*!
 * @function CCCP_SurfaceFromRadialGradient
 * @brief Creates a surface with a radial gradient.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param centerColor Color at the center.
 * @param edgeColor Color at the edges.
 * @return A new surface with radial gradient.
 */
CCCP_Surface CCCP_SurfaceFromRadialGradient(unsigned int width, unsigned int height, color_t centerColor, color_t edgeColor);

/*!
 * @function CCCP_SurfaceFromDiagonalGradient
 * @brief Creates a surface with a diagonal gradient.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param startColor Starting color of the gradient.
 * @param endColor Ending color of the gradient.
 * @return A new surface with diagonal gradient.
 */
CCCP_Surface CCCP_SurfaceFromDiagonalGradient(unsigned int width, unsigned int height, color_t startColor, color_t endColor);

/*!
 * @function CCCP_SurfaceFromCheckerboard
 * @brief Creates a surface with a checkerboard pattern.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param color1 First color of the checkerboard.
 * @param color2 Second color of the checkerboard.
 * @param squareSize Size of each square in the checkerboard.
 * @return A new surface with checkerboard pattern.
 */
CCCP_Surface CCCP_SurfaceFromCheckerboard(unsigned int width, unsigned int height, color_t color1, color_t color2, unsigned int squareSize);

/*!
 * @function CCCP_SurfaceFromHorizontalStripes
 * @brief Creates a surface with horizontal stripes.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param color1 First color of the stripes.
 * @param color2 Second color of the stripes.
 * @param stripeWidth Width of each stripe.
 * @return A new surface with horizontal stripes.
 */
CCCP_Surface CCCP_SurfaceFromHorizontalStripes(unsigned int width, unsigned int height, color_t color1, color_t color2, unsigned int stripeWidth);

/*!
 * @function CCCP_SurfaceFromVerticalStripes
 * @brief Creates a surface with vertical stripes.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param color1 First color of the stripes.
 * @param color2 Second color of the stripes.
 * @param stripeWidth Width of each stripe.
 * @return A new surface with vertical stripes.
 */
CCCP_Surface CCCP_SurfaceFromVerticalStripes(unsigned int width, unsigned int height, color_t color1, color_t color2, unsigned int stripeWidth);

/*!
 * @function CCCP_SurfaceFromConcentricCircles
 * @brief Creates a surface with concentric circles.
 * @param width Width of the surface.
 * @param height Height of the surface.
 * @param centerColor Color at the center.
 * @param edgeColor Color at the edges.
 * @param numRings Number of concentric rings.
 * @return A new surface with concentric circles.
 */
CCCP_Surface CCCP_SurfaceFromConcentricCircles(unsigned int width, unsigned int height, color_t centerColor, color_t edgeColor, unsigned int numRings);

/*!
 * @function CCCP_NewShader
 * @brief Creates a new shader.
 * @param func The shader function.
 * @param numThreads Number of threads to use (0 = hardware concurrency).
 * @return A new CCCP_Shader.
 */
CCCP_Shader CCCP_NewShader(CCCP_ShaderFunc func, int numThreads);

/*!
 * @function CCCP_DestroyShader
 * @brief Destroys a shader.
 * @param shader Pointer to the shader to destroy.
 */
void CCCP_DestroyShader(CCCP_Shader *shader);

/*!
 * @function CCCP_ApplyShader
 * @brief Applies a shader to a surface.
 * @param surface The surface to apply the shader to.
 * @param shader Pointer to the shader.
 * @param userdata User-defined data to pass to the shader function.
 * @return true if the shader was applied successfully, false otherwise.
 */
bool CCCP_ApplyShader(CCCP_Surface surface, CCCP_Shader *shader, void* userdata);

/*!
 * @function CCCP_DebugPrintASCII
 * @brief Prints ASCII text to a surface for debugging.
 * @param surface The surface to print on.
 * @param x X coordinate to start printing.
 * @param y Y coordinate to start printing.
 * @param text The ASCII text to print.
 * @param color The color of the text.
 */
void CCCP_DebugPrintASCII(CCCP_Surface surface, int x, int y, const char* text, color_t color);

/*!
 * @function CCCP_DebugPrintUnicode
 * @brief Prints Unicode text to a surface for debugging.
 * @param surface The surface to print on.
 * @param x X coordinate to start printing.
 * @param y Y coordinate to start printing.
 * @param text The Unicode text to print.
 * @param color The color of the text.
 */
void CCCP_DebugPrintUnicode(CCCP_Surface surface, int x, int y, const wchar_t* text, color_t color);

/* === AUDIO === */

/*!
 * @function CCCP_SetMasterVolume
 * @brief Sets the master volume for all audio.
 * @param ctx The audio context.
 * @param volume The volume level (0.0 to 1.0).
 */
void CCCP_SetMasterVolume(CCCP_AudioContext* ctx, float volume);

/*!
 * @function CCCP_GetMasterVolume
 * @brief Gets the current master volume.
 * @param ctx The audio context.
 * @return The current master volume (0.0 to 1.0).
 */
float CCCP_GetMasterVolume(CCCP_AudioContext* ctx);

/*!
 * @function CCCP_NewWaveFromMemory
 * @brief Creates a new wave from data in memory.
 * @param ctx The audio context.
 * @param key The key to associate with the wave.
 * @param data The wave data.
 * @param dataSize Size of the data in bytes.
 * @return true if the wave was created successfully, false otherwise.
 */
bool CCCP_NewWaveFromMemory(CCCP_AudioContext* ctx, const char* key, const void* data, int dataSize);

/*!
 * @function CCCP_NewWaveFromFile
 * @brief Creates a new wave from a file.
 * @param ctx The audio context.
 * @param key The key to associate with the wave.
 * @param filename Path to the wave file.
 * @return true if the wave was created successfully, false otherwise.
 */
bool CCCP_NewWaveFromFile(CCCP_AudioContext* ctx, const char* key, const char* filename);

/*!
 * @function CCCP_DestroyWave
 * @brief Destroys a wave.
 * @param ctx The audio context.
 * @param key The key of the wave to destroy.
 * @return true if the wave was destroyed successfully, false otherwise.
 */
bool CCCP_DestroyWave(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_NewSoundFromWave
 * @brief Creates a new sound from an existing wave.
 * @param ctx The audio context.
 * @param key The key to associate with the sound.
 * @param waveKey The key of the wave to use.
 * @return true if the sound was created successfully, false otherwise.
 */
bool CCCP_NewSoundFromWave(CCCP_AudioContext* ctx, const char* key, const char* waveKey);

/*!
 * @function CCCP_NewSoundFromFile
 * @brief Creates a new sound from a file.
 * @param ctx The audio context.
 * @param key The key to associate with the sound.
 * @param filename Path to the sound file.
 * @return true if the sound was created successfully, false otherwise.
 */
bool CCCP_NewSoundFromFile(CCCP_AudioContext* ctx, const char* key, const char* filename);

/*!
 * @function CCCP_DestroySound
 * @brief Destroys a sound.
 * @param ctx The audio context.
 * @param key The key of the sound to destroy.
 * @return true if the sound was destroyed successfully, false otherwise.
 */
bool CCCP_DestroySound(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_NewMusicFromMemory
 * @brief Creates new music from data in memory.
 * @param ctx The audio context.
 * @param key The key to associate with the music.
 * @param data The music data.
 * @param dataSize Size of the data in bytes.
 * @return true if the music was created successfully, false otherwise.
 */
bool CCCP_NewMusicFromMemory(CCCP_AudioContext* ctx, const char* key, const void* data, int dataSize);

/*!
 * @function CCCP_NewMusicFromFile
 * @brief Creates new music from a file.
 * @param ctx The audio context.
 * @param key The key to associate with the music.
 * @param filename Path to the music file.
 * @return true if the music was created successfully, false otherwise.
 */
bool CCCP_NewMusicFromFile(CCCP_AudioContext* ctx, const char* key, const char* filename);

/*!
 * @function CCCP_DestroyMusic
 * @brief Destroys music.
 * @param ctx The audio context.
 * @param key The key of the music to destroy.
 * @return true if the music was destroyed successfully, false otherwise.
 */
bool CCCP_DestroyMusic(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_UnloadAllWaves
 * @brief Unloads all waves from the audio context.
 * @param ctx The audio context.
 */
void CCCP_UnloadAllWaves(CCCP_AudioContext* ctx);

/*!
 * @function CCCP_UnloadAllSounds
 * @brief Unloads all sounds from the audio context.
 * @param ctx The audio context.
 */
void CCCP_UnloadAllSounds(CCCP_AudioContext* ctx);

/*!
 * @function CCCP_UnloadAllMusic
 * @brief Unloads all music from the audio context.
 * @param ctx The audio context.
 */
void CCCP_UnloadAllMusic(CCCP_AudioContext* ctx);

/*!
 * @function CCCP_IsWaveReady
 * @brief Checks if a wave is ready to use.
 * @param ctx The audio context.
 * @param key The key of the wave.
 * @return true if the wave is ready, false otherwise.
 */
bool CCCP_IsWaveReady(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_IsSoundReady
 * @brief Checks if a sound is ready to use.
 * @param ctx The audio context.
 * @param key The key of the sound.
 * @return true if the sound is ready, false otherwise.
 */
bool CCCP_IsSoundReady(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_IsMusicReady
 * @brief Checks if music is ready to use.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @return true if the music is ready, false otherwise.
 */
bool CCCP_IsMusicReady(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_UpdateSound
 * @brief Updates sound data.
 * @param ctx The audio context.
 * @param key The key of the sound.
 * @param data The new sound data.
 * @param frameCount Number of frames in the data.
 */
void CCCP_UpdateSound(CCCP_AudioContext* ctx, const char* key, const void *data, int frameCount);

/*!
 * @function CCCP_UpdateMusic
 * @brief Updates music data.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @param data The new music data.
 * @param sampleCount Number of samples in the data.
 */
void CCCP_UpdateMusic(CCCP_AudioContext* ctx, const char* key, const void *data, int sampleCount);

/*!
 * @function CCCP_PlaySound
 * @brief Plays a sound.
 * @param ctx The audio context.
 * @param key The key of the sound to play.
 */
void CCCP_PlaySound(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_StopSound
 * @brief Stops a sound.
 * @param ctx The audio context.
 * @param key The key of the sound to stop.
 */
void CCCP_StopSound(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_PauseSound
 * @brief Pauses a sound.
 * @param ctx The audio context.
 * @param key The key of the sound to pause.
 */
void CCCP_PauseSound(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_ResumeSound
 * @brief Resumes a paused sound.
 * @param ctx The audio context.
 * @param key The key of the sound to resume.
 */
void CCCP_ResumeSound(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_IsSoundPlaying
 * @brief Checks if a sound is currently playing.
 * @param ctx The audio context.
 * @param key The key of the sound.
 * @return true if the sound is playing, false otherwise.
 */
bool CCCP_IsSoundPlaying(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_SetSoundVolume
 * @brief Sets the volume of a sound.
 * @param ctx The audio context.
 * @param key The key of the sound.
 * @param volume The volume level (0.0 to 1.0).
 */
void CCCP_SetSoundVolume(CCCP_AudioContext* ctx, const char* key, float volume);

/*!
 * @function CCCP_GetSoundVolume
 * @brief Gets the volume of a sound.
 * @param ctx The audio context.
 * @param key The key of the sound.
 * @return The current volume level (0.0 to 1.0).
 */
float CCCP_GetSoundVolume(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_PlayMusic
 * @brief Plays music.
 * @param ctx The audio context.
 * @param key The key of the music to play.
 */
void CCCP_PlayMusic(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_StopMusic
 * @brief Stops music.
 * @param ctx The audio context.
 * @param key The key of the music to stop.
 */
void CCCP_StopMusic(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_PauseMusic
 * @brief Pauses music.
 * @param ctx The audio context.
 * @param key The key of the music to pause.
 */
void CCCP_PauseMusic(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_ResumeMusic
 * @brief Resumes paused music.
 * @param ctx The audio context.
 * @param key The key of the music to resume.
 */
void CCCP_ResumeMusic(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_IsMusicPlaying
 * @brief Checks if music is currently playing.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @return true if the music is playing, false otherwise.
 */
bool CCCP_IsMusicPlaying(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_SetMusicVolume
 * @brief Sets the volume of music.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @param volume The volume level (0.0 to 1.0).
 */
void CCCP_SetMusicVolume(CCCP_AudioContext* ctx, const char* key, float volume);

/*!
 * @function CCCP_GetMusicVolume
 * @brief Gets the volume of music.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @return The current volume level (0.0 to 1.0).
 */
float CCCP_GetMusicVolume(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_SeekMusic
 * @brief Seeks to a position in the music.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @param position The position to seek to (in seconds).
 */
void CCCP_SeekMusic(CCCP_AudioContext* ctx, const char* key, float position);

/*!
 * @function CCCP_GetMusicTimeLength
 * @brief Gets the total length of the music.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @return The total length in seconds.
 */
float CCCP_GetMusicTimeLength(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_GetMusicTimePlayed
 * @brief Gets the current playback position of the music.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @return The current position in seconds.
 */
float CCCP_GetMusicTimePlayed(CCCP_AudioContext* ctx, const char* key);

/*!
 * @function CCCP_SetMusicLooping
 * @brief Sets whether music should loop.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @param looping Whether to enable looping.
 */
void CCCP_SetMusicLooping(CCCP_AudioContext* ctx, const char* key, bool looping);

/*!
 * @function CCCP_IsMusicLooping
 * @brief Checks if music is set to loop.
 * @param ctx The audio context.
 * @param key The key of the music.
 * @return true if looping is enabled, false otherwise.
 */
bool CCCP_IsMusicLooping(CCCP_AudioContext* ctx, const char* key);

/* === TIMER === */

/*!
 * @typedef CCCP_Timer
 * @brief Opaque type representing a timer.
 */
typedef struct CCCP_Timer CCCP_Timer;

/*!
 * @function CCCP_NewTimer
 * @brief Creates a new timer.
 * @return A new CCCP_Timer.
 */
CCCP_Timer* CCCP_NewTimer(void);

/*!
 * @function CCCP_DestroyTimer
 * @brief Destroys a timer.
 * @param timer The timer to destroy.
 */
void CCCP_DestroyTimer(CCCP_Timer* timer);

/*!
 * @function CCCP_StartTimer
 * @brief Starts a timer.
 * @param timer The timer to start.
 */
void CCCP_StartTimer(CCCP_Timer* timer);

/*!
 * @function CCCP_StopTimer
 * @brief Stops a timer.
 * @param timer The timer to stop.
 */
void CCCP_StopTimer(CCCP_Timer* timer);

/*!
 * @function CCCP_PauseTimer
 * @brief Pauses a timer.
 * @param timer The timer to pause.
 */
void CCCP_PauseTimer(CCCP_Timer* timer);

/*!
 * @function CCCP_ResumeTimer
 * @brief Resumes a paused timer.
 * @param timer The timer to resume.
 */
void CCCP_ResumeTimer(CCCP_Timer* timer);

/*!
 * @function CCCP_GetElapsedTime
 * @brief Gets the elapsed time of a timer.
 * @param timer The timer.
 * @return The elapsed time in seconds.
 */
double CCCP_GetElapsedTime(CCCP_Timer* timer);

/*!
 * @function CCCP_Sleep
 * @brief Sleeps for the specified number of seconds.
 * @param seconds The number of seconds to sleep.
 */
void CCCP_Sleep(double seconds);

/* === HASH TABLE === */

/*!
 * @function CCCP_NewHashTable
 * @brief Creates a new hash table.
 * @param capacity Initial capacity of the hash table.
 * @return A new CCCP_HashTable.
 */
CCCP_HashTable* CCCP_NewHashTable(size_t capacity);

/*!
 * @function CCCP_DestroyHashTable
 * @brief Destroys a hash table.
 * @param table The hash table to destroy.
 */
void CCCP_DestroyHashTable(CCCP_HashTable* table);

/*!
 * @function CCCP_HashTableInsert
 * @brief Inserts a key-value pair into the hash table.
 * @param table The hash table.
 * @param key The key string.
 * @param value The value pointer.
 * @return 0 on success, non-zero on failure.
 */
int CCCP_HashTableInsert(CCCP_HashTable* table, const char* key, void* value);

/*!
 * @function CCCP_HashTableGet
 * @brief Gets a value from the hash table.
 * @param table The hash table.
 * @param key The key string.
 * @return The value pointer, or NULL if not found.
 */
void* CCCP_HashTableGet(CCCP_HashTable* table, const char* key);

/*!
 * @function CCCP_HashTableRemove
 * @brief Removes a key-value pair from the hash table.
 * @param table The hash table.
 * @param key The key string.
 * @return 0 on success, non-zero on failure.
 */
int CCCP_HashTableRemove(CCCP_HashTable* table, const char* key);

/*!
 * @function CCCP_HashTableSize
 * @brief Gets the number of entries in the hash table.
 * @param table The hash table.
 * @return The number of entries.
 */
size_t CCCP_HashTableSize(CCCP_HashTable* table);

/*!
 * @function CCCP_HashTableClear
 * @brief Clears all entries from the hash table.
 * @param table The hash table.
 */
void CCCP_HashTableClear(CCCP_HashTable* table);

/* === FONT === */

/*!
 * @function CCCP_LoadFont
 * @brief Loads a font from a file.
 * @param filename Path to the font file.
 * @return A new CCCP_Font, or NULL on failure.
 */
CCCP_Font* CCCP_LoadFont(const char* filename);

/*!
 * @function CCCP_DestroyFont
 * @brief Destroys a font.
 * @param font The font to destroy.
 */
void CCCP_DestroyFont(CCCP_Font* font);

/*!
 * @function CCCP_DrawText
 * @brief Draws text to a surface using a font.
 * @param surface The surface to draw on.
 * @param font The font to use.
 * @param x X coordinate to start drawing.
 * @param y Y coordinate to start drawing.
 * @param text The text to draw.
 * @param color The color of the text.
 * @param size The size of the text.
 */
void CCCP_DrawText(CCCP_Surface surface, CCCP_Font* font, int x, int y, const char* text, color_t color, float size);

#ifdef __cplusplus
}
#endif
#endif // CCCP_H