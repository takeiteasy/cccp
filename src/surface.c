#include "cccp.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define QOI_IMPLEMENTATION
#include "qoi.h"

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
