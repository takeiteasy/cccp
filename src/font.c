#include "cccp.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "../deps/stb_truetype.h"
#include "font8x8.h"

static void render_char(CCCP_Surface surface, int x, int y, const char bitmap[8], color_t color) {
    for (int px = 0; px < 8; px++)
        for (int py = 0; py < 8; py++)
            if (bitmap[px] & (1 << py))
                CCCP_SetPixel(surface, x + px, y + py, color);
}

void CCCP_DebugPrintASCII(CCCP_Surface surface, int x, int y, const char* text, color_t color) {
    int pixel_x = x * 8;
    int pixel_y = y * 8;
    while (*text) {
        unsigned char c = (unsigned char)*text;
        render_char(surface, pixel_x, pixel_y, font8x8_basic[c], color);
        pixel_x += 8;
        text++;
    }
}

void CCCP_DebugPrintUnicode(CCCP_Surface surface, int x, int y, const wchar_t* text, color_t color) {
    int start_pixel_x = x * 8;
    int current_pixel_x = start_pixel_x;
    int pixel_y = y * 8;
    while (*text) {
        if (*text == L'\n') {
            current_pixel_x = start_pixel_x;
            pixel_y += 8;
        } else if (*text == L'\t')
            current_pixel_x += 32; // 4 spaces
        else if (*text == L'\r')
            current_pixel_x = start_pixel_x;
        else {
            unsigned int code = (unsigned int)*text;
            const char* bitmap = NULL;
            if (code >= 0x0000 && code <= 0x007F)
                bitmap = font8x8_basic[code];
            else if (code >= 0x0080 && code <= 0x009F)
                bitmap = font8x8_control[code - 0x0080];
            else if (code >= 0x00A0 && code <= 0x00FF)
                bitmap = font8x8_ext_latin[code - 0x00A0];
            else if (code >= 0x0390 && code <= 0x03C9)
                bitmap = font8x8_greek[code - 0x0390];
            else if (code >= 0x2500 && code <= 0x257F)
                bitmap = font8x8_box[code - 0x2500];
            else if (code >= 0x2580 && code <= 0x259F)
                bitmap = font8x8_block[code - 0x2580];
            else if (code >= 0x3040 && code <= 0x309F)
                bitmap = font8x8_hiragana[code - 0x3040];
            else
                bitmap = font8x8_basic[32];
            render_char(surface, current_pixel_x, pixel_y, bitmap, color);
            current_pixel_x += 8;
        }
        text++;
    }
}

struct CCCP_Font {
    unsigned char* data;
    stbtt_fontinfo info;
    CCCP_HashTable* cache; // key: "size_glyphindex" value: bitmap_t*
};

CCCP_Font* CCCP_LoadFont(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file)
        return NULL;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* data = malloc(size);
    if (!data) {
        fclose(file);
        return NULL;
    }

    fread(data, 1, size, file);
    fclose(file);

    CCCP_Font* font = malloc(sizeof(CCCP_Font));
    if (!font) {
        free(data);
        return NULL;
    }

    font->data = data;
    font->cache = CCCP_NewHashTable(256);
    if (!font->cache) {
        free(data);
        free(font);
        return NULL;
    }
    font->cache->free_callback = (void(*)(void*))bitmap_destroy;

    if (stbtt_InitFont(&font->info, data, 0) == 0) {
        CCCP_DestroyHashTable(font->cache);
        free(data);
        free(font);
        return NULL;
    }

    return font;
}

void CCCP_DestroyFont(CCCP_Font* font) {
    if (!font)
        return;
    free(font->data);
    CCCP_DestroyHashTable(font->cache);
    free(font);
}

static bitmap_t get_cached_glyph(CCCP_Font* font, float size, int glyph_index) {
    char key[64];
    sprintf(key, "%.2f_%d", size, glyph_index);
    return (bitmap_t)CCCP_HashTableGet(font->cache, key);
}

static void cache_glyph(CCCP_Font* font, float size, int glyph_index, bitmap_t bitmap) {
    char key[64];
    sprintf(key, "%.2f_%d", size, glyph_index);
    CCCP_HashTableInsert(font->cache, strdup(key), bitmap);
}

void CCCP_DrawText(CCCP_Surface surface, CCCP_Font* font, int x, int y, const char* text, color_t color, float size) {
    if (!font || !text)
        return;

    float scale = stbtt_ScaleForPixelHeight(&font->info, size);
    int ascent, descent, line_gap;
    stbtt_GetFontVMetrics(&font->info, &ascent, &descent, &line_gap);
    int baseline = y + (int)(ascent * scale);
    int current_x = x;
    for (const char* c = text; *c; ++c) {
        int codepoint = (unsigned char)*c;
        int glyph_index = stbtt_FindGlyphIndex(&font->info, codepoint);

        bitmap_t glyph_bitmap = get_cached_glyph(font, size, glyph_index);
        if (!glyph_bitmap) {
            // Rasterize
            int width, height, xoff, yoff;
            unsigned char* bitmap = stbtt_GetCodepointBitmap(&font->info, 0, scale, codepoint, &width, &height, &xoff, &yoff);
            if (bitmap && width > 0 && height > 0) {
                // Create RGBA data
                unsigned char* rgba_data = malloc(width * height * 4);
                if (rgba_data) {
                    for (int i = 0; i < width * height; ++i) {
                        unsigned char alpha = bitmap[i];
                        rgba_data[i * 4 + 0] = color.r;
                        rgba_data[i * 4 + 1] = color.g;
                        rgba_data[i * 4 + 2] = color.b;
                        rgba_data[i * 4 + 3] = alpha;
                    }
                    glyph_bitmap = bitmap_load(rgba_data, width, height, BITMAP_FORMAT_RGBA);
                    free(rgba_data);
                    if (glyph_bitmap)
                        cache_glyph(font, size, glyph_index, glyph_bitmap);
                }
                stbtt_FreeBitmap(bitmap, NULL);
            }
        }

        if (glyph_bitmap) {
            int xoff, yoff;
            stbtt_GetCodepointBitmapBox(&font->info, codepoint, 0, scale, &xoff, &yoff, NULL, NULL);
            CCCP_BlitSurface(surface, glyph_bitmap, current_x + xoff, baseline + yoff);
        }

        // Advance
        int advance, lsb;
        stbtt_GetCodepointHMetrics(&font->info, codepoint, &advance, &lsb);
        current_x += (int)(advance * scale);
    }
}