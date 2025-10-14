/* paul/paul_bitmap.h -- https://github.com/takeiteasy/paul

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
 along with this program.  If not, see <https://www.gnu.org/licenses/>. */

 /*!
 @header paul_bitmap.h
 @copyright George Watson GPLv3
 @updated 2025-09-29
 @brief Bitmap manipulation library for C/C++.
 @discussion
    Implementation is included when PAUL_BITMAP_IMPLEMENTATION or PAUL_IMPLEMENTATION is defined.
*/

#ifndef PAUL_BITMAP_HEADER
#define PAUL_BITMAP_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#ifdef _WIN32
#include <io.h>
#include <dirent.h>
#define F_OK 0
#define access _access
#else
#include <unistd.h>
#endif
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef PAUL_COLOR_HEADER
#ifndef __has_include
#define __has_include(x) 0
#endif
#if __has_include("paul_color.h")
#if defined(PAUL_BITMAP_IMPLEMENTATION) && !(defined(PAUL_COLOR_IMPLEMENTATION) || defined(PAUL_IMPLEMENTATION))
#define PAUL_COLOR_IMPLEMENTATION
#endif
#include "paul_color.h"
#else
/*! @typedef color_t
    @brief Represents a color with red, green, blue, and alpha components.
    @field r Red component (0-255)
    @field g Green component (0-255)
    @field b Blue component (0-255)
    @field a Alpha component (0-255)
    @field rgba Packed RGBA value as 32-bit integer
*/
typedef union color_t {
    struct {
        uint8_t r, g, b, a;
    };
    uint32_t rgba;
} color_t;
#endif
#endif

/*! @typedef bitmap_t
    @brief Represents an RGBA color with 8 bits per channel.
*/
typedef color_t* bitmap_t;

/*!
 * @function bitmap_empty
 * @brief Creates a new empty image filled with a specified color.
 * @discussion Allocates memory for a new image of the specified width and height, initializing all pixels to the given color. The returned image must be freed with bitmap_destroy() when no longer needed.
 * @param w The width of the image in pixels.
 * @param h The height of the image in pixels.
 * @param color The color to fill the image with.
 * @return A pointer to the new image, or NULL on allocation failure.
*/
bitmap_t bitmap_empty(unsigned int w, unsigned int h, color_t color);

/*!
 * @function bitmap_destroy
 * @brief Frees the memory associated with an image.
 * @discussion Releases all memory allocated for the image. The image pointer becomes invalid after this call and should not be used.
 * @param img The image to destroy.
*/
void bitmap_destroy(bitmap_t img);

/*!
 * @function bitmap_width
 * @brief Gets the width of an image in pixels.
 * @discussion Returns the width dimension of the image.
 * @param img The image to query.
 * @return The width of the image in pixels.
*/
int bitmap_width(const bitmap_t img);

/*!
 * @function bitmap_height
 * @brief Gets the height of an image in pixels.
 * @discussion Returns the height dimension of the image.
 * @param img The image to query.
 * @return The height of the image in pixels.
*/
int bitmap_height(const bitmap_t img);

/*!
 * @function bitmap_size
 * @brief Gets both width and height of an image.
 * @discussion Retrieves the dimensions of the image, storing them in the provided pointers. This is more efficient than calling bitmap_width() and bitmap_height() separately.
 * @param img The image to query.
 * @param w Pointer to store the width (can be NULL if not needed).
 * @param h Pointer to store the height (can be NULL if not needed).
 * @return true if successful, false if the image is invalid.
*/
bool bitmap_size(const bitmap_t img, int *w, int *h);

/*!
 * @function bitmap_pset
 * @brief Sets the color of a pixel at the specified coordinates.
 * @discussion Changes the color of the pixel at position (x, y). Coordinates are zero-based, with (0,0) being the top-left corner. If coordinates are out of bounds, the operation fails.
 * @param img The image to modify.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The new color for the pixel.
 * @return true if successful, false if coordinates are out of bounds or image is invalid.
*/
bool bitmap_pset(bitmap_t img, int x, int y, color_t color);

/*!
 * @function bitmap_pget
 * @brief Gets the color of a pixel at the specified coordinates.
 * @discussion Retrieves the color of the pixel at position (x, y). Coordinates are zero-based, with (0,0) being the top-left corner. If coordinates are out of bounds, returns a default color.
 * @param img The image to query.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return The color of the pixel, or a default color if coordinates are out of bounds.
*/
color_t bitmap_pget(const bitmap_t img, int x, int y);

/*!
 * @function bitmap_fill
 * @brief Fills the entire image with a solid color.
 * @discussion Sets all pixels in the image to the specified color, effectively clearing the image to a uniform color.
 * @param img The image to fill.
 * @param color The color to fill the image with.
 * @return true if successful, false if the image is invalid.
*/
bool bitmap_fill(bitmap_t img, color_t color);

/*!
 * @function bitmap_flood
 * @brief Performs a flood fill starting from the specified coordinates.
 * @discussion Fills a contiguous region of pixels with the same color as the starting pixel with a new color. Uses 4-way connectivity (up, down, left, right).
 * @param img The image to modify.
 * @param x The x-coordinate of the starting pixel.
 * @param y The y-coordinate of the starting pixel.
 * @param color The new color to fill the region with.
 * @return true if successful, false if coordinates are out of bounds or image is invalid.
*/
bool bitmap_flood(bitmap_t img, int x, int y, color_t color);

/*!
 * @function bitmap_paste
 * @brief Pastes one image onto another at the specified position.
 * @discussion Copies all pixels from the source image onto the destination image starting at position (x, y). The source image is pasted over the destination without any alpha blending.
 * @param dst The destination image to paste onto.
 * @param src The source image to paste from.
 * @param x The x-coordinate in the destination where to paste.
 * @param y The y-coordinate in the destination where to paste.
 * @return true if successful, false if images are invalid or operation would exceed bounds.
*/
bool bitmap_paste(bitmap_t dst, const bitmap_t src, int x, int y);

/*!
 * @function bitmap_clipped_paste
 * @brief Pastes a rectangular region from one image to another.
 * @discussion Copies a rectangular region (rx, ry, rw, rh) from the source image onto the destination image at position (x, y). Only the specified region of the source is copied.
 * @param dst The destination image to paste onto.
 * @param src The source image to paste from.
 * @param x The x-coordinate in the destination where to paste.
 * @param y The y-coordinate in the destination where to paste.
 * @param rx The x-coordinate of the region in the source image.
 * @param ry The y-coordinate of the region in the source image.
 * @param rw The width of the region in the source image.
 * @param rh The height of the region in the source image.
 * @return true if successful, false if images are invalid or operation would exceed bounds.
*/
bool bitmap_clipped_paste(bitmap_t dst, const bitmap_t src, int x, int y, int rx, int ry, int rw, int rh);

/*!
 * @function bitmap_resize
 * @brief Resizes an image in-place to new dimensions.
 * @discussion Changes the size of the image to the specified width and height. The original image data is lost and replaced with resized content. Uses nearest-neighbor interpolation.
 * @param src Pointer to the image to resize (will be modified).
 * @param nw The new width for the image.
 * @param nh The new height for the image.
 * @return true if successful, false if allocation fails or image is invalid.
*/
bool bitmap_resize(bitmap_t *src, int nw, int nh);

/*!
 * @function bitmap_rotate
 * @brief Rotates an image in-place by the specified angle.
 * @discussion Rotates the image around its center by the given angle in degrees. Positive angles rotate clockwise. The image dimensions may change to accommodate the rotated content.
 * @param src Pointer to the image to rotate (will be modified).
 * @param angle The rotation angle in degrees.
 * @return true if successful, false if allocation fails or image is invalid.
*/
bool bitmap_rotate(bitmap_t *src, float angle);

/*!
 * @function bitmap_clip
 * @brief Clips a rectangular region from an image in-place.
 * @discussion Extracts a rectangular region from the image, making it the new image content. The original image is replaced with just the clipped region.
 * @param src Pointer to the image to clip (will be modified).
 * @param rx The x-coordinate of the region to keep.
 * @param ry The y-coordinate of the region to keep.
 * @param rw The width of the region to keep.
 * @param rh The height of the region to keep.
 * @return true if successful, false if region is invalid or image is invalid.
*/
bool bitmap_clip(bitmap_t *src, int rx, int ry, int rw, int rh);

/*!
 * @function bitmap_dupe
 * @brief Creates a duplicate copy of an image.
 * @discussion Allocates a new image with the same dimensions and pixel data as the source image. The returned image is independent and must be freed with bitmap_destroy() when no longer needed.
 * @param src The source image to duplicate.
 * @return A new image that is a copy of the source, or NULL on allocation failure.
*/
bitmap_t bitmap_dupe(bitmap_t src);

/*!
 * @function bitmap_resized
 * @brief Creates a resized copy of an image.
 * @discussion Allocates a new image with the specified dimensions and copies the source image content resized to fit. Uses nearest-neighbor interpolation. The original image remains unchanged.
 * @param src The source image to resize.
 * @param nw The width of the new image.
 * @param nh The height of the new image.
 * @return A new resized image, or NULL on allocation failure.
*/
bitmap_t bitmap_resized(bitmap_t src, int nw, int nh);

/*!
 * @function bitmap_rotated
 * @brief Creates a rotated copy of an image.
 * @discussion Allocates a new image and copies the source image content rotated by the specified angle. The original image remains unchanged.
 * @param src The source image to rotate.
 * @param angle The rotation angle in degrees.
 * @return A new rotated image, or NULL on allocation failure.
*/
bitmap_t bitmap_rotated(bitmap_t src, float angle);

/*!
 * @function bitmap_clipped
 * @brief Creates a new image from a rectangular region of another image.
 * @discussion Allocates a new image containing only the specified rectangular region from the source image. The original image remains unchanged.
 * @param src The source image to clip from.
 * @param rx The x-coordinate of the region in the source image.
 * @param ry The y-coordinate of the region in the source image.
 * @param rw The width of the region.
 * @param rh The height of the region.
 * @return A new image containing the clipped region, or NULL on allocation failure.
*/
bitmap_t bitmap_clipped(bitmap_t src, int rx, int ry, int rw, int rh);

/*!
 * @function bitmap_flipped
 * @brief Creates a flipped copy of an image.
 * @discussion Allocates a new image that is a horizontally and/or vertically flipped version of the source image. The original image remains unchanged.
 * @param src The source image to flip.
 * @param horizontal Non-zero to flip horizontally, zero to keep original orientation.
 * @param vertical Non-zero to flip vertically, zero to keep original orientation.
 * @return A new flipped image, or NULL on allocation failure.
*/
bitmap_t bitmap_flipped(bitmap_t src, int horizontal, int vertical);

/*!
 * @function bitmap_clipped
 * @brief Creates a new image from a rectangular region of another image.
 * @discussion Allocates a new image containing only the specified rectangular region from the source image. The original image remains unchanged.
 * @param src The source image to clip from.
 * @param rx The x-coordinate of the region in the source image.
 * @param ry The y-coordinate of the region in the source image.
 * @param rw The width of the region.
 * @param rh The height of the region.
 * @return A new image containing the clipped region, or NULL on allocation failure.
*/
bitmap_t bitmap_clipped(bitmap_t src, int rx, int ry, int rw, int rh);

/*!
 * @function bitmap_dominant_color
 * @brief Finds the most frequently occurring color in the image.
 * @discussion Analyzes all pixels in the image and returns the color that appears most often. Useful for generating color palettes or determining the primary color of an image.
 * @param img The image to analyze.
 * @return The dominant color in the image.
*/
color_t bitmap_dominant_color(const bitmap_t img);

/*!
 * @function bitmap_histogram
 * @brief Generates a histogram of color frequencies in the image.
 * @discussion Creates an array representing the frequency distribution of colors in the image. The returned array must be freed by the caller when no longer needed.
 * @param img The image to analyze.
 * @return An array of integers representing color frequencies, or NULL on failure.
*/
int* bitmap_histogram(const bitmap_t img);

/*!
 * @function bitmap_palette
 * @brief Extracts a color palette from the image.
 * @discussion Analyzes the image and extracts the specified number of most representative colors. The returned array contains the palette colors and must be freed by the caller.
 * @param img The image to analyze.
 * @param count The number of colors to extract for the palette.
 * @return An array of colors representing the extracted palette, or NULL on failure.
*/
color_t* bitmap_palette(const bitmap_t img, int count);

/*!
 * @function bitmap_draw_line
 * @brief Draws a line between two points.
 * @discussion Draws a straight line from (x0, y0) to (x1, y1) using the specified color. Uses Bresenham's line algorithm for efficient rasterization.
 * @param img The image to draw on.
 * @param x0 The x-coordinate of the starting point.
 * @param y0 The y-coordinate of the starting point.
 * @param x1 The x-coordinate of the ending point.
 * @param y1 The y-coordinate of the ending point.
 * @param color The color to draw the line with.
 * @return true if successful, false if the image is invalid.
*/
bool bitmap_draw_line(bitmap_t img, int x0, int y0, int x1, int y1, color_t color);

/*!
 * @function bitmap_draw_circle
 * @brief Draws a circle or filled circle.
 * @discussion Draws a circle centered at (xc, yc) with radius r. If fill is non-zero, the circle is filled; otherwise only the outline is drawn.
 * @param img The image to draw on.
 * @param xc The x-coordinate of the circle center.
 * @param yc The y-coordinate of the circle center.
 * @param r The radius of the circle.
 * @param color The color to draw the circle with.
 * @param fill Non-zero to fill the circle, zero for outline only.
 * @return true if successful, false if the image is invalid.
*/
bool bitmap_draw_circle(bitmap_t img, int xc, int yc, int r, color_t color, int fill);

/*!
 * @function bitmap_draw_rectangle
 * @brief Draws a rectangle or filled rectangle.
 * @discussion Draws a rectangle with top-left corner at (x, y) and dimensions w by h. If fill is non-zero, the rectangle is filled; otherwise only the outline is drawn.
 * @param img The image to draw on.
 * @param x The x-coordinate of the top-left corner.
 * @param y The y-coordinate of the top-left corner.
 * @param w The width of the rectangle.
 * @param h The height of the rectangle.
 * @param color The color to draw the rectangle with.
 * @param fill Non-zero to fill the rectangle, zero for outline only.
 * @return true if successful, false if the image is invalid.
*/
bool bitmap_draw_rectangle(bitmap_t img, int x, int y, int w, int h, color_t color, int fill);

/*!
 * @function bitmap_draw_triangle
 * @brief Draws a triangle or filled triangle.
 * @discussion Draws a triangle defined by three vertices (x0,y0), (x1,y1), (x2,y2). If fill is non-zero, the triangle is filled; otherwise only the outline is drawn.
 * @param img The image to draw on.
 * @param x0 The x-coordinate of the first vertex.
 * @param y0 The y-coordinate of the first vertex.
 * @param x1 The x-coordinate of the second vertex.
 * @param y1 The y-coordinate of the second vertex.
 * @param x2 The x-coordinate of the third vertex.
 * @param y2 The y-coordinate of the third vertex.
 * @param color The color to draw the triangle with.
 * @param fill Non-zero to fill the triangle, zero for outline only.
 * @return true if successful, false if the image is invalid.
*/
bool bitmap_draw_triangle(bitmap_t img, int x0, int y0, int x1, int y1, int x2, int y2, color_t color, int fill);

// Data format enumeration for bitmap_load function
/*!
 * @typedef bitmap_format_t
 * @brief Enumeration of supported pixel data formats for image loading.
 * @discussion Defines the various pixel formats that can be used when loading image data from raw pixel arrays. Each format specifies the byte layout and channel count of the pixel data.
 * @field BITMAP_FORMAT_RGBA 4 bytes per pixel: R, G, B, A
 * @field BITMAP_FORMAT_RGB 3 bytes per pixel: R, G, B (alpha = 255)
 * @field BITMAP_FORMAT_BGRA 4 bytes per pixel: B, G, R, A
 * @field BITMAP_FORMAT_BGR 3 bytes per pixel: B, G, R (alpha = 255)
 * @field BITMAP_FORMAT_ARGB 4 bytes per pixel: A, R, G, B
 * @field BITMAP_FORMAT_ABGR 4 bytes per pixel: A, B, G, R
 * @field BITMAP_FORMAT_GRAY 1 byte per pixel: grayscale (alpha = 255)
 * @field BITMAP_FORMAT_GRAY_ALPHA 2 bytes per pixel: grayscale, alpha
 * @field BITMAP_FORMAT_RGB565 2 bytes per pixel: 5-bit R, 6-bit G, 5-bit B (alpha = 255)
 * @field BITMAP_FORMAT_RGB555 2 bytes per pixel: 5-bit R, 5-bit G, 5-bit B (alpha = 255)
 * @field BITMAP_FORMAT_ARGB1555 2 bytes per pixel: 1-bit A, 5-bit R, 5-bit G, 5-bit B
*/
typedef enum {
    BITMAP_FORMAT_RGBA,          // 4 bytes per pixel: R, G, B, A
    BITMAP_FORMAT_RGB,           // 3 bytes per pixel: R, G, B (alpha = 255)
    BITMAP_FORMAT_BGRA,          // 4 bytes per pixel: B, G, R, A
    BITMAP_FORMAT_BGR,           // 3 bytes per pixel: B, G, R (alpha = 255)
    BITMAP_FORMAT_ARGB,          // 4 bytes per pixel: A, R, G, B
    BITMAP_FORMAT_ABGR,          // 4 bytes per pixel: A, B, G, R
    BITMAP_FORMAT_GRAY,          // 1 byte per pixel: grayscale (alpha = 255)
    BITMAP_FORMAT_GRAY_ALPHA,    // 2 bytes per pixel: grayscale, alpha
    BITMAP_FORMAT_RGB565,        // 2 bytes per pixel: 5-bit R, 6-bit G, 5-bit B (alpha = 255)
    BITMAP_FORMAT_RGB555,        // 2 bytes per pixel: 5-bit R, 5-bit G, 5-bit B (alpha = 255)
    BITMAP_FORMAT_ARGB1555       // 2 bytes per pixel: 1-bit A, 5-bit R, 5-bit G, 5-bit B
} bitmap_format_t;

/*!
 * @function bitmap_load
 * @brief Creates an image from raw pixel data in the specified format.
 * @discussion Loads pixel data from a raw byte array and creates a new image. The data must be in the specified format and contain width * height * bytes_per_pixel bytes. The returned image must be freed with bitmap_destroy() when no longer needed.
 * @param data Pointer to the raw pixel data.
 * @param width The width of the image in pixels.
 * @param height The height of the image in pixels.
 * @param format The format of the pixel data (see bitmap_format_t).
 * @return A new image created from the pixel data, or NULL on failure.
*/
bitmap_t bitmap_load(const void* data, int width, int height, bitmap_format_t format);

#ifdef __cplusplus
}
#endif
#endif // PAUL_BITMAP_HEADER

#if defined(PAUL_BITMAP_IMPLEMENTATION) || defined(PAUL_IMPLEMENTATION)
#define _RADIANS(N) (((double)(N)) * (M_PI / 180.))
#define _MIN(A, B) ((A) < (B) ? (A) : (B))
#define _MAX(A, B) ((A) > (B) ? (A) : (B))
#define _CLAMP(x, low, high) _MIN(_MAX(x, low), high)
#define _SWAP(A, B) ((A)^=(B)^=(A)^=(B))

static _CONSTEXPR color_t _black = { 0.0f, 0.0f, 0.0f, 1.0f };

#ifndef PAUL_COLOR_HEADER
static float color_distance(color_t a, color_t b) {
    int dr = a.r - b.r;
    int dg = a.g - b.g;
    int db = a.b - b.b;
    return sqrtf(dr*dr + dg*dg + db*db);
}
#endif

static color_t* bitmap_make(unsigned int w, unsigned int h) {
    static_assert(sizeof(color_t) == sizeof(uint32_t), "color_t must be 4 bytes");
    uint32_t *buffer = (uint32_t*)malloc((w * h + 2) * sizeof(uint32_t));
    if (!buffer)
        return NULL;
    buffer[0] = w;
    buffer[1] = h;
    return (color_t*)(buffer + 2);
}

bitmap_t bitmap_empty(unsigned int w, unsigned int h, color_t color) {
    if (w <= 0 || h <= 0)
        return NULL;
    bitmap_t result = bitmap_make(w, h);
    if (!result)
        return NULL;
    bitmap_fill(result, _black);
    return result;
}

static uint32_t* _raw(bitmap_t img) {
    return img ? (uint32_t*)(img) - 2 : NULL;
}

void bitmap_destroy(bitmap_t img) {
    uint32_t *raw = _raw(img);
    if (raw)
        free(raw);
}

int bitmap_width(const bitmap_t img) {
    uint32_t *raw = _raw(img);
    return raw ? raw[0] : 0;
}

int bitmap_height(const bitmap_t img) {
    uint32_t *raw = _raw(img);
    return raw ? raw[1] : 0;
}

bool bitmap_size(const bitmap_t img, int *w, int *h) {
    if (!img || (!w && !h))
        return false;
    uint32_t *raw = _raw(img);
    int _w = raw ? raw[0] : 0;
    int _h = raw ? raw[1] : 0;
    if (w)
        *w = _w;
    if (h)
        *h = _h;
    return true;
}

bool bitmap_pset(bitmap_t img, int x, int y, color_t color) {
    if (!img || x < 0 || y < 0)
        return false;
    int w, h;
    bitmap_size(img, &w, &h);
    if (x >= w || y >= h || w <= 0 || h <= 0)
        return false;
    img[y * w + x] = color;
    return true;
}

color_t bitmap_pget(const bitmap_t img, int x, int y) {
    if (!img || x < 0 || y < 0)
        return _black;
    int w, h;
    bitmap_size(img, &w, &h);
    if (x >= w || y >= h || w <= 0 || h <= 0)
        return _black;
    return img[y * w + x];
}

bool bitmap_fill(bitmap_t img, color_t color) {
    if (!img)
        return false;
    int w, h;
    bitmap_size(img, &w, &h);
    for (int i = 0; i < w * h; ++i)
        img[i] = color;
    return true;
}

bool color_cmp(color_t a, color_t b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

static inline void _flood(bitmap_t img, int x, int y, color_t _new, color_t _old) {
    if (color_cmp(_new, _old) || !color_cmp(bitmap_pget(img, x, y), _old))
        return;

    int x1 = x;
    int w = bitmap_width(img);
    while (x1 < w && color_cmp(bitmap_pget(img, x1, y), _old)) {
        bitmap_pset(img, x1, y, _new);
        x1++;
    }

    x1 = x - 1;
    while (x1 >= 0 && color_cmp(bitmap_pget(img, x1, y), _old)) {
        bitmap_pset(img, x1, y, _new);
        x1--;
    }

    x1 = x;
    while (x1 < w && color_cmp(bitmap_pget(img, x1, y), _old)) {
        if(y > 0 && color_cmp(bitmap_pget(img, x1, y - 1), _old))
            _flood(img, x1, y - 1, _new, _old);
        x1++;
    }

    x1 = x - 1;
    while(x1 >= 0 && color_cmp(bitmap_pget(img, x1, y), _old)) {
        if(y > 0 && color_cmp(bitmap_pget(img, x1, y - 1), _old))
            _flood(img, x1, y - 1, _new, _old);
        x1--;
    }

    x1 = x;
    int h = bitmap_height(img);
    while(x1 < w && color_cmp(bitmap_pget(img, x1, y), _old)) {
        if(y < h - 1 && color_cmp(bitmap_pget(img, x1, y + 1), _old))
            _flood(img, x1, y + 1, _new, _old);
        x1++;
    }

    x1 = x - 1;
    while(x1 >= 0 && color_cmp(bitmap_pget(img, x1, y), _old)) {
        if(y < h - 1 && color_cmp(bitmap_pget(img, x1, y + 1), _old))
            _flood(img, x1, y + 1, _new, _old);
        x1--;
    }
}

bool bitmap_flood(bitmap_t img, int x, int y, color_t color) {
    if (!img || x < 0 || y < 0)
        return false;
    int w, h;
    bitmap_size(img, &w, &h);
    if (x >= w || y >= h || w <= 0 || h <= 0)
        return false;
    _flood(img, x, y, color, bitmap_pget(img, x, y));
    return true;
}

bool bitmap_paste(bitmap_t dst, const bitmap_t src, int x, int y) {
    if (!src || !dst || x < 0 || y < 0)
        return false;
    int w, h;
    bitmap_size(src, &w, &h);
    int dw, dh;
    bitmap_size(dst, &dw, &dh);
    if (x >= dw || y >= dh || dw <= 0 || dh <= 0)
        return false;
    for (int ox = 0; ox < w; ++ox) {
        for (int oy = 0; oy < h; ++oy) {
            if (oy > h)
                break;
            bitmap_pset(dst, x + ox, y + oy, bitmap_pget(src, ox, oy));
        }
        if (ox > w)
            break;
    }
    return true;
}

bool bitmap_clipped_paste(bitmap_t dst, const bitmap_t src, int x, int y, int rx, int ry, int rw, int rh) {
    if (!src || !dst || x < 0 || y < 0 || rw <= 0 || rh <= 0 || rx < 0 || ry < 0)
        return false;
    int w, h;
    bitmap_size(src, &w, &h);
    if (rx + rw > w || ry + rh > h)
        return false;
    if (x + rw > bitmap_width(dst) || y + rh > bitmap_height(dst))
        return false;
    int dw, dh;
    bitmap_size(dst, &dw, &dh);
    if (x > dw || y > dh)
        return false;
    for (int ox = 0; ox < rw; ++ox)
        for (int oy = 0; oy < rh; ++oy)
            bitmap_pset(dst, ox + x, oy + y, bitmap_pget(src, ox + rx, oy + ry));
    return true;
}

bitmap_t bitmap_dupe(bitmap_t src) {
    if (!src)
        return NULL;
    int w, h;
    bitmap_size(src, &w, &h);
    bitmap_t result = bitmap_make(w, h);
    if (!result)
        return NULL;
    memcpy(result, src, w * h * sizeof(uint32_t));
    return result;
}

bitmap_t bitmap_resized(bitmap_t src, int nw, int nh) {
    if (!src || nw <= 0 || nh <= 0)
        return NULL;
    int w, h;
    bitmap_size(src, &w, &h);
    bitmap_t result = bitmap_make(nw, nh);
    if (!result)
        return false;
    int x_ratio = (int)((w << 16) / nw) + 1;
    int y_ratio = (int)((h << 16) / nh) + 1;
    int x2, y2, i, j;
    for (i = 0; i < nh; ++i) {
        color_t *t = result + i * nw;
        y2 = ((i * y_ratio) >> 16);
        color_t *p = src + y2 * w;
        int rat = 0;
        for (j = 0; j < nw; ++j) {
            x2 = (rat >> 16);
            *t++ = p[x2];
            rat += x_ratio;
        }
    }
    return result;
}

bool bitmap_resize(bitmap_t *src, int nw, int nh) {
    if (!src || !*src || nw < 0 || nh < 0)
        return false;
    int w, h;
    bitmap_size(*src, &w, &h);
    if (w == nw && h == nh)
        return false;
    bitmap_t result = bitmap_resized(*src, nw, nh);
    if (result)
        return false;
    bitmap_destroy(*src);
    *src = result;
    return true;
}

bitmap_t bitmap_rotated(bitmap_t src, float angle) {
    if (!src)
        return NULL;
    int w, h;
    bitmap_size(src, &w, &h);

    float theta = _RADIANS(angle);
    float c = cosf(theta), s = sinf(theta);
    float r[3][2] = {
        { -h * s, h * c },
        {  w * c - h * s, h * c + w * s },
        {  w * c, w * s }
    };

    float mm[2][2] = {{
        _MIN(0, _MIN(r[0][0], _MIN(r[1][0], r[2][0]))),
        _MIN(0, _MIN(r[0][1], _MIN(r[1][1], r[2][1])))
    }, {
        (theta > 1.5708  && theta < 3.14159 ? 0.f : _MAX(r[0][0], _MAX(r[1][0], r[2][0]))),
        (theta > 3.14159 && theta < 4.71239 ? 0.f : _MAX(r[0][1], _MAX(r[1][1], r[2][1])))
    }};

    int dw = (int)ceil(fabsf(mm[1][0]) - mm[0][0]);
    int dh = (int)ceil(fabsf(mm[1][1]) - mm[0][1]);
    bitmap_t result = bitmap_make(dw, dh);
    if (!result)
        return NULL;
    int x, y, sx, sy;
    for (x = 0; x < dw; ++x)
        for (y = 0; y < dh; ++y) {
            sx = ((x + mm[0][0]) * c + (y + mm[0][1]) * s);
            sy = ((y + mm[0][1]) * c - (x + mm[0][0]) * s);
            if (sx < 0 || sx >= w || sy < 0 || sy >= h)
                continue;
            bitmap_pset(result, x, y, bitmap_pget(src, sx, sy));
        }
    return result;
}

bool bitmap_rotate(bitmap_t *src, float angle) {
    if (!src || !*src)
        return false;
    int w, h;
    bitmap_size(*src, &w, &h);
    bitmap_t result = bitmap_rotated(*src, angle);
    if (!result)
        return false;
    bitmap_destroy(*src);
    *src = result;
    return true;
}

bool bitmap_flip(bitmap_t *src, int horizontal, int vertical) {
    if (!src || !*src || (!horizontal && !vertical))
        return false;
    int w, h;
    bitmap_size(*src, &w, &h);
    if (w <= 0 || h <= 0)
        return false;
    bitmap_t result = bitmap_make(w, h);
    if (!result)
        return false;
    int x, y, sx, sy;
    for (x = 0; x < w; ++x)
        for (y = 0; y < h; ++y) {
            sx = horizontal ? (w - 1 - x) : x;
            sy = vertical   ? (h - 1 - y) : y;
            bitmap_pset(result, x, y, bitmap_pget(*src, sx, sy));
        }
    bitmap_destroy(*src);
    *src = result;
    return true;
}

bitmap_t bitmap_flipped(bitmap_t src, int horizontal, int vertical) {
    if (!src || (!horizontal && !vertical))
        return NULL;
    int w, h;
    bitmap_size(src, &w, &h);
    if (w <= 0 || h <= 0)
        return NULL;
    bitmap_t result = bitmap_make(w, h);
    if (!result)
        return NULL;
    int x, y, sx, sy;
    for (x = 0; x < w; ++x)
        for (y = 0; y < h; ++y) {
            sx = horizontal ? (w - 1 - x) : x;
            sy = vertical   ? (h - 1 - y) : y;
            bitmap_pset(result, x, y, bitmap_pget(src, sx, sy));
        }
    return result;
}

bitmap_t bitmap_clipped(bitmap_t src, int rx, int ry, int rw, int rh) {
    if (!src || rw <= 0 || rh <= 0 || rx < 0 || ry < 0)
        return NULL;
    int w, h;
    bitmap_size(src, &w, &h);
    if (rx >= w || ry >= h || rw <= 0 || rh <= 0)
        return NULL;

    int ox = _CLAMP(rx, 0, w);
    int oy = _CLAMP(ry, 0, h);
    if (ox >= w || oy >= h)
        return NULL;
    int mx = _MIN(ox + rw, w);
    int my = _MIN(oy + rh, h);
    int iw = mx - ox;
    int ih = my - oy;
    if (iw <= 0 || ih <= 0)
        return NULL;
    color_t *result = bitmap_make(rw, rh);
    if (!result)
        return NULL;
    for (int px = 0; px < iw; px++)
        for (int py = 0; py < ih; py++) {
            int cx = ox + px;
            int cy = oy + py;
            bitmap_pset(result, px, py, bitmap_pget(src, cx, cy));
        }
    return result;
}

bool bitmap_clip(bitmap_t *src, int rx, int ry, int rw, int rh) {
    if (!src || !*src || rw <= 0 || rh <= 0 || rx < 0 || ry < 0)
        return false;
    int w, h;
    bitmap_size(*src, &w, &h);
    if (rx >= w || ry >= h || rw <= 0 || rh <= 0)
        return false;
    bitmap_t result = bitmap_clipped(*src, rx, ry, rw, rh);
    if (!result)
        return false;
    bitmap_destroy(*src);
    *src = result;
    return true;
}

static inline void vline(bitmap_t img, int w, int h, int x, int y0, int y1, color_t color) {
    if (y1 < y0) {
        y0 += y1;
        y1  = y0 - y1;
        y0 -= y1;
    }

    if (x < 0 || x >= w || y0 >= h)
        return;

    if (y0 < 0)
        y0 = 0;
    if (y1 >= h)
        y1 = h - 1;

    for(int y = y0; y <= y1; y++)
        bitmap_pset(img, x, y, color);
}

static inline void hline(bitmap_t img, int w, int h, int y, int x0, int x1, color_t color) {
    if (x1 < x0) {
        x0 += x1;
        x1  = x0 - x1;
        x0 -= x1;
    }

    if (y < 0 || y >= h || x0 >= w)
        return;

    if (x0 < 0)
        x0 = 0;
    if (x1 >= w)
        x1 = w - 1;

    for(int x = x0; x <= x1; x++)
        bitmap_pset(img, x, y, color);
}

bool bitmap_draw_line(bitmap_t img, int x0, int y0, int x1, int y1, color_t color) {
    if (!img || x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0)
        return false;
    int w, h;
    bitmap_size(img, &w, &h);
    if (x0 >= w || y0 >= h || x1 >= w || y1 >= h || w <= 0 || h <= 0)
        return false;

    if (x0 == x1)
        vline(img, w, h, x0, y0, y1, color);
    else if (y0 == y1)
        hline(img, w, h, y0, x0, x1, color);
    else {
        int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
        int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
        int err = (dx > dy ? dx : -dy) / 2;

        while (bitmap_pset(img, x0, y0, color), x0 != x1 || y0 != y1) {
            int e2 = err;
            if (e2 > -dx) { err -= dy; x0 += sx; }
            if (e2 <  dy) { err += dx; y0 += sy; }
        }
    }

    return true;
}

bool bitmap_draw_circle(bitmap_t img, int xc, int yc, int r, color_t color, int fill) {
    if (!img || xc < 0 || yc < 0 || r <= 0)
        return false;
    int w, h;
    bitmap_size(img, &w, &h);
    if (xc >= w || yc >= h || xc < 0 || yc < 0 || w <= 0 || h <= 0)
        return false;

    int x = -r, y = 0, err = 2 - 2 * r; /* II. Quadrant */
    do {
        bitmap_pset(img, xc - x, yc + y, color);    /*   I. Quadrant */
        bitmap_pset(img, xc - y, yc - x, color);    /*  II. Quadrant */
        bitmap_pset(img, xc + x, yc - y, color);    /* III. Quadrant */
        bitmap_pset(img, xc + y, yc + x, color);    /*  IV. Quadrant */

        if (fill) {
            hline(img, w, h, yc - y, xc - x, xc + x, color);
            hline(img, w, h, yc + y, xc - x, xc + x, color);
        }

        r = err;
        if (r <= y)
            err += ++y * 2 + 1; /* e_xy+e_y < 0 */
        if (r > x || err > y)
            err += ++x * 2 + 1; /* e_xy+e_x > 0 or no 2nd y-step */
    } while (x < 0);

    return true;
}

bool bitmap_draw_rectangle(bitmap_t img, int x, int y, int w, int h, color_t color, int fill) {
    if (!img || w <= 0 || h <= 0)
        return false;
    int img_w, img_h;
    bitmap_size(img, &img_w, &img_h);
    if (x >= img_w || y >= img_h || x < 0 || y < 0 || img_w <= 0 || img_h <= 0)
        return false;

    if (x < 0) {
        w += x;
        x  = 0;
    }
    if (y < 0) {
        h += y;
        y  = 0;
    }

    w += x;
    h += y;
    if (w < 0 || h < 0 || x > img_w || y > img_h)
        return false;

    if (w > img_w)
        w = img_w;
    if (h > img_h)
        h = img_h;

    if (fill) {
        for (; y < h; ++y)
            hline(img, img_w, img_h, y, x, w, color);
    } else {
        hline(img, img_w, img_h, y, x, w, color);
        hline(img, img_w, img_h, h, x, w, color);
        vline(img, img_w, img_h, x, y, h, color);
        vline(img, img_w, img_h, w, y, h, color);
    }

    return true;
}

bool bitmap_draw_triangle(bitmap_t img, int x0, int y0, int x1, int y1, int x2, int y2, color_t color, int fill) {
    if (!img || x0 < 0 || y0 < 0 || x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0)
        return false;
    int w, h;
    bitmap_size(img, &w, &h);
    if (x0 >= w || y0 >= h || x1 >= w || y1 >= h || x2 >= w || y2 >= h || w <= 0 || h <= 0)
        return false;

    if (y0 ==  y1 && y0 ==  y2)
        return false;
    if (fill) {
        if (y0 > y1) {
            _SWAP(x0, x1);
            _SWAP(y0, y1);
        }
        if (y0 > y2) {
            _SWAP(x0, x2);
            _SWAP(y0, y2);
        }
        if (y1 > y2) {
            _SWAP(x1, x2);
            _SWAP(y1, y2);
        }

        int total_height = y2 - y0, i, j;
        for (i = 0; i < total_height; ++i) {
            int second_half = i > y1 - y0 || y1 == y0;
            int segment_height = second_half ? y2 - y1 : y1 - y0;
            float alpha = (float)i / total_height;
            float beta  = (float)(i - (second_half ? y1 - y0 : 0)) / segment_height;
            int ax = x0 + (x2 - x0) * alpha;
            int ay = y0 + (y2 - y0) * alpha;
            int bx = second_half ? x1 + (x2 - x1) : x0 + (x1 - x0) * beta;
            int by = second_half ? y1 + (y2 - y1) : y0 + (y1 - y0) * beta;
            if (ax > bx) {
                _SWAP(ax, bx);
                _SWAP(ay, by);
            }
            for (j = ax; j <= bx; ++j)
                bitmap_pset(img, j, y0 + i, color);
        }
    } else {
        bitmap_draw_line(img, x0, y0, x1, y1, color);
        bitmap_draw_line(img, x1, y1, x2, y2, color);
        bitmap_draw_line(img, x2, y2, x0, y0, color);
    }

    return true;
}

color_t bitmap_dominant_color(const bitmap_t img) {
    if (!img)
        return _black;
    
    int w, h;
    bitmap_size(img, &w, &h);
    int count = w * h;
    if (count <= 0)
        return _black;
    
    int max_count = 0;
    int dominant_index = -1;
    // Simple O(n²) approach - for better performance with large arrays,
    // consider using a hash table or sorting approach
    for (int i = 0; i < count; i++) {
        int current_count = 0;
        // Count occurrences of img[i]
        for (int j = 0; j < count; j++)
            if (img[i].rgba == img[j].rgba)
                current_count++;
        if (current_count > max_count) {
            max_count = current_count;
            dominant_index = i;
        }
    }
    return dominant_index < 0 ? _black : img[dominant_index];
}

int* bitmap_histogram(const bitmap_t img) {
    if (!img)
        return NULL;
    
    int w, h;
    bitmap_size(img, &w, &h);
    int count = w * h;
    if (count <= 0)
        return NULL;
    
    // Create a simple histogram array for each possible RGB value
    // This is a simplified version - a real histogram might be more complex
    int* histogram = (int*)calloc(256 * 3, sizeof(int)); // R, G, B histograms
    if (!histogram)
        return NULL;
    
    for (int i = 0; i < count; i++) {
        histogram[img[i].r]++;                    // Red histogram
        histogram[256 + img[i].g]++;              // Green histogram  
        histogram[512 + img[i].b]++;              // Blue histogram
    }
    
    return histogram;
}

color_t* bitmap_palette(const bitmap_t img, int count) {
    if (!img || count <= 0)
        return NULL;

    int w, h;
    bitmap_size(img, &w, &h);
    size_t img_size = w * h;
    if (img_size <= 0)
        return NULL;
    
    color_t *palette = (color_t*)malloc(count * sizeof(color_t));
    if (!palette)
        return NULL;
    
    if (count > img_size) {
        for (int i = 0; i < count; i++)
            palette[i] = i >= img_size ? _black : img[i];
        return palette;
    } else {
        for (int i = 0; i < count; i++)
            palette[i] = img[i * img_size / count];
    }

    // K-means iterations
    for (int iter = 0; iter < 10; iter++) {
        // Arrays to accumulate color values for each cluster
        int cluster_r[count];
        int cluster_g[count];
        int cluster_b[count];
        int cluster_a[count];
        int cluster_count[count];
        for (int i = 0; i < count; i++)
            cluster_r[i] = cluster_g[i] = cluster_b[i] = cluster_a[i] = cluster_count[i] = 0;

        // Assign each pixel to nearest palette color
        for (int p = 0; p < img_size; p++) {
            int closest_idx = 0;
            float min_distance = color_distance(img[p], palette[0]);

            for (int i = 1; i < count; i++) {
                float distance = color_distance(img[p], palette[i]);
                if (distance < min_distance) {
                    min_distance = distance;
                    closest_idx = i;
                }
            }

            // Add pixel to cluster
            cluster_r[closest_idx] += img[p].r;
            cluster_g[closest_idx] += img[p].g;
            cluster_b[closest_idx] += img[p].b;
            cluster_a[closest_idx] += img[p].a;
            cluster_count[closest_idx]++;
        }

        // Update palette colors to cluster centroids
        for (int i = 0; i < count; i++) {
            if (cluster_count[i] > 0) {
                palette[i].r = cluster_r[i] / cluster_count[i];
                palette[i].g = cluster_g[i] / cluster_count[i];
                palette[i].b = cluster_b[i] / cluster_count[i];
                palette[i].a = cluster_a[i] / cluster_count[i];
            }
        }
    }

    // Sort palette by brightness (optional, for consistent ordering)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            int brightness_i = palette[i].r + palette[i].g + palette[i].b;
            int brightness_j = palette[j].r + palette[j].g + palette[j].b;

            if (brightness_i > brightness_j) {
                color_t temp = palette[i];
                palette[i] = palette[j];
                palette[j] = temp;
            }
        }
    }

    return palette;
}

// Load image from raw pixel data with specified format
bitmap_t bitmap_load(const void* data, int width, int height, bitmap_format_t format) {
    if (!data || width <= 0 || height <= 0)
        return NULL;
    
    bitmap_t img = bitmap_make(width, height);
    if (!img)
        return NULL;
    
    const uint8_t* src = (const uint8_t*)data;
    
    for (int y = 0; y < height; y++) 
        for (int x = 0; x < width; x++) {
            color_t pixel = {0, 0, 0, 255}; // Default: black with full alpha
            switch (format) {
                case BITMAP_FORMAT_RGBA:
                    pixel.r = *src++;
                    pixel.g = *src++;
                    pixel.b = *src++;
                    pixel.a = *src++;
                    break;
                case BITMAP_FORMAT_RGB:
                    pixel.r = *src++;
                    pixel.g = *src++;
                    pixel.b = *src++;
                    pixel.a = 255;
                    break;
                case BITMAP_FORMAT_BGRA:
                    pixel.b = *src++;
                    pixel.g = *src++;
                    pixel.r = *src++;
                    pixel.a = *src++;
                    break;
                case BITMAP_FORMAT_BGR:
                    pixel.b = *src++;
                    pixel.g = *src++;
                    pixel.r = *src++;
                    pixel.a = 255;
                    break;
                case BITMAP_FORMAT_ARGB:
                    pixel.a = *src++;
                    pixel.r = *src++;
                    pixel.g = *src++;
                    pixel.b = *src++;
                    break;
                case BITMAP_FORMAT_ABGR:
                    pixel.a = *src++;
                    pixel.b = *src++;
                    pixel.g = *src++;
                    pixel.r = *src++;
                    break;
                case BITMAP_FORMAT_GRAY: {
                    uint8_t gray = *src++;
                    pixel.r = gray;
                    pixel.g = gray;
                    pixel.b = gray;
                    pixel.a = 255;
                    break;
                }
                case BITMAP_FORMAT_GRAY_ALPHA: {
                    uint8_t gray = *src++;
                    pixel.r = gray;
                    pixel.g = gray;
                    pixel.b = gray;
                    pixel.a = *src++;
                    break;
                }
                case BITMAP_FORMAT_RGB565: {
                    uint16_t rgb565 = *(const uint16_t*)src;
                    src += 2;
                    
                    // Extract 5-6-5 components
                    uint8_t r5 = (rgb565 >> 11) & 0x1F;
                    uint8_t g6 = (rgb565 >> 5) & 0x3F;
                    uint8_t b5 = rgb565 & 0x1F;
                    
                    // Scale to 8-bit
                    pixel.r = (r5 << 3) | (r5 >> 2);
                    pixel.g = (g6 << 2) | (g6 >> 4);
                    pixel.b = (b5 << 3) | (b5 >> 2);
                    pixel.a = 255;
                    break;
                }
                case BITMAP_FORMAT_RGB555: {
                    uint16_t rgb555 = *(const uint16_t*)src;
                    src += 2;
                    
                    // Extract 5-5-5 components
                    uint8_t r5 = (rgb555 >> 10) & 0x1F;
                    uint8_t g5 = (rgb555 >> 5) & 0x1F;
                    uint8_t b5 = rgb555 & 0x1F;
                    
                    // Scale to 8-bit
                    pixel.r = (r5 << 3) | (r5 >> 2);
                    pixel.g = (g5 << 3) | (g5 >> 2);
                    pixel.b = (b5 << 3) | (b5 >> 2);
                    pixel.a = 255;
                    break;
                }
                case BITMAP_FORMAT_ARGB1555: {
                    uint16_t argb1555 = *(const uint16_t*)src;
                    src += 2;
                    
                    // Extract 1-5-5-5 components
                    uint8_t a1 = (argb1555 >> 15) & 0x1;
                    uint8_t r5 = (argb1555 >> 10) & 0x1F;
                    uint8_t g5 = (argb1555 >> 5) & 0x1F;
                    uint8_t b5 = argb1555 & 0x1F;
                    
                    // Scale to 8-bit
                    pixel.r = (r5 << 3) | (r5 >> 2);
                    pixel.g = (g5 << 3) | (g5 >> 2);
                    pixel.b = (b5 << 3) | (b5 >> 2);
                    pixel.a = a1 ? 255 : 0;
                    break;
                }
                default:
                    // Unknown format, fill with black
                    pixel.r = pixel.g = pixel.b = 0;
                    pixel.a = 255;
                    break;
            }
            bitmap_pset(img, x, y, pixel);
        }
    
    return img;
}
#endif
