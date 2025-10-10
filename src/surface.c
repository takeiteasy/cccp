#include "cccp.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define QOI_IMPLEMENTATION
#include "qoi.h"
#define PAUL_RANDOM_IMPLEMENTATION
#include "paul_random.h"

CCCP_Surface CCCP_NewSurface(unsigned int w, unsigned int h, color_t clearColor) {
    return bitmap_empty(w, h, clearColor);
}

CCCP_Surface CCCP_SurfaceFromMemory(const void* data, int width, int height, bitmap_format_t format) {
    return bitmap_load(data, width, height, format);   
}

CCCP_Surface CCCP_SurfaceFromFile(const char* filename) {
    unsigned char magic[4] = { 'q', 'o', 'i', 'f' };
    unsigned char *data = NULL;
    int width,  height;
    bool is_qoi = false;
    if (memcmp(filename, magic, 4) == 0) {
        qoi_desc desc;
        if (!(data = qoi_read(filename, &desc, 4)))
            return NULL;
        width = desc.width;
        height = desc.height;
        is_qoi = true;
    } else {
        int c;
        if (!(data = stbi_load(filename, &width, &height, &c, 4)))
            return NULL;
    }

    CCCP_Surface bmp = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 0.0f});
    if (!bmp)
        return NULL;
    for (int y = 0; y < height; y++)
        for (int x = 0; x < width; x++) {
            int i = (y * width + x) * 4;
            CCCP_SetPixel(bmp, x, y, (color_t){ data[i], data[i + 1], data[i + 2], data[i + 3] });
        }
    if (data)
        free(data);
    return bmp;
}

CCCP_Surface CCCP_CopySurface(CCCP_Surface surface) {
    return bitmap_dupe(surface);
}

void CCCP_DestroySurface(CCCP_Surface surface) {
    bitmap_destroy(surface);
}

int CCCP_SurfaceWidth(CCCP_Surface surface) {
    return bitmap_width(surface);
}

int CCCP_SurfaceHeight(CCCP_Surface surface) {
    return bitmap_height(surface);
}

void CCCP_ClearSurface(CCCP_Surface surface, color_t clearColor) {
    bitmap_fill(surface, clearColor);
}

bool CCCP_SetPixel(CCCP_Surface surface, int x, int y, color_t color) {
    return bitmap_pset(surface, x, y, color);
}

color_t CCCP_GetPixel(CCCP_Surface surface, int x, int y) {
    return bitmap_pget(surface, x, y);
}

void CCCP_BlitSurface(CCCP_Surface dest, CCCP_Surface src, int x, int y) {
    bitmap_paste(dest, src, x, y);
}

void CCCP_BlitSurfaceRect(CCCP_Surface dest, CCCP_Surface src, int srcX, int srcY, int srcW, int srcH, int destX, int destY) {
    bitmap_clipped_paste(dest, src, destX, destY, srcX, srcY, srcW, srcH);
}

void CCCP_DrawLine(CCCP_Surface surface, int x1, int y1, int x2, int y2, color_t color) {
    bitmap_draw_line(surface, x1, y1, x2, y2, color);
}

void CCCP_DrawRect(CCCP_Surface surface, int x, int y, int w, int h, color_t color, bool filled) {
    bitmap_draw_rectangle(surface, x, y, w, h, color, filled);
}

void CCCP_DrawCircle(CCCP_Surface surface, int x, int y, int radius, color_t color, bool filled) {
    bitmap_draw_circle(surface, x, y, radius, color, filled);
}

void CCCP_DrawTriangle(CCCP_Surface surface, int x1, int y1, int x2, int y2, int x3, int y3, color_t color, bool filled) {
    bitmap_draw_triangle(surface, x1, y1, x2, y2, x3, y3, color, filled);
}

CCCP_Surface CCCP_ResizeSurface(CCCP_Surface surface, unsigned int w, unsigned int h) {
    return bitmap_resized(surface, w, h);
}
CCCP_Surface CCCP_RotateSurface(CCCP_Surface surface, float angle) {
    return bitmap_rotated(surface, angle);
}

CCCP_Surface CCCP_FlipSurface(CCCP_Surface surface, bool horizontal, bool vertical) {
    return bitmap_flipped(surface, horizontal, vertical);
}

CCCP_Surface CCCP_ClipSurface(CCCP_Surface surface, int x, int y, int w, int h) {
    return bitmap_clipped(surface, x, y, w, h);
}

CCCP_Surface CCCP_SurfaceFromPerlinNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float nx = (float)x / scale + offsetX;
            float ny = (float)y / scale + offsetY;
            float noise = perlin_noise(nx, ny, 0.0f);
            // Convert from [-1, 1] to [0, 255]
            uint8_t gray = (uint8_t)((noise + 1.0f) * 0.5f * 255.0f);
            color_t color = {gray / 255.0f, gray / 255.0f, gray / 255.0f, 1.0f};
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromSimplexNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float nx = (float)x / scale + offsetX;
            float ny = (float)y / scale + offsetY;
            float noise = simplex_noise(nx, ny, 0.0f);
            // Convert from [-1, 1] to [0, 255]
            uint8_t gray = (uint8_t)((noise + 1.0f) * 0.5f * 255.0f);
            color_t color = {gray / 255.0f, gray / 255.0f, gray / 255.0f, 1.0f};
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromWorleyNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float nx = (float)x / scale + offsetX;
            float ny = (float)y / scale + offsetY;
            float noise = worley_noise(nx, ny, 0.0f);
            // Worley noise is typically in [0, 1], convert to [0, 255]
            uint8_t gray = (uint8_t)(noise * 255.0f);
            color_t color = {gray / 255.0f, gray / 255.0f, gray / 255.0f, 1.0f};
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromValueNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float nx = (float)x / scale + offsetX;
            float ny = (float)y / scale + offsetY;
            float noise = value_noise(nx, ny, 0.0f);
            // Convert from [-1, 1] to [0, 255]
            uint8_t gray = (uint8_t)((noise + 1.0f) * 0.5f * 255.0f);
            color_t color = {gray / 255.0f, gray / 255.0f, gray / 255.0f, 1.0f};
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromWhiteNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float nx = (float)x / scale + offsetX;
            float ny = (float)y / scale + offsetY;
            float noise = white_noise(nx, ny, 0.0f);
            // Convert from [-1, 1] to [0, 255]
            uint8_t gray = (uint8_t)((noise + 1.0f) * 0.5f * 255.0f);
            color_t color = {gray / 255.0f, gray / 255.0f, gray / 255.0f, 1.0f};
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromFBMNoise(unsigned int width, unsigned int height, float scale, float offsetX, float offsetY, float lacunarity, float gain, int octaves) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++) 
        for (unsigned int x = 0; x < width; x++) {
            float nx = (float)x / scale + offsetX;
            float ny = (float)y / scale + offsetY;
            float noise = fbm(nx, ny, 0.0f, lacunarity, gain, octaves, perlin_noise);
            // Convert from [-1, 1] to [0, 255]
            uint8_t gray = (uint8_t)((noise + 1.0f) * 0.5f * 255.0f);
            color_t color = {gray / 255.0f, gray / 255.0f, gray / 255.0f, 1.0f};
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromHorizontalGradient(unsigned int width, unsigned int height, color_t startColor, color_t endColor) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float t = (float)x / (float)(width - 1);
            color_t color = {
                startColor.r + t * (endColor.r - startColor.r),
                startColor.g + t * (endColor.g - startColor.g),
                startColor.b + t * (endColor.b - startColor.b),
                startColor.a + t * (endColor.a - startColor.a)
            };
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromVerticalGradient(unsigned int width, unsigned int height, color_t startColor, color_t endColor) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float t = (float)y / (float)(height - 1);
            color_t color = {
                startColor.r + t * (endColor.r - startColor.r),
                startColor.g + t * (endColor.g - startColor.g),
                startColor.b + t * (endColor.b - startColor.b),
                startColor.a + t * (endColor.a - startColor.a)
            };
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromRadialGradient(unsigned int width, unsigned int height, color_t centerColor, color_t edgeColor) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    float centerX = (float)width / 2.0f;
    float centerY = (float)height / 2.0f;
    float maxDist = sqrtf(centerX * centerX + centerY * centerY);
    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float dx = (float)x - centerX;
            float dy = (float)y - centerY;
            float dist = sqrtf(dx * dx + dy * dy);
            float t = dist / maxDist;
            t = fminf(t, 1.0f); // Clamp to 1.0
            color_t color = {
                centerColor.r + t * (edgeColor.r - centerColor.r),
                centerColor.g + t * (edgeColor.g - centerColor.g),
                centerColor.b + t * (edgeColor.b - centerColor.b),
                centerColor.a + t * (edgeColor.a - centerColor.a)
            };
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromDiagonalGradient(unsigned int width, unsigned int height, color_t startColor, color_t endColor) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float t = ((float)x / (float)(width - 1) + (float)y / (float)(height - 1)) / 2.0f;
            color_t color = {
                startColor.r + t * (endColor.r - startColor.r),
                startColor.g + t * (endColor.g - startColor.g),
                startColor.b + t * (endColor.b - startColor.b),
                startColor.a + t * (endColor.a - startColor.a)
            };
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromCheckerboard(unsigned int width, unsigned int height, color_t color1, color_t color2, unsigned int squareSize) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            unsigned int gridX = x / squareSize;
            unsigned int gridY = y / squareSize;
            color_t color = ((gridX + gridY) % 2 == 0) ? color1 : color2;
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromHorizontalStripes(unsigned int width, unsigned int height, color_t color1, color_t color2, unsigned int stripeWidth) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            unsigned int stripeIndex = y / stripeWidth;
            color_t color = (stripeIndex % 2 == 0) ? color1 : color2;
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromVerticalStripes(unsigned int width, unsigned int height, color_t color1, color_t color2, unsigned int stripeWidth) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            unsigned int stripeIndex = x / stripeWidth;
            color_t color = (stripeIndex % 2 == 0) ? color1 : color2;
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}

CCCP_Surface CCCP_SurfaceFromConcentricCircles(unsigned int width, unsigned int height, color_t centerColor, color_t edgeColor, unsigned int numRings) {
    CCCP_Surface surface = CCCP_NewSurface(width, height, (color_t){0.0f, 0.0f, 0.0f, 1.0f});
    if (!surface)
        return NULL;

    float centerX = (float)width / 2.0f;
    float centerY = (float)height / 2.0f;
    float maxDist = sqrtf(centerX * centerX + centerY * centerY);
    for (unsigned int y = 0; y < height; y++)
        for (unsigned int x = 0; x < width; x++) {
            float dx = (float)x - centerX;
            float dy = (float)y - centerY;
            float dist = sqrtf(dx * dx + dy * dy);
            float ringIndex = (dist / maxDist) * (float)numRings;
            color_t color = (fmodf(ringIndex, 2.0f) < 1.0f) ? centerColor : edgeColor;
            CCCP_SetPixel(surface, x, y, color);
        }
    return surface;
}
