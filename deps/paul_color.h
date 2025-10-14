
/* paul/paul_color.h -- https://github.com/takeiteasy/paul

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
 @header paul_color.h
 @copyright George Watson GPLv3
 @updated 2025-09-29
 @brief Color manipulation library for C/C++.
 @discussion
    Implementation is included when PAUL_COLOR_IMPLEMENTATION or PAUL_IMPLEMENTATION is defined.
*/

#ifndef PAUL_COLOR_HEADER
#define PAUL_COLOR_HEADER
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

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

#ifdef __cplusplus
#define _CONSTEXPR constexpr
#else
#if __STDC_VERSION__ >= 202311L
#define _CONSTEXPR constexpr
#else
#define _CONSTEXPR const
#endif
#endif

/*! @constsection Color Constants
    @brief Predefined color constants for common web colors.
    @discussion When NO_COLOR_CONSTANTS is not defined, this header provides a comprehensive set of predefined color constants. Each color is defined in multiple formats:
    - COLOR_NAME: RGBA byte values {r, g, b, a}
    - COLOR_NAME_FLT: Floating-point RGBA values {r, g, b, a}
    - COLOR_NAME_INT: Packed 32-bit RGBA integer
    - color_name: _CONSTEXPR color_t struct instance
    
    All colors use standard web color values with alpha=255 (fully opaque) unless otherwise noted.
*/
#ifndef NO_COLOR_CONSTANTS
#define COLOR_ALICE_BLUE { 240, 248, 255, 255 }
#define COLOR_ALICE_BLUE_FLT { 0.941176471f, 0.97254902f, 1.f, 1.f }
#define COLOR_ALICE_BLUE_INT 0xF0F8FFFF
static _CONSTEXPR color_t color_alice_blue = COLOR_ALICE_BLUE;
#define COLOR_ANTIQUE_WHITE { 250, 235, 215, 255 }
#define COLOR_ANTIQUE_WHITE_FLT { 0.980392157f, 0.921568627f, 0.843137255f, 1.f }
#define COLOR_ANTIQUE_WHITE_INT 0xFAEBD7FF
static _CONSTEXPR color_t color_antique_white = COLOR_ANTIQUE_WHITE;
#define COLOR_AQUA { 0, 255, 255, 255 }
#define COLOR_AQUA_FLT { 0.f, 1.f, 1.f, 1.f }
#define COLOR_AQUA_INT 0x00FFFFFF
static _CONSTEXPR color_t color_aqua = COLOR_AQUA;
#define COLOR_AQUAMARINE { 127, 255, 212, 255 }
#define COLOR_AQUAMARINE_FLT { 0.498039216f, 1.f, 0.831372549f, 1.f }
#define COLOR_AQUAMARINE_INT 0x7FFFD4FF
static _CONSTEXPR color_t color_aquamarine = COLOR_AQUAMARINE;
#define COLOR_AZURE { 240, 255, 255, 255 }
#define COLOR_AZURE_FLT { 0.941176471f, 1.f, 1.f, 1.f }
#define COLOR_AZURE_INT 0xF0FFFFFF
static _CONSTEXPR color_t color_azure = COLOR_AZURE;
#define COLOR_BEIGE { 245, 245, 220, 255 }
#define COLOR_BEIGE_FLT { 0.960784314f, 0.960784314f, 0.862745098f, 1.f }
#define COLOR_BEIGE_INT 0xF5F5DCFF
static _CONSTEXPR color_t color_beige = COLOR_BEIGE;
#define COLOR_BISQUE { 255, 228, 196, 255 }
#define COLOR_BISQUE_FLT { 1.f, 0.894117647f, 0.768627451f, 1.f }
#define COLOR_BISQUE_INT 0xFFE4C4FF
static _CONSTEXPR color_t color_bisque = COLOR_BISQUE;
#define COLOR_BLACK { 0, 0, 0, 255 }
#define COLOR_BLACK_FLT { 0.f, 0.f, 0.f, 1.f }
#define COLOR_BLACK_INT 0x000000FF
static _CONSTEXPR color_t color_black = COLOR_BLACK;
#define COLOR_BLANCHED_ALMOND { 255, 235, 205, 255 }
#define COLOR_BLANCHED_ALMOND_FLT { 1.f, 0.921568627f, 0.803921569f, 1.f }
#define COLOR_BLANCHED_ALMOND_INT 0xFFEBCDFF
static _CONSTEXPR color_t color_blanched_almond = COLOR_BLANCHED_ALMOND;
#define COLOR_BLUE { 0, 0, 255, 255 }
#define COLOR_BLUE_FLT { 0.f, 0.f, 1.f, 1.f }
#define COLOR_BLUE_INT 0x0000FFFF
static _CONSTEXPR color_t color_blue = COLOR_BLUE;
#define COLOR_BLUE_VIOLET { 138, 43, 226, 255 }
#define COLOR_BLUE_VIOLET_FLT { 0.541176471f, 0.168627451f, 0.88627451f, 1.f }
#define COLOR_BLUE_VIOLET_INT 0x8A2BE2FF
static _CONSTEXPR color_t color_blue_violet = COLOR_BLUE_VIOLET;
#define COLOR_BROWN { 165, 42, 42, 255 }
#define COLOR_BROWN_FLT { 0.647058824f, 0.164705882f, 0.164705882f, 1.f }
#define COLOR_BROWN_INT 0xA52A2AFF
static _CONSTEXPR color_t color_brown = COLOR_BROWN;
#define COLOR_BURLYWOOD { 222, 184, 135, 255 }
#define COLOR_BURLYWOOD_FLT { 0.870588235f, 0.721568627f, 0.529411765f, 1.f }
#define COLOR_BURLYWOOD_INT 0xDEB887FF
static _CONSTEXPR color_t color_burlywood = COLOR_BURLYWOOD;
#define COLOR_CADET_BLUE { 95, 158, 160, 255 }
#define COLOR_CADET_BLUE_FLT { 0.37254902f, 0.619607843f, 0.62745098f, 1.f }
#define COLOR_CADET_BLUE_INT 0x5F9EA0FF
static _CONSTEXPR color_t color_cadet_blue = COLOR_CADET_BLUE;
#define COLOR_CHARTREUSE { 127, 255, 0, 255 }
#define COLOR_CHARTREUSE_FLT { 0.498039216f, 1.f, 0.f, 1.f }
#define COLOR_CHARTREUSE_INT 0x7FFF00FF
static _CONSTEXPR color_t color_chartreuse = COLOR_CHARTREUSE;
#define COLOR_CHOCOLATE { 210, 105, 30, 255 }
#define COLOR_CHOCOLATE_FLT { 0.823529412f, 0.411764706f, 0.117647059f, 1.f }
#define COLOR_CHOCOLATE_INT 0xD2691EFF
static _CONSTEXPR color_t color_chocolate = COLOR_CHOCOLATE;
#define COLOR_CORAL { 255, 127, 80, 255 }
#define COLOR_CORAL_FLT { 1.f, 0.498039216f, 0.31372549f, 1.f }
#define COLOR_CORAL_INT 0xFF7F50FF
static _CONSTEXPR color_t color_coral = COLOR_CORAL;
#define COLOR_CORNFLOWER_BLUE { 100, 149, 237, 255 }
#define COLOR_CORNFLOWER_BLUE_FLT { 0.392156863f, 0.584313725f, 0.929411765f, 1.f }
#define COLOR_CORNFLOWER_BLUE_INT 0x6495EDFF
static _CONSTEXPR color_t color_cornflower_blue = COLOR_CORNFLOWER_BLUE;
#define COLOR_CORNSILK { 255, 248, 220, 255 }
#define COLOR_CORNSILK_FLT { 1.f, 0.97254902f, 0.862745098f, 1.f }
#define COLOR_CORNSILK_INT 0xFFF8DCFF
static _CONSTEXPR color_t color_cornsilk = COLOR_CORNSILK;
#define COLOR_CRIMSON { 220, 20, 60, 255 }
#define COLOR_CRIMSON_FLT { 0.862745098f, 0.0784313725f, 0.235294118f, 1.f }
#define COLOR_CRIMSON_INT 0xDC143CFF
static _CONSTEXPR color_t color_crimson = COLOR_CRIMSON;
#define COLOR_CYAN { 0, 255, 255, 255 }
#define COLOR_CYAN_FLT { 0.f, 1.f, 1.f, 1.f }
#define COLOR_CYAN_INT 0x00FFFFFF
static _CONSTEXPR color_t color_cyan = COLOR_CYAN;
#define COLOR_DARK_BLUE { 0, 0, 139, 255 }
#define COLOR_DARK_BLUE_FLT { 0.f, 0.f, 0.545098039f, 1.f }
#define COLOR_DARK_BLUE_INT 0x00008BFF
static _CONSTEXPR color_t color_dark_blue = COLOR_DARK_BLUE;
#define COLOR_DARK_CYAN { 0, 139, 139, 255 }
#define COLOR_DARK_CYAN_FLT { 0.f, 0.545098039f, 0.545098039f, 1.f }
#define COLOR_DARK_CYAN_INT 0x008B8BFF
static _CONSTEXPR color_t color_dark_cyan = COLOR_DARK_CYAN;
#define COLOR_DARK_GOLDENROD { 184, 134, 11, 255 }
#define COLOR_DARK_GOLDENROD_FLT { 0.721568627f, 0.525490196f, 0.0431372549f, 1.f }
#define COLOR_DARK_GOLDENROD_INT 0xB8860BFF
static _CONSTEXPR color_t color_dark_goldenrod = COLOR_DARK_GOLDENROD;
#define COLOR_DARK_GRAY { 169, 169, 169, 255 }
#define COLOR_DARK_GRAY_FLT { 0.662745098f, 0.662745098f, 0.662745098f, 1.f }
#define COLOR_DARK_GRAY_INT 0xA9A9A9FF
static _CONSTEXPR color_t color_dark_gray = COLOR_DARK_GRAY;
#define COLOR_DARK_GREEN { 0, 100, 0, 255 }
#define COLOR_DARK_GREEN_FLT { 0.f, 0.392156863f, 0.f, 1.f }
#define COLOR_DARK_GREEN_INT 0x006400FF
static _CONSTEXPR color_t color_dark_green = COLOR_DARK_GREEN;
#define COLOR_DARK_KHAKI { 189, 183, 107, 255 }
#define COLOR_DARK_KHAKI_FLT { 0.741176471f, 0.717647059f, 0.419607843f, 1.f }
#define COLOR_DARK_KHAKI_INT 0xBDB76BFF
static _CONSTEXPR color_t color_dark_khaki = COLOR_DARK_KHAKI;
#define COLOR_DARK_MAGENTA { 139, 0, 139, 255 }
#define COLOR_DARK_MAGENTA_FLT { 0.545098039f, 0.f, 0.545098039f, 1.f }
#define COLOR_DARK_MAGENTA_INT 0x8B008BFF
static _CONSTEXPR color_t color_dark_magenta = COLOR_DARK_MAGENTA;
#define COLOR_DARK_OLIVE_GREEN { 85, 107, 47, 255 }
#define COLOR_DARK_OLIVE_GREEN_FLT { 0.333333333f, 0.419607843f, 0.184313725f, 1.f }
#define COLOR_DARK_OLIVE_GREEN_INT 0x556B2FFF
static _CONSTEXPR color_t color_dark_olive_green = COLOR_DARK_OLIVE_GREEN;
#define COLOR_DARK_ORANGE { 255, 140, 0, 255 }
#define COLOR_DARK_ORANGE_FLT { 1.f, 0.549019608f, 0.f, 1.f }
#define COLOR_DARK_ORANGE_INT 0xFF8C00FF
static _CONSTEXPR color_t color_dark_orange = COLOR_DARK_ORANGE;
#define COLOR_DARK_ORCHID { 153, 50, 204, 255 }
#define COLOR_DARK_ORCHID_FLT { 0.6f, 0.196078431f, 0.8f, 1.f }
#define COLOR_DARK_ORCHID_INT 0x9932CCFF
static _CONSTEXPR color_t color_dark_orchid = COLOR_DARK_ORCHID;
#define COLOR_DARK_RED { 139, 0, 0, 255 }
#define COLOR_DARK_RED_FLT { 0.545098039f, 0.f, 0.f, 1.f }
#define COLOR_DARK_RED_INT 0x8B0000FF
static _CONSTEXPR color_t color_dark_red = COLOR_DARK_RED;
#define COLOR_DARK_SALMON { 233, 150, 122, 255 }
#define COLOR_DARK_SALMON_FLT { 0.91372549f, 0.588235294f, 0.478431373f, 1.f }
#define COLOR_DARK_SALMON_INT 0xE9967AFF
static _CONSTEXPR color_t color_dark_salmon = COLOR_DARK_SALMON;
#define COLOR_DARK_SEA_GREEN { 143, 188, 143, 255 }
#define COLOR_DARK_SEA_GREEN_FLT { 0.560784314f, 0.737254902f, 0.560784314f, 1.f }
#define COLOR_DARK_SEA_GREEN_INT 0x8FBC8FFF
static _CONSTEXPR color_t color_dark_sea_green = COLOR_DARK_SEA_GREEN;
#define COLOR_DARK_SLATE_BLUE { 72, 61, 139, 255 }
#define COLOR_DARK_SLATE_BLUE_FLT { 0.282352941f, 0.239215686f, 0.545098039f, 1.f }
#define COLOR_DARK_SLATE_BLUE_INT 0x483D8BFF
static _CONSTEXPR color_t color_dark_slate_blue = COLOR_DARK_SLATE_BLUE;
#define COLOR_DARK_SLATE_GRAY { 47, 79, 79, 255 }
#define COLOR_DARK_SLATE_GRAY_FLT { 0.184313725f, 0.309803922f, 0.309803922f, 1.f }
#define COLOR_DARK_SLATE_GRAY_INT 0x2F4F4FFF
static _CONSTEXPR color_t color_dark_slate_gray = COLOR_DARK_SLATE_GRAY;
#define COLOR_DARK_TURQUOISE { 0, 206, 209, 255 }
#define COLOR_DARK_TURQUOISE_FLT { 0.f, 0.807843137f, 0.819607843f, 1.f }
#define COLOR_DARK_TURQUOISE_INT 0x00CED1FF
static _CONSTEXPR color_t color_dark_turquoise = COLOR_DARK_TURQUOISE;
#define COLOR_DARK_VIOLET { 148, 0, 211, 255 }
#define COLOR_DARK_VIOLET_FLT { 0.580392157f, 0.f, 0.82745098f, 1.f }
#define COLOR_DARK_VIOLET_INT 0x9400D3FF
static _CONSTEXPR color_t color_dark_violet = COLOR_DARK_VIOLET;
#define COLOR_DEEP_PINK { 255, 20, 147, 255 }
#define COLOR_DEEP_PINK_FLT { 1.f, 0.0784313725f, 0.576470588f, 1.f }
#define COLOR_DEEP_PINK_INT 0xFF1493FF
static _CONSTEXPR color_t color_deep_pink = COLOR_DEEP_PINK;
#define COLOR_DEEP_SKY_BLUE { 0, 191, 255, 255 }
#define COLOR_DEEP_SKY_BLUE_FLT { 0.f, 0.749019608f, 1.f, 1.f }
#define COLOR_DEEP_SKY_BLUE_INT 0x00BFFFFF
static _CONSTEXPR color_t color_deep_sky_blue = COLOR_DEEP_SKY_BLUE;
#define COLOR_DIM_GRAY { 105, 105, 105, 255 }
#define COLOR_DIM_GRAY_FLT { 0.411764706f, 0.411764706f, 0.411764706f, 1.f }
#define COLOR_DIM_GRAY_INT 0x696969FF
static _CONSTEXPR color_t color_dim_gray = COLOR_DIM_GRAY;
#define COLOR_DODGER_BLUE { 30, 144, 255, 255 }
#define COLOR_DODGER_BLUE_FLT { 0.117647059f, 0.564705882f, 1.f, 1.f }
#define COLOR_DODGER_BLUE_INT 0x1E90FFFF
static _CONSTEXPR color_t color_dodger_blue = COLOR_DODGER_BLUE;
#define COLOR_FIREBRICK { 178, 34, 34, 255 }
#define COLOR_FIREBRICK_FLT { 0.698039216f, 0.133333333f, 0.133333333f, 1.f }
#define COLOR_FIREBRICK_INT 0xB22222FF
static _CONSTEXPR color_t color_firebrick = COLOR_FIREBRICK;
#define COLOR_FLORAL_WHITE { 255, 250, 240, 255 }
#define COLOR_FLORAL_WHITE_FLT { 1.f, 0.980392157f, 0.941176471f, 1.f }
#define COLOR_FLORAL_WHITE_INT 0xFFFAF0FF
static _CONSTEXPR color_t color_floral_white = COLOR_FLORAL_WHITE;
#define COLOR_FOREST_GREEN { 34, 139, 34, 255 }
#define COLOR_FOREST_GREEN_FLT { 0.133333333f, 0.545098039f, 0.133333333f, 1.f }
#define COLOR_FOREST_GREEN_INT 0x228B22FF
static _CONSTEXPR color_t color_forest_green = COLOR_FOREST_GREEN;
#define COLOR_FUCHSIA { 255, 0, 255, 255 }
#define COLOR_FUCHSIA_FLT { 1.f, 0.f, 1.f, 1.f }
#define COLOR_FUCHSIA_INT 0xFF00FFFF
static _CONSTEXPR color_t color_fuchsia = COLOR_FUCHSIA;
#define COLOR_GAINSBORO { 220, 220, 220, 255 }
#define COLOR_GAINSBORO_FLT { 0.862745098f, 0.862745098f, 0.862745098f, 1.f }
#define COLOR_GAINSBORO_INT 0xDCDCDCFF
static _CONSTEXPR color_t color_gainsboro = COLOR_GAINSBORO;
#define COLOR_GHOST_WHITE { 248, 248, 255, 255 }
#define COLOR_GHOST_WHITE_FLT { 0.97254902f, 0.97254902f, 1.f, 1.f }
#define COLOR_GHOST_WHITE_INT 0xF8F8FFFF
static _CONSTEXPR color_t color_ghost_white = COLOR_GHOST_WHITE;
#define COLOR_GOLD { 255, 215, 0, 255 }
#define COLOR_GOLD_FLT { 1.f, 0.843137255f, 0.f, 1.f }
#define COLOR_GOLD_INT 0xFFD700FF
static _CONSTEXPR color_t color_gold = COLOR_GOLD;
#define COLOR_GOLDENROD { 218, 165, 32, 255 }
#define COLOR_GOLDENROD_FLT { 0.854901961f, 0.647058824f, 0.125490196f, 1.f }
#define COLOR_GOLDENROD_INT 0xDAA520FF
static _CONSTEXPR color_t color_goldenrod = COLOR_GOLDENROD;
#define COLOR_GRAY { 190, 190, 190, 255 }
#define COLOR_GRAY_FLT { 0.745098039f, 0.745098039f, 0.745098039f, 1.f }
#define COLOR_GRAY_INT 0xBEBEBEFF
static _CONSTEXPR color_t color_gray = COLOR_GRAY;
#define COLOR_WEB_GRAY { 128, 128, 128, 255 }
#define COLOR_WEB_GRAY_FLT { 0.501960784f, 0.501960784f, 0.501960784f, 1.f }
#define COLOR_WEB_GRAY_INT 0x808080FF
static _CONSTEXPR color_t color_web_gray = COLOR_WEB_GRAY;
#define COLOR_GREEN { 0, 255, 0, 255 }
#define COLOR_GREEN_FLT { 0.f, 1.f, 0.f, 1.f }
#define COLOR_GREEN_INT 0x00FF00FF
static _CONSTEXPR color_t color_green = COLOR_GREEN;
#define COLOR_WEB_GREEN { 0, 128, 0, 255 }
#define COLOR_WEB_GREEN_FLT { 0.f, 0.501960784f, 0.f, 1.f }
#define COLOR_WEB_GREEN_INT 0x008000FF
static _CONSTEXPR color_t color_web_green = COLOR_WEB_GREEN;
#define COLOR_GREEN_YELLOW { 173, 255, 47, 255 }
#define COLOR_GREEN_YELLOW_FLT { 0.678431373f, 1.f, 0.184313725f, 1.f }
#define COLOR_GREEN_YELLOW_INT 0xADFF2FFF
static _CONSTEXPR color_t color_green_yellow = COLOR_GREEN_YELLOW;
#define COLOR_HONEYDEW { 240, 255, 240, 255 }
#define COLOR_HONEYDEW_FLT { 0.941176471f, 1.f, 0.941176471f, 1.f }
#define COLOR_HONEYDEW_INT 0xF0FFF0FF
static _CONSTEXPR color_t color_honeydew = COLOR_HONEYDEW;
#define COLOR_HOT_PINK { 255, 105, 180, 255 }
#define COLOR_HOT_PINK_FLT { 1.f, 0.411764706f, 0.705882353f, 1.f }
#define COLOR_HOT_PINK_INT 0xFF69B4FF
static _CONSTEXPR color_t color_hot_pink = COLOR_HOT_PINK;
#define COLOR_INDIAN_RED { 205, 92, 92, 255 }
#define COLOR_INDIAN_RED_FLT { 0.803921569f, 0.360784314f, 0.360784314f, 1.f }
#define COLOR_INDIAN_RED_INT 0xCD5C5CFF
static _CONSTEXPR color_t color_indian_red = COLOR_INDIAN_RED;
#define COLOR_INDIGO { 75, 0, 130, 255 }
#define COLOR_INDIGO_FLT { 0.294117647f, 0.f, 0.509803922f, 1.f }
#define COLOR_INDIGO_INT 0x4B0082FF
static _CONSTEXPR color_t color_indigo = COLOR_INDIGO;
#define COLOR_IVORY { 255, 255, 240, 255 }
#define COLOR_IVORY_FLT { 1.f, 1.f, 0.941176471f, 1.f }
#define COLOR_IVORY_INT 0xFFFFF0FF
static _CONSTEXPR color_t color_ivory = COLOR_IVORY;
#define COLOR_KHAKI { 240, 230, 140, 255 }
#define COLOR_KHAKI_FLT { 0.941176471f, 0.901960784f, 0.549019608f, 1.f }
#define COLOR_KHAKI_INT 0xF0E68CFF
static _CONSTEXPR color_t color_khaki = COLOR_KHAKI;
#define COLOR_LAVENDER { 230, 230, 250, 255 }
#define COLOR_LAVENDER_FLT { 0.901960784f, 0.901960784f, 0.980392157f, 1.f }
#define COLOR_LAVENDER_INT 0xE6E6FAFF
static _CONSTEXPR color_t color_lavender = COLOR_LAVENDER;
#define COLOR_LAVENDER_BLUSH { 255, 240, 245, 255 }
#define COLOR_LAVENDER_BLUSH_FLT { 1.f, 0.941176471f, 0.960784314f, 1.f }
#define COLOR_LAVENDER_BLUSH_INT 0xFFF0F5FF
static _CONSTEXPR color_t color_lavender_blush = COLOR_LAVENDER_BLUSH;
#define COLOR_LAWN_GREEN { 124, 252, 0, 255 }
#define COLOR_LAWN_GREEN_FLT { 0.48627451f, 0.988235294f, 0.f, 1.f }
#define COLOR_LAWN_GREEN_INT 0x7CFC00FF
static _CONSTEXPR color_t color_lawn_green = COLOR_LAWN_GREEN;
#define COLOR_LEMON_CHIFFON { 255, 250, 205, 255 }
#define COLOR_LEMON_CHIFFON_FLT { 1.f, 0.980392157f, 0.803921569f, 1.f }
#define COLOR_LEMON_CHIFFON_INT 0xFFFACDFF
static _CONSTEXPR color_t color_lemon_chiffon = COLOR_LEMON_CHIFFON;
#define COLOR_LIGHT_BLUE { 173, 216, 230, 255 }
#define COLOR_LIGHT_BLUE_FLT { 0.678431373f, 0.847058824f, 0.901960784f, 1.f }
#define COLOR_LIGHT_BLUE_INT 0xADD8E6FF
static _CONSTEXPR color_t color_light_blue = COLOR_LIGHT_BLUE;
#define COLOR_LIGHT_CORAL { 240, 128, 128, 255 }
#define COLOR_LIGHT_CORAL_FLT { 0.941176471f, 0.501960784f, 0.501960784f, 1.f }
#define COLOR_LIGHT_CORAL_INT 0xF08080FF
static _CONSTEXPR color_t color_light_coral = COLOR_LIGHT_CORAL;
#define COLOR_LIGHT_CYAN { 224, 255, 255, 255 }
#define COLOR_LIGHT_CYAN_FLT { 0.878431373f, 1.f, 1.f, 1.f }
#define COLOR_LIGHT_CYAN_INT 0xE0FFFFFF
static _CONSTEXPR color_t color_light_cyan = COLOR_LIGHT_CYAN;
#define COLOR_LIGHT_GOLDENROD { 250, 250, 210, 255 }
#define COLOR_LIGHT_GOLDENROD_FLT { 0.980392157f, 0.980392157f, 0.823529412f, 1.f }
#define COLOR_LIGHT_GOLDENROD_INT 0xFAFAD2FF
static _CONSTEXPR color_t color_light_goldenrod = COLOR_LIGHT_GOLDENROD;
#define COLOR_LIGHT_GRAY { 211, 211, 211, 255 }
#define COLOR_LIGHT_GRAY_FLT { 0.82745098f, 0.82745098f, 0.82745098f, 1.f }
#define COLOR_LIGHT_GRAY_INT 0xD3D3D3FF
static _CONSTEXPR color_t color_light_gray = COLOR_LIGHT_GRAY;
#define COLOR_LIGHT_GREEN { 144, 238, 144, 255 }
#define COLOR_LIGHT_GREEN_FLT { 0.564705882f, 0.933333333f, 0.564705882f, 1.f }
#define COLOR_LIGHT_GREEN_INT 0x90EE90FF
static _CONSTEXPR color_t color_light_green = COLOR_LIGHT_GREEN;
#define COLOR_LIGHT_PINK { 255, 182, 193, 255 }
#define COLOR_LIGHT_PINK_FLT { 1.f, 0.71372549f, 0.756862745f, 1.f }
#define COLOR_LIGHT_PINK_INT 0xFFB6C1FF
static _CONSTEXPR color_t color_light_pink = COLOR_LIGHT_PINK;
#define COLOR_LIGHT_SALMON { 255, 160, 122, 255 }
#define COLOR_LIGHT_SALMON_FLT { 1.f, 0.62745098f, 0.478431373f, 1.f }
#define COLOR_LIGHT_SALMON_INT 0xFFA07AFF
static _CONSTEXPR color_t color_light_salmon = COLOR_LIGHT_SALMON;
#define COLOR_LIGHT_SEA_GREEN { 32, 178, 170, 255 }
#define COLOR_LIGHT_SEA_GREEN_FLT { 0.125490196f, 0.698039216f, 0.666666667f, 1.f }
#define COLOR_LIGHT_SEA_GREEN_INT 0x20B2AAFF
static _CONSTEXPR color_t color_light_sea_green = COLOR_LIGHT_SEA_GREEN;
#define COLOR_LIGHT_SKY_BLUE { 135, 206, 250, 255 }
#define COLOR_LIGHT_SKY_BLUE_FLT { 0.529411765f, 0.807843137f, 0.980392157f, 1.f }
#define COLOR_LIGHT_SKY_BLUE_INT 0x87CEFAFF
static _CONSTEXPR color_t color_light_sky_blue = COLOR_LIGHT_SKY_BLUE;
#define COLOR_LIGHT_SLATE_GRAY { 119, 136, 153, 255 }
#define COLOR_LIGHT_SLATE_GRAY_FLT { 0.466666667f, 0.533333333f, 0.6f, 1.f }
#define COLOR_LIGHT_SLATE_GRAY_INT 0x778899FF
static _CONSTEXPR color_t color_light_slate_gray = COLOR_LIGHT_SLATE_GRAY;
#define COLOR_LIGHT_STEEL_BLUE { 176, 196, 222, 255 }
#define COLOR_LIGHT_STEEL_BLUE_FLT { 0.690196078f, 0.768627451f, 0.870588235f, 1.f }
#define COLOR_LIGHT_STEEL_BLUE_INT 0xB0C4DEFF
static _CONSTEXPR color_t color_light_steel_blue = COLOR_LIGHT_STEEL_BLUE;
#define COLOR_LIGHT_YELLOW { 255, 255, 224, 255 }
#define COLOR_LIGHT_YELLOW_FLT { 1.f, 1.f, 0.878431373f, 1.f }
#define COLOR_LIGHT_YELLOW_INT 0xFFFFE0FF
static _CONSTEXPR color_t color_light_yellow = COLOR_LIGHT_YELLOW;
#define COLOR_LIME { 0, 255, 0, 255 }
#define COLOR_LIME_FLT { 0.f, 1.f, 0.f, 1.f }
#define COLOR_LIME_INT 0x00FF00FF
static _CONSTEXPR color_t color_lime = COLOR_LIME;
#define COLOR_LIME_GREEN { 50, 205, 50, 255 }
#define COLOR_LIME_GREEN_FLT { 0.196078431f, 0.803921569f, 0.196078431f, 1.f }
#define COLOR_LIME_GREEN_INT 0x32CD32FF
static _CONSTEXPR color_t color_lime_green = COLOR_LIME_GREEN;
#define COLOR_LINEN { 250, 240, 230, 255 }
#define COLOR_LINEN_FLT { 0.980392157f, 0.941176471f, 0.901960784f, 1.f }
#define COLOR_LINEN_INT 0xFAF0E6FF
static _CONSTEXPR color_t color_linen = COLOR_LINEN;
#define COLOR_MAGENTA { 255, 0, 255, 255 }
#define COLOR_MAGENTA_FLT { 1.f, 0.f, 1.f, 1.f }
#define COLOR_MAGENTA_INT 0xFF00FFFF
static _CONSTEXPR color_t color_magenta = COLOR_MAGENTA;
#define COLOR_MAROON { 176, 48, 96, 255 }
#define COLOR_MAROON_FLT { 0.690196078f, 0.188235294f, 0.376470588f, 1.f }
#define COLOR_MAROON_INT 0xB03060FF
static _CONSTEXPR color_t color_maroon = COLOR_MAROON;
#define COLOR_WEB_MAROON { 128, 0, 0, 255 }
#define COLOR_WEB_MAROON_FLT { 0.501960784f, 0.f, 0.f, 1.f }
#define COLOR_WEB_MAROON_INT 0x800000FF
static _CONSTEXPR color_t color_web_maroon = COLOR_WEB_MAROON;
#define COLOR_MEDIUM_AQUAMARINE { 102, 205, 170, 255 }
#define COLOR_MEDIUM_AQUAMARINE_FLT { 0.4f, 0.803921569f, 0.666666667f, 1.f }
#define COLOR_MEDIUM_AQUAMARINE_INT 0x66CDAAFF
static _CONSTEXPR color_t color_medium_aquamarine = COLOR_MEDIUM_AQUAMARINE;
#define COLOR_MEDIUM_BLUE { 0, 0, 205, 255 }
#define COLOR_MEDIUM_BLUE_FLT { 0.f, 0.f, 0.803921569f, 1.f }
#define COLOR_MEDIUM_BLUE_INT 0x0000CDFF
static _CONSTEXPR color_t color_medium_blue = COLOR_MEDIUM_BLUE;
#define COLOR_MEDIUM_ORCHID { 186, 85, 211, 255 }
#define COLOR_MEDIUM_ORCHID_FLT { 0.729411765f, 0.333333333f, 0.82745098f, 1.f }
#define COLOR_MEDIUM_ORCHID_INT 0xBA55D3FF
static _CONSTEXPR color_t color_medium_orchid = COLOR_MEDIUM_ORCHID;
#define COLOR_MEDIUM_PURPLE { 147, 112, 219, 255 }
#define COLOR_MEDIUM_PURPLE_FLT { 0.576470588f, 0.439215686f, 0.858823529f, 1.f }
#define COLOR_MEDIUM_PURPLE_INT 0x9370DBFF
static _CONSTEXPR color_t color_medium_purple = COLOR_MEDIUM_PURPLE;
#define COLOR_MEDIUM_SEA_GREEN { 60, 179, 113, 255 }
#define COLOR_MEDIUM_SEA_GREEN_FLT { 0.235294118f, 0.701960784f, 0.443137255f, 1.f }
#define COLOR_MEDIUM_SEA_GREEN_INT 0x3CB371FF
static _CONSTEXPR color_t color_medium_sea_green = COLOR_MEDIUM_SEA_GREEN;
#define COLOR_MEDIUM_SLATE_BLUE { 123, 104, 238, 255 }
#define COLOR_MEDIUM_SLATE_BLUE_FLT { 0.482352941f, 0.407843137f, 0.933333333f, 1.f }
#define COLOR_MEDIUM_SLATE_BLUE_INT 0x7B68EEFF
static _CONSTEXPR color_t color_medium_slate_blue = COLOR_MEDIUM_SLATE_BLUE;
#define COLOR_MEDIUM_SPRING_GREEN { 0, 250, 154, 255 }
#define COLOR_MEDIUM_SPRING_GREEN_FLT { 0.f, 0.980392157f, 0.603921569f, 1.f }
#define COLOR_MEDIUM_SPRING_GREEN_INT 0x00FA9AFF
static _CONSTEXPR color_t color_medium_spring_green = COLOR_MEDIUM_SPRING_GREEN;
#define COLOR_MEDIUM_TURQUOISE { 72, 209, 204, 255 }
#define COLOR_MEDIUM_TURQUOISE_FLT { 0.282352941f, 0.819607843f, 0.8f, 1.f }
#define COLOR_MEDIUM_TURQUOISE_INT 0x48D1CCFF
static _CONSTEXPR color_t color_medium_turquoise = COLOR_MEDIUM_TURQUOISE;
#define COLOR_MEDIUM_VIOLET_RED { 199, 21, 133, 255 }
#define COLOR_MEDIUM_VIOLET_RED_FLT { 0.780392157f, 0.0823529412f, 0.521568627f, 1.f }
#define COLOR_MEDIUM_VIOLET_RED_INT 0xC71585FF
static _CONSTEXPR color_t color_medium_violet_red = COLOR_MEDIUM_VIOLET_RED;
#define COLOR_MIDNIGHT_BLUE { 25, 25, 112, 255 }
#define COLOR_MIDNIGHT_BLUE_FLT { 0.0980392157f, 0.0980392157f, 0.439215686f, 1.f }
#define COLOR_MIDNIGHT_BLUE_INT 0x191970FF
static _CONSTEXPR color_t color_midnight_blue = COLOR_MIDNIGHT_BLUE;
#define COLOR_MINT_CREAM { 245, 255, 250, 255 }
#define COLOR_MINT_CREAM_FLT { 0.960784314f, 1.f, 0.980392157f, 1.f }
#define COLOR_MINT_CREAM_INT 0xF5FFFAFF
static _CONSTEXPR color_t color_mint_cream = COLOR_MINT_CREAM;
#define COLOR_MISTY_ROSE { 255, 228, 225, 255 }
#define COLOR_MISTY_ROSE_FLT { 1.f, 0.894117647f, 0.882352941f, 1.f }
#define COLOR_MISTY_ROSE_INT 0xFFE4E1FF
static _CONSTEXPR color_t color_misty_rose = COLOR_MISTY_ROSE;
#define COLOR_MOCCASIN { 255, 228, 181, 255 }
#define COLOR_MOCCASIN_FLT { 1.f, 0.894117647f, 0.709803922f, 1.f }
#define COLOR_MOCCASIN_INT 0xFFE4B5FF
static _CONSTEXPR color_t color_moccasin = COLOR_MOCCASIN;
#define COLOR_NAVAJO_WHITE { 255, 222, 173, 255 }
#define COLOR_NAVAJO_WHITE_FLT { 1.f, 0.870588235f, 0.678431373f, 1.f }
#define COLOR_NAVAJO_WHITE_INT 0xFFDEADFF
static _CONSTEXPR color_t color_navajo_white = COLOR_NAVAJO_WHITE;
#define COLOR_NAVY_BLUE { 0, 0, 128, 255 }
#define COLOR_NAVY_BLUE_FLT { 0.f, 0.f, 0.501960784f, 1.f }
#define COLOR_NAVY_BLUE_INT 0x000080FF
static _CONSTEXPR color_t color_navy_blue = COLOR_NAVY_BLUE;
#define COLOR_OLD_LACE { 253, 245, 230, 255 }
#define COLOR_OLD_LACE_FLT { 0.992156863f, 0.960784314f, 0.901960784f, 1.f }
#define COLOR_OLD_LACE_INT 0xFDF5E6FF
static _CONSTEXPR color_t color_old_lace = COLOR_OLD_LACE;
#define COLOR_OLIVE { 128, 128, 0, 255 }
#define COLOR_OLIVE_FLT { 0.501960784f, 0.501960784f, 0.f, 1.f }
#define COLOR_OLIVE_INT 0x808000FF
static _CONSTEXPR color_t color_olive = COLOR_OLIVE;
#define COLOR_OLIVE_DRAB { 107, 142, 35, 255 }
#define COLOR_OLIVE_DRAB_FLT { 0.419607843f, 0.556862745f, 0.137254902f, 1.f }
#define COLOR_OLIVE_DRAB_INT 0x6B8E23FF
static _CONSTEXPR color_t color_olive_drab = COLOR_OLIVE_DRAB;
#define COLOR_ORANGE { 255, 165, 0, 255 }
#define COLOR_ORANGE_FLT { 1.f, 0.647058824f, 0.f, 1.f }
#define COLOR_ORANGE_INT 0xFFA500FF
static _CONSTEXPR color_t color_orange = COLOR_ORANGE;
#define COLOR_ORANGE_RED { 255, 69, 0, 255 }
#define COLOR_ORANGE_RED_FLT { 1.f, 0.270588235f, 0.f, 1.f }
#define COLOR_ORANGE_RED_INT 0xFF4500FF
static _CONSTEXPR color_t color_orange_red = COLOR_ORANGE_RED;
#define COLOR_ORCHID { 218, 112, 214, 255 }
#define COLOR_ORCHID_FLT { 0.854901961f, 0.439215686f, 0.839215686f, 1.f }
#define COLOR_ORCHID_INT 0xDA70D6FF
static _CONSTEXPR color_t color_orchid = COLOR_ORCHID;
#define COLOR_PALE_GOLDENROD { 238, 232, 170, 255 }
#define COLOR_PALE_GOLDENROD_FLT { 0.933333333f, 0.909803922f, 0.666666667f, 1.f }
#define COLOR_PALE_GOLDENROD_INT 0xEEE8AAFF
static _CONSTEXPR color_t color_pale_goldenrod = COLOR_PALE_GOLDENROD;
#define COLOR_PALE_GREEN { 152, 251, 152, 255 }
#define COLOR_PALE_GREEN_FLT { 0.596078431f, 0.984313725f, 0.596078431f, 1.f }
#define COLOR_PALE_GREEN_INT 0x98FB98FF
static _CONSTEXPR color_t color_pale_green = COLOR_PALE_GREEN;
#define COLOR_PALE_TURQUOISE { 175, 238, 238, 255 }
#define COLOR_PALE_TURQUOISE_FLT { 0.68627451f, 0.933333333f, 0.933333333f, 1.f }
#define COLOR_PALE_TURQUOISE_INT 0xAFEEEEFF
static _CONSTEXPR color_t color_pale_turquoise = COLOR_PALE_TURQUOISE;
#define COLOR_PALE_VIOLET_RED { 219, 112, 147, 255 }
#define COLOR_PALE_VIOLET_RED_FLT { 0.858823529f, 0.439215686f, 0.576470588f, 1.f }
#define COLOR_PALE_VIOLET_RED_INT 0xDB7093FF
static _CONSTEXPR color_t color_pale_violet_red = COLOR_PALE_VIOLET_RED;
#define COLOR_PAPAYA_WHIP { 255, 239, 213, 255 }
#define COLOR_PAPAYA_WHIP_FLT { 1.f, 0.937254902f, 0.835294118f, 1.f }
#define COLOR_PAPAYA_WHIP_INT 0xFFEFD5FF
static _CONSTEXPR color_t color_papaya_whip = COLOR_PAPAYA_WHIP;
#define COLOR_PEACH_PUFF { 255, 218, 185, 255 }
#define COLOR_PEACH_PUFF_FLT { 1.f, 0.854901961f, 0.725490196f, 1.f }
#define COLOR_PEACH_PUFF_INT 0xFFDAB9FF
static _CONSTEXPR color_t color_peach_puff = COLOR_PEACH_PUFF;
#define COLOR_PERU { 205, 133, 63, 255 }
#define COLOR_PERU_FLT { 0.803921569f, 0.521568627f, 0.247058824f, 1.f }
#define COLOR_PERU_INT 0xCD853FFF
static _CONSTEXPR color_t color_peru = COLOR_PERU;
#define COLOR_PINK { 255, 192, 203, 255 }
#define COLOR_PINK_FLT { 1.f, 0.752941176f, 0.796078431f, 1.f }
#define COLOR_PINK_INT 0xFFC0CBFF
static _CONSTEXPR color_t color_pink = COLOR_PINK;
#define COLOR_PLUM { 221, 160, 221, 255 }
#define COLOR_PLUM_FLT { 0.866666667f, 0.62745098f, 0.866666667f, 1.f }
#define COLOR_PLUM_INT 0xDDA0DDFF
static _CONSTEXPR color_t color_plum = COLOR_PLUM;
#define COLOR_POWDER_BLUE { 176, 224, 230, 255 }
#define COLOR_POWDER_BLUE_FLT { 0.690196078f, 0.878431373f, 0.901960784f, 1.f }
#define COLOR_POWDER_BLUE_INT 0xB0E0E6FF
static _CONSTEXPR color_t color_powder_blue = COLOR_POWDER_BLUE;
#define COLOR_PURPLE { 160, 32, 240, 255 }
#define COLOR_PURPLE_FLT { 0.62745098f, 0.125490196f, 0.941176471f, 1.f }
#define COLOR_PURPLE_INT 0xA020F0FF
static _CONSTEXPR color_t color_purple = COLOR_PURPLE;
#define COLOR_WEB_PURPLE { 128, 0, 128, 255 }
#define COLOR_WEB_PURPLE_FLT { 0.501960784f, 0.f, 0.501960784f, 1.f }
#define COLOR_WEB_PURPLE_INT 0x800080FF
static _CONSTEXPR color_t color_web_purple = COLOR_WEB_PURPLE;
#define COLOR_REBECCA_PURPLE { 102, 51, 153, 255 }
#define COLOR_REBECCA_PURPLE_FLT { 0.4f, 0.2f, 0.6f, 1.f }
#define COLOR_REBECCA_PURPLE_INT 0x663399FF
static _CONSTEXPR color_t color_rebecca_purple = COLOR_REBECCA_PURPLE;
#define COLOR_RED { 255, 0, 0, 255 }
#define COLOR_RED_FLT { 1.f, 0.f, 0.f, 1.f }
#define COLOR_RED_INT 0xFF0000FF
static _CONSTEXPR color_t color_red = COLOR_RED;
#define COLOR_ROSY_BROWN { 188, 143, 143, 255 }
#define COLOR_ROSY_BROWN_FLT { 0.737254902f, 0.560784314f, 0.560784314f, 1.f }
#define COLOR_ROSY_BROWN_INT 0xBC8F8FFF
static _CONSTEXPR color_t color_rosy_brown = COLOR_ROSY_BROWN;
#define COLOR_ROYAL_BLUE { 65, 105, 225, 255 }
#define COLOR_ROYAL_BLUE_FLT { 0.254901961f, 0.411764706f, 0.882352941f, 1.f }
#define COLOR_ROYAL_BLUE_INT 0x4169E1FF
static _CONSTEXPR color_t color_royal_blue = COLOR_ROYAL_BLUE;
#define COLOR_SADDLE_BROWN { 139, 69, 19, 255 }
#define COLOR_SADDLE_BROWN_FLT { 0.545098039f, 0.270588235f, 0.0745098039f, 1.f }
#define COLOR_SADDLE_BROWN_INT 0x8B4513FF
static _CONSTEXPR color_t color_saddle_brown = COLOR_SADDLE_BROWN;
#define COLOR_SALMON { 250, 128, 114, 255 }
#define COLOR_SALMON_FLT { 0.980392157f, 0.501960784f, 0.447058824f, 1.f }
#define COLOR_SALMON_INT 0xFA8072FF
static _CONSTEXPR color_t color_salmon = COLOR_SALMON;
#define COLOR_SANDY_BROWN { 244, 164, 96, 255 }
#define COLOR_SANDY_BROWN_FLT { 0.956862745f, 0.643137255f, 0.376470588f, 1.f }
#define COLOR_SANDY_BROWN_INT 0xF4A460FF
static _CONSTEXPR color_t color_sandy_brown = COLOR_SANDY_BROWN;
#define COLOR_SEA_GREEN { 46, 139, 87, 255 }
#define COLOR_SEA_GREEN_FLT { 0.180392157f, 0.545098039f, 0.341176471f, 1.f }
#define COLOR_SEA_GREEN_INT 0x2E8B57FF
static _CONSTEXPR color_t color_sea_green = COLOR_SEA_GREEN;
#define COLOR_SEASHELL { 255, 245, 238, 255 }
#define COLOR_SEASHELL_FLT { 1.f, 0.960784314f, 0.933333333f, 1.f }
#define COLOR_SEASHELL_INT 0xFFF5EEFF
static _CONSTEXPR color_t color_seashell = COLOR_SEASHELL;
#define COLOR_SIENNA { 160, 82, 45, 255 }
#define COLOR_SIENNA_FLT { 0.62745098f, 0.321568627f, 0.176470588f, 1.f }
#define COLOR_SIENNA_INT 0xA0522DFF
static _CONSTEXPR color_t color_sienna = COLOR_SIENNA;
#define COLOR_SILVER { 192, 192, 192, 255 }
#define COLOR_SILVER_FLT { 0.752941176f, 0.752941176f, 0.752941176f, 1.f }
#define COLOR_SILVER_INT 0xC0C0C0FF
static _CONSTEXPR color_t color_silver = COLOR_SILVER;
#define COLOR_SKY_BLUE { 135, 206, 235, 255 }
#define COLOR_SKY_BLUE_FLT { 0.529411765f, 0.807843137f, 0.921568627f, 1.f }
#define COLOR_SKY_BLUE_INT 0x87CEEBFF
static _CONSTEXPR color_t color_sky_blue = COLOR_SKY_BLUE;
#define COLOR_SLATE_BLUE { 106, 90, 205, 255 }
#define COLOR_SLATE_BLUE_FLT { 0.415686275f, 0.352941176f, 0.803921569f, 1.f }
#define COLOR_SLATE_BLUE_INT 0x6A5ACDFF
static _CONSTEXPR color_t color_slate_blue = COLOR_SLATE_BLUE;
#define COLOR_SLATE_GRAY { 112, 128, 144, 255 }
#define COLOR_SLATE_GRAY_FLT { 0.439215686f, 0.501960784f, 0.564705882f, 1.f }
#define COLOR_SLATE_GRAY_INT 0x708090FF
static _CONSTEXPR color_t color_slate_gray = COLOR_SLATE_GRAY;
#define COLOR_SNOW { 255, 250, 250, 255 }
#define COLOR_SNOW_FLT { 1.f, 0.980392157f, 0.980392157f, 1.f }
#define COLOR_SNOW_INT 0xFFFAFAFF
static _CONSTEXPR color_t color_snow = COLOR_SNOW;
#define COLOR_SPRING_GREEN { 0, 255, 127, 255 }
#define COLOR_SPRING_GREEN_FLT { 0.f, 1.f, 0.498039216f, 1.f }
#define COLOR_SPRING_GREEN_INT 0x00FF7FFF
static _CONSTEXPR color_t color_spring_green = COLOR_SPRING_GREEN;
#define COLOR_STEEL_BLUE { 70, 130, 180, 255 }
#define COLOR_STEEL_BLUE_FLT { 0.274509804f, 0.509803922f, 0.705882353f, 1.f }
#define COLOR_STEEL_BLUE_INT 0x4682B4FF
static _CONSTEXPR color_t color_steel_blue = COLOR_STEEL_BLUE;
#define COLOR_TAN { 210, 180, 140, 255 }
#define COLOR_TAN_FLT { 0.823529412f, 0.705882353f, 0.549019608f, 1.f }
#define COLOR_TAN_INT 0xD2B48CFF
static _CONSTEXPR color_t color_tan = COLOR_TAN;
#define COLOR_TEAL { 0, 128, 128, 255 }
#define COLOR_TEAL_FLT { 0.f, 0.501960784f, 0.501960784f, 1.f }
#define COLOR_TEAL_INT 0x008080FF
static _CONSTEXPR color_t color_teal = COLOR_TEAL;
#define COLOR_THISTLE { 216, 191, 216, 255 }
#define COLOR_THISTLE_FLT { 0.847058824f, 0.749019608f, 0.847058824f, 1.f }
#define COLOR_THISTLE_INT 0xD8BFD8FF
static _CONSTEXPR color_t color_thistle = COLOR_THISTLE;
#define COLOR_TOMATO { 255, 99, 71, 255 }
#define COLOR_TOMATO_FLT { 1.f, 0.388235294f, 0.278431373f, 1.f }
#define COLOR_TOMATO_INT 0xFF6347FF
static _CONSTEXPR color_t color_tomato = COLOR_TOMATO;
#define COLOR_TRANSPARENT { 0, 0, 0, 0 }
#define COLOR_TRANSPARENT_FLT { 0.f, 0.f, 0.f, 0.f }
#define COLOR_TRANSPARENT_INT 0x00000000
static _CONSTEXPR color_t color_transparent = COLOR_TRANSPARENT;
#define COLOR_TURQUOISE { 64, 224, 208, 255 }
#define COLOR_TURQUOISE_FLT { 0.250980392f, 0.878431373f, 0.815686275f, 1.f }
#define COLOR_TURQUOISE_INT 0x40E0D0FF
static _CONSTEXPR color_t color_turquoise = COLOR_TURQUOISE;
#define COLOR_VIOLET { 238, 130, 238, 255 }
#define COLOR_VIOLET_FLT { 0.933333333f, 0.509803922f, 0.933333333f, 1.f }
#define COLOR_VIOLET_INT 0xEE82EEFF
static _CONSTEXPR color_t color_violet = COLOR_VIOLET;
#define COLOR_WHEAT { 245, 222, 179, 255 }
#define COLOR_WHEAT_FLT { 0.960784314f, 0.870588235f, 0.701960784f, 1.f }
#define COLOR_WHEAT_INT 0xF5DEB3FF
static _CONSTEXPR color_t color_wheat = COLOR_WHEAT;
#define COLOR_WHITE { 255, 255, 255, 255 }
#define COLOR_WHITE_FLT { 1.f, 1.f, 1.f, 1.f }
#define COLOR_WHITE_INT 0xFFFFFFFF
static _CONSTEXPR color_t color_white = COLOR_WHITE;
#define COLOR_WHITE_SMOKE { 245, 245, 245, 255 }
#define COLOR_WHITE_SMOKE_FLT { 0.960784314f, 0.960784314f, 0.960784314f, 1.f }
#define COLOR_WHITE_SMOKE_INT 0xF5F5F5FF
static _CONSTEXPR color_t color_white_smoke = COLOR_WHITE_SMOKE;
#define COLOR_YELLOW { 255, 255, 0, 255 }
#define COLOR_YELLOW_FLT { 1.f, 1.f, 0.f, 1.f }
#define COLOR_YELLOW_INT 0xFFFF00FF
static _CONSTEXPR color_t color_yellow = COLOR_YELLOW;
#define COLOR_YELLOW_GREEN { 154, 205, 50, 255 }
#define COLOR_YELLOW_GREEN_FLT { 0.603921569f, 0.803921569f, 0.196078431f, 1.f }
#define COLOR_YELLOW_GREEN_INT 0x9ACD32FF
static _CONSTEXPR color_t color_yellow_green = COLOR_YELLOW_GREEN;
#endif

/*! @typedef color_rgba_t
    @brief Alias for color_t representing RGBA colors.
    @discussion This typedef provides an alternative name for the color_t type, emphasizing its RGBA nature. It is functionally identical to color_t.
*/
typedef color_t color_rgba_t;

/*! @typedef color_rgbaf_t
    @brief Structure representing RGBA colors with floating-point components.
    @discussion This structure holds RGBA color values as floating-point numbers in the range [0.0, 1.0]. The alpha channel represents opacity, where 0.0 is fully transparent and 1.0 is fully opaque.
    @field r Red component (0.0 to 1.0)
    @field g Green component (0.0 to 1.0)
    @field b Blue component (0.0 to 1.0)
    @field a Alpha component (0.0 to 1.0)
*/
typedef struct color_rgbaf_t {
    float r, g, b, a;
} color_rgbaf_t;

/*! @typedef color_hsva_t
    @brief Structure representing HSVA (Hue, Saturation, Value, Alpha) colors.
    @discussion This structure holds HSVA color values where hue is in the range [0.0, 1.0] representing 0-360 degrees, saturation and value are in the range [0.0, 1.0], and alpha represents opacity from 0.0 (transparent) to 1.0 (opaque).
    @field h Hue component (0.0 to 1.0, representing 0-360 degrees)
    @field s Saturation component (0.0 to 1.0)
    @field v Value/Brightness component (0.0 to 1.0)
    @field a Alpha component (0.0 to 1.0)
*/
typedef struct color_hsva_t {
    float h, s, v, a;
} color_hsva_t;

/*! @typedef color_hsla_t
    @brief Structure representing HSLA (Hue, Saturation, Lightness, Alpha) colors.
    @discussion This structure holds HSLA color values where hue is in the range [0.0, 1.0] representing 0-360 degrees, saturation and lightness are in the range [0.0, 1.0], and alpha represents opacity from 0.0 (transparent) to 1.0 (opaque).
    @field h Hue component (0.0 to 1.0, representing 0-360 degrees)
    @field s Saturation component (0.0 to 1.0)
    @field l Lightness component (0.0 to 1.0)
    @field a Alpha component (0.0 to 1.0)
*/
typedef struct color_hsla_t {
    float h, s, l, a;
} color_hsla_t;

/*!
 * @typedef color_lab_t
 * @brief Represents a color in CIE L*a*b* color space.
 * @discussion The CIE L*a*b* color space is a device-independent color model designed to approximate human vision. It separates lightness from color information and is perceptually uniform.
 * @field l Lightness component (0.0 to 100.0, but can exceed these bounds)
 * @field a Green-red axis component (typically -128.0 to 127.0, but can exceed these bounds)
 * @field b Blue-yellow axis component (typically -128.0 to 127.0, but can exceed these bounds)
 * @field alpha Alpha transparency component (0.0 to 1.0)
*/
typedef struct color_lab_t {
    float l, a, b, alpha;
} color_lab_t;

/*!
 * @typedef color_xyz_t
 * @brief Represents a color in CIE XYZ color space.
 * @discussion The CIE XYZ color space is a device-independent color model based on the human visual system's response to red, green, and blue stimuli. It serves as the foundation for other color spaces and is designed to encompass all colors visible to the human eye.
 * @field x X component (red response, typically 0.0 to 1.0, but can exceed these bounds)
 * @field y Y component (luminance/green response, typically 0.0 to 1.0, but can exceed these bounds)
 * @field z Z component (blue response, typically 0.0 to 1.0, but can exceed these bounds)
 * @field a Alpha transparency component (0.0 to 1.0)
*/
typedef struct color_xyz_t {
    float x, y, z, a;
} color_xyz_t;

/*!
 * @typedef color_yuv_t
 * @brief Represents a color in YUV color space.
 * @discussion The YUV color space separates luminance (Y) from chrominance (U and V) components. It is commonly used in video systems and digital broadcasting, with BT.601 standard coefficients used for the conversion.
 * @field y Luminance component (brightness, typically 0.0 to 1.0)
 * @field u Chrominance U component (blue-luminance difference, typically -0.5 to 0.5)
 * @field v Chrominance V component (red-luminance difference, typically -0.5 to 0.5)
 * @field a Alpha transparency component (0.0 to 1.0)
*/
typedef struct color_yuv_t {
    float y, u, v, a;
} color_yuv_t;

/*!
 * @typedef color_cmyk_t
 * @brief Represents a color in CMYK color space.
 * @discussion The CMYK color space is primarily used in printing processes, where colors are created by subtracting varying amounts of cyan, magenta, yellow, and black inks from white light. The 'K' in CMYK stands for black (key) to avoid confusion with blue. This color space is device-dependent and commonly used in professional printing workflows.
 * @field c Cyan component (0.0 to 1.0)
 * @field m Magenta component (0.0 to 1.0)
 * @field y Yellow component (0.0 to 1.0)
 * @field k Black component (0.0 to 1.0)
 * @field a Alpha transparency component (0.0 to 1.0)
*/
typedef struct color_cmyk_t {
    float c, m, y, k, a;
} color_cmyk_t;

/*!
 * @typedef color_rgb_t565
 * @brief Represents a color in RGB565 format with alpha.
 * @discussion RGB565 is a 16-bit color format commonly used in displays, embedded systems, and graphics hardware. It allocates 5 bits for red, 6 bits for green, and 5 bits for blue components, providing 65,536 possible colors. This format is efficient for memory usage while maintaining reasonable color fidelity, particularly for green hues which are more perceptually important.
 * @field rgb565 Packed 16-bit RGB565 color value (5-bit R, 6-bit G, 5-bit B)
 * @field a Alpha transparency component (0-255)
*/
typedef struct color_rgb_t565 {
    uint16_t rgb565;
    uint8_t a;
} color_rgb_t565;

/*!
 * @typedef color_int_t
 * @brief A 32-bit unsigned integer type for representing colors.
 * @discussion This type is used for color values stored as packed 32-bit integers, typically in RGBA format where each component occupies 8 bits. It provides a convenient alias for uint32_t when working with color data in integer form, making code more readable and self-documenting.
*/
typedef uint32_t color_int_t;

/*!
 * @function rgba
 * @brief Creates a color from RGBA components.
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 * @param a Alpha component (0-255).
 * @return A color_t value representing the specified RGBA color.
 * @discussion This function constructs a color_t union from individual 8-bit RGBA components. The alpha channel controls transparency, where 0 is fully transparent and 255 is fully opaque.
*/
color_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/*!
 * @function rgb
 * @brief Creates an opaque color from RGB components.
 * @param r Red component (0-255).
 * @param g Green component (0-255).
 * @param b Blue component (0-255).
 * @return A color_t value representing the specified RGB color with full opacity.
 * @discussion This function constructs a color_t union from RGB components with the alpha channel set to 255 (fully opaque). Equivalent to calling rgba(r, g, b, 255).
*/
color_t rgb(uint8_t r, uint8_t g, uint8_t b);

/*!
 * @function rgbaf
 * @brief Creates a color from floating-point RGBA components.
 * @param r Red component (0.0-1.0).
 * @param g Green component (0.0-1.0).
 * @param b Blue component (0.0-1.0).
 * @param a Alpha component (0.0-1.0).
 * @return A color_t value representing the specified floating-point RGBA color.
 * @discussion This function constructs a color_t union from normalized floating-point RGBA components. Values are clamped to the 0.0-1.0 range and converted to 8-bit integers internally.
*/
color_t rgbaf(float r, float g, float b, float a);

/*!
 * @function rgbf
 * @brief Creates an opaque color from floating-point RGB components.
 * @param r Red component (0.0-1.0).
 * @param g Green component (0.0-1.0).
 * @param b Blue component (0.0-1.0).
 * @return A color_t value representing the specified floating-point RGB color with full opacity.
 * @discussion This function constructs a color_t union from normalized floating-point RGB components with the alpha channel set to 1.0 (fully opaque). Equivalent to calling rgbaf(r, g, b, 1.0f).
*/
color_t rgbf(float r, float g, float b);

/*!
 * @function hsva
 * @brief Creates a color from HSVA components.
 * @param h Hue component (0.0-1.0, where 0.0 = red, 0.333 = green, 0.667 = blue).
 * @param s Saturation component (0.0-1.0, where 0.0 = grayscale, 1.0 = fully saturated).
 * @param v Value/brightness component (0.0-1.0, where 0.0 = black, 1.0 = full brightness).
 * @param a Alpha component (0.0-1.0).
 * @return A color_t value representing the specified HSVA color.
 * @discussion This function constructs a color_t union from HSV color space components. The hue wraps around (1.0 = 0.0), saturation and value are clamped to 0.0-1.0, and the result is converted to RGBA internally.
*/
color_t hsva(float h, float s, float v, float a);

/*!
 * @function hsv
 * @brief Creates an opaque color from HSV components.
 * @param h Hue component (0.0-1.0, where 0.0 = red, 0.333 = green, 0.667 = blue).
 * @param s Saturation component (0.0-1.0, where 0.0 = grayscale, 1.0 = fully saturated).
 * @param v Value/brightness component (0.0-1.0, where 0.0 = black, 1.0 = full brightness).
 * @return A color_t value representing the specified HSV color with full opacity.
 * @discussion This function constructs a color_t union from HSV color space components with the alpha channel set to 1.0 (fully opaque). Equivalent to calling hsva(h, s, v, 1.0f).
*/
color_t hsv(float h, float s, float v);

/*!
 * @function hsla
 * @brief Creates a color from HSLA components.
 * @param h Hue component (0.0-1.0, where 0.0 = red, 0.333 = green, 0.667 = blue).
 * @param s Saturation component (0.0-1.0, where 0.0 = grayscale, 1.0 = fully saturated).
 * @param l Lightness component (0.0-1.0, where 0.0 = black, 0.5 = normal, 1.0 = white).
 * @param a Alpha component (0.0-1.0).
 * @return A color_t value representing the specified HSLA color.
 * @discussion This function constructs a color_t union from HSL color space components. The hue wraps around (1.0 = 0.0), saturation and lightness are clamped to 0.0-1.0, and the result is converted to RGBA internally.
*/
color_t hsla(float h, float s, float l, float a);

/*!
 * @function hsl
 * @brief Creates an opaque color from HSL components.
 * @param h Hue component (0.0-1.0, where 0.0 = red, 0.333 = green, 0.667 = blue).
 * @param s Saturation component (0.0-1.0, where 0.0 = grayscale, 1.0 = fully saturated).
 * @param l Lightness component (0.0-1.0, where 0.0 = black, 0.5 = normal, 1.0 = white).
 * @return A color_t value representing the specified HSL color with full opacity.
 * @discussion This function constructs a color_t union from HSL color space components with the alpha channel set to 1.0 (fully opaque). Equivalent to calling hsla(h, s, l, 1.0f).
*/
color_t hsl(float h, float s, float l);

/*!
 * @function lab
 * @brief Creates a color from CIELAB components.
 * @param l Lightness component (0.0-100.0).
 * @param a Green-red axis component (-128.0 to 128.0).
 * @param b Blue-yellow axis component (-128.0 to 128.0).
 * @param alpha Alpha component (0.0-1.0).
 * @return A color_t value representing the specified CIELAB color.
 * @discussion This function constructs a color_t union from CIELAB color space components. The L*a*b* values are converted to XYZ and then to RGBA internally. This color space is designed to be perceptually uniform.
*/
color_t lab(float l, float a, float b, float alpha);

/*!
 * @function xyz
 * @brief Creates a color from CIEXYZ components.
 * @param x X tristimulus value (0.0-1.0+).
 * @param y Y tristimulus value (0.0-1.0+).
 * @param z Z tristimulus value (0.0-1.0+).
 * @param a Alpha component (0.0-1.0).
 * @return A color_t value representing the specified CIEXYZ color.
 * @discussion This function constructs a color_t union from CIEXYZ color space components. The XYZ values are converted to sRGB and then to RGBA internally. XYZ represents absolute color measurements.
*/
color_t xyz(float x, float y, float z, float a);

/*!
 * @function yuv
 * @brief Creates a color from YUV components.
 * @param y Luma/brightness component (0.0-1.0).
 * @param u Blue-luma difference component (-0.5 to 0.5).
 * @param v Red-luma difference component (-0.5 to 0.5).
 * @param a Alpha component (0.0-1.0).
 * @return A color_t value representing the specified YUV color.
 * @discussion This function constructs a color_t union from YUV color space components using the BT.601 standard. YUV is commonly used in video encoding and separates luminance from chrominance information.
*/
color_t yuv(float y, float u, float v, float a);

/*!
 * @function cmyk
 * @brief Creates a color from CMYK components.
 * @param c Cyan component (0.0-1.0).
 * @param m Magenta component (0.0-1.0).
 * @param y Yellow component (0.0-1.0).
 * @param k Black/key component (0.0-1.0).
 * @param a Alpha component (0.0-1.0).
 * @return A color_t value representing the specified CMYK color.
 * @discussion This function constructs a color_t union from CMYK color space components. CMYK is the standard color model used in printing, where colors are represented as the amount of cyan, magenta, yellow, and black ink needed.
*/
color_t cmyk(float c, float m, float y, float k, float a);

/*!
 * @function rgb_565
 * @brief Creates a color from a 16-bit RGB565 value.
 * @param rgb565 16-bit RGB565 packed color value.
 * @param a Alpha component (0-255).
 * @return A color_t value representing the specified RGB565 color.
 * @discussion This function constructs a color_t union from a 16-bit RGB565 packed color value. RGB565 uses 5 bits for red, 6 bits for green, and 5 bits for blue, providing 65,536 possible colors. Commonly used in embedded systems and older displays.
*/
color_t rgb_565(uint16_t rgb565, uint8_t a);

/*!
 * @function rgba_to_rgbaf
 * @brief Converts an RGBA color to floating-point RGBA format.
 * @param rgba The input RGBA color.
 * @return A color_rgbaf_t structure with normalized floating-point components (0.0-1.0).
 * @discussion This function converts 8-bit RGBA components to normalized floating-point values, which is useful for color calculations that require higher precision.
*/
color_rgbaf_t rgba_to_rgbaf(color_t rgba);

/*!
 * @function rgbaf_to_rgba
 * @brief Converts floating-point RGBA to 8-bit RGBA format.
 * @param rgbaf The input floating-point RGBA color.
 * @return A color_t value with clamped 8-bit components.
 * @discussion This function converts normalized floating-point RGBA components to 8-bit integers, clamping values to the valid 0-255 range.
*/
color_t rgbaf_to_rgba(color_rgbaf_t rgbaf);

/*!
 * @function rgba_to_hsva
 * @brief Converts an RGBA color to HSVA color space.
 * @param rgba The input RGBA color.
 * @return A color_hsva_t structure with hue (0.0-1.0), saturation (0.0-1.0), value (0.0-1.0), and alpha (0.0-1.0).
 * @discussion This function converts RGBA to HSV color space, where hue represents the color angle, saturation represents color purity, and value represents brightness.
*/
color_hsva_t rgba_to_hsva(color_t rgba);

/*!
 * @function hsva_to_rgba
 * @brief Converts HSVA color space to RGBA.
 * @param hsva The input HSVA color.
 * @return A color_t value representing the equivalent RGBA color.
 * @discussion This function converts HSV color space back to RGBA, applying the standard HSV to RGB conversion algorithm.
*/
color_t hsva_to_rgba(color_hsva_t hsva);

/*!
 * @function rgbaf_to_hsva
 * @brief Converts floating-point RGBA to HSVA color space.
 * @param rgbaf The input floating-point RGBA color.
 * @return A color_hsva_t structure with HSV components.
 * @discussion This function converts normalized RGBA to HSV color space, providing higher precision than the 8-bit version.
*/
color_hsva_t rgbaf_to_hsva(color_rgbaf_t rgbaf);

/*!
 * @function hsva_to_rgbaf
 * @brief Converts HSVA color space to floating-point RGBA.
 * @param hsva The input HSVA color.
 * @return A color_rgbaf_t structure with normalized RGBA components.
 * @discussion This function converts HSV color space to normalized RGBA, providing higher precision than the 8-bit version.
*/
color_rgbaf_t hsva_to_rgbaf(color_hsva_t hsva);

/*!
 * @function rgba_to_hsla
 * @brief Converts an RGBA color to HSLA color space.
 * @param rgba The input RGBA color.
 * @return A color_hsla_t structure with hue (0.0-1.0), saturation (0.0-1.0), lightness (0.0-1.0), and alpha (0.0-1.0).
 * @discussion This function converts RGBA to HSL color space, where lightness represents the perceived brightness and saturation represents color purity.
*/
color_hsla_t rgba_to_hsla(color_t rgba);

/*!
 * @function hsla_to_rgba
 * @brief Converts HSLA color space to RGBA.
 * @param hsla The input HSLA color.
 * @return A color_t value representing the equivalent RGBA color.
 * @discussion This function converts HSL color space back to RGBA using the standard HSL to RGB conversion algorithm.
*/
color_t hsla_to_rgba(color_hsla_t hsla);

/*!
 * @function rgbaf_to_hsla
 * @brief Converts floating-point RGBA to HSLA color space.
 * @param rgbaf The input floating-point RGBA color.
 * @return A color_hsla_t structure with HSL components.
 * @discussion This function converts normalized RGBA to HSL color space, providing higher precision than the 8-bit version.
*/
color_hsla_t rgbaf_to_hsla(color_rgbaf_t rgbaf);

/*!
 * @function hsla_to_rgbaf
 * @brief Converts HSLA color space to floating-point RGBA.
 * @param hsla The input HSLA color.
 * @return A color_rgbaf_t structure with normalized RGBA components.
 * @discussion This function converts HSL color space to normalized RGBA, providing higher precision than the 8-bit version.
*/
color_rgbaf_t hsla_to_rgbaf(color_hsla_t hsla);

/*!
 * @function rgba_to_lab
 * @brief Converts an RGBA color to CIELAB color space.
 * @param rgba The input RGBA color.
 * @return A color_lab_t structure with L* (0-100), a* (-128 to 128), b* (-128 to 128), and alpha (0.0-1.0).
 * @discussion This function converts RGBA to CIELAB color space using the D65 white point. CIELAB is designed to be perceptually uniform, making it ideal for color difference calculations.
*/
color_lab_t rgba_to_lab(color_t rgba);

/*!
 * @function lab_to_rgba
 * @brief Converts CIELAB color space to RGBA.
 * @param lab The input CIELAB color.
 * @return A color_t value representing the equivalent RGBA color.
 * @discussion This function converts CIELAB color space back to RGBA using the D65 white point and sRGB color space.
*/
color_t lab_to_rgba(color_lab_t lab);

/*!
 * @function rgba_to_xyz
 * @brief Converts an RGBA color to CIEXYZ color space.
 * @param rgba The input RGBA color.
 * @return A color_xyz_t structure with X, Y, Z tristimulus values and alpha.
 * @discussion This function converts RGBA to CIEXYZ color space using the D65 white point. XYZ represents absolute color measurements in the CIE 1931 color space.
*/
color_xyz_t rgba_to_xyz(color_t rgba);

/*!
 * @function xyz_to_rgba
 * @brief Converts CIEXYZ color space to RGBA.
 * @param xyz The input CIEXYZ color.
 * @return A color_t value representing the equivalent RGBA color.
 * @discussion This function converts CIEXYZ color space back to RGBA using the D65 white point and sRGB color space.
*/
color_t xyz_to_rgba(color_xyz_t xyz);

/*!
 * @function lab_to_xyz
 * @brief Converts CIELAB to CIEXYZ color space.
 * @param lab The input CIELAB color.
 * @return A color_xyz_t structure with XYZ tristimulus values.
 * @discussion This function converts CIELAB to CIEXYZ using the D65 white point reference.
*/
color_xyz_t lab_to_xyz(color_lab_t lab);

/*!
 * @function xyz_to_lab
 * @brief Converts CIEXYZ to CIELAB color space.
 * @param xyz The input CIEXYZ color.
 * @return A color_lab_t structure with LAB components.
 * @discussion This function converts CIEXYZ to CIELAB using the D65 white point reference.
*/
color_lab_t xyz_to_lab(color_xyz_t xyz);

/*!
 * @function rgba_to_yuv
 * @brief Converts an RGBA color to YUV color space.
 * @param rgba The input RGBA color.
 * @return A color_yuv_t structure with Y (luma), U (blue-luma difference), V (red-luma difference), and alpha.
 * @discussion This function converts RGBA to YUV color space using the BT.601 standard. YUV separates luminance from chrominance information, commonly used in video encoding.
*/
color_yuv_t rgba_to_yuv(color_t rgba);

/*!
 * @function yuv_to_rgba
 * @brief Converts YUV color space to RGBA.
 * @param yuv The input YUV color.
 * @return A color_t value representing the equivalent RGBA color.
 * @discussion This function converts YUV color space back to RGBA using the BT.601 standard.
*/
color_t yuv_to_rgba(color_yuv_t yuv);

/*!
 * @function rgba_to_cmyk
 * @brief Converts an RGBA color to CMYK color space.
 * @param rgba The input RGBA color.
 * @return A color_cmyk_t structure with C (cyan), M (magenta), Y (yellow), K (black), and alpha.
 * @discussion This function converts RGBA to CMYK color space. CMYK is the standard color model used in printing, representing the amount of each ink needed.
*/
color_cmyk_t rgba_to_cmyk(color_t rgba);

/*!
 * @function cmyk_to_rgba
 * @brief Converts CMYK color space to RGBA.
 * @param cmyk The input CMYK color.
 * @return A color_t value representing the equivalent RGBA color.
 * @discussion This function converts CMYK color space back to RGBA.
*/
color_t cmyk_to_rgba(color_cmyk_t cmyk);

/*!
 * @function rgba_to_rgb565
 * @brief Converts an RGBA color to RGB565 format.
 * @param rgba The input RGBA color.
 * @return A color_rgb_t565 structure with packed RGB565 value and alpha.
 * @discussion This function converts RGBA to RGB565 format, which uses 5 bits for red, 6 bits for green, and 5 bits for blue. This format is commonly used in embedded systems and older displays.
*/
color_rgb_t565 rgba_to_rgb565(color_t rgba);

/*!
 * @function rgb565_to_rgba
 * @brief Converts RGB565 format to RGBA.
 * @param rgb565 The input RGB565 color.
 * @return A color_t value representing the equivalent RGBA color.
 * @discussion This function converts RGB565 format back to RGBA, expanding the 5-6-5 bit components back to 8-bit values.
*/
color_t rgb565_to_rgba(color_rgb_t565 rgb565);

/*!
 * @function color_cmp
 * @brief Compares two colors for exact equality.
 * @param a First color to compare.
 * @param b Second color to compare.
 * @return true if all RGBA components are identical, false otherwise.
 * @discussion This function performs a bitwise comparison of all color components including alpha. It returns true only if both colors are exactly identical.
*/
bool color_cmp(color_t a, color_t b);

/*!
 * @function color_distance_lab
 * @brief Calculates the Euclidean distance between two colors in CIELAB color space.
 * @param a First color in CIELAB space.
 * @param b Second color in CIELAB space.
 * @return The Euclidean distance in LAB space (Delta E CIE76).
 * @discussion This function computes the straight-line distance between two points in CIELAB color space. This is a simple but effective color difference metric, though not as perceptually accurate as CIEDE2000.
*/
float color_distance_lab(color_lab_t a, color_lab_t b);

/*!
 * @function color_distance
 * @brief Calculates the Euclidean distance between two colors in RGB space.
 * @param a First color.
 * @param b Second color.
 * @return The Euclidean distance in RGB space.
 * @discussion This function computes the straight-line distance between two colors in RGB color space. This is a simple metric that doesn't account for perceptual differences between colors.
*/
float color_distance(color_t a, color_t b);

/*!
 * @function color_lerp
 * @brief Linearly interpolates between two colors.
 * @param a Starting color.
 * @param b Ending color.
 * @param t Interpolation factor (0.0 = a, 1.0 = b).
 * @return The interpolated color.
 * @discussion This function performs linear interpolation between two colors in RGB space. The interpolation factor t is clamped to the range [0.0, 1.0]. Alpha is also interpolated.
*/
color_t color_lerp(color_t a, color_t b, float t);

// Luminance and brightness
/*!
 * @function color_luminance
 * @brief Calculates the perceptual luminance of a color.
 * @param color The input color.
 * @return The luminance value (0.0-1.0) using sRGB perceptual coefficients.
 * @discussion This function computes the perceived brightness of a color using the standard sRGB luminance formula. This is different from simple averaging and accounts for human visual perception where green appears brighter than red or blue.
*/
float color_luminance(color_t color);

/*!
 * @function color_relative_luminance
 * @brief Calculates the relative luminance for WCAG accessibility compliance.
 * @param color The input color.
 * @return The relative luminance value (0.0-1.0) with gamma correction applied.
 * @discussion This function computes relative luminance according to WCAG guidelines, applying gamma correction to sRGB values. This is used for calculating contrast ratios between colors for accessibility compliance.
*/
float color_relative_luminance(color_t color);

/*!
 * @function color_brightness
 * @brief Calculates the simple average brightness of a color.
 * @param color The input color.
 * @return The average brightness value (0.0-1.0).
 * @discussion This function computes brightness as the simple average of RGB components. This is a basic metric that doesn't account for perceptual differences between color channels.
*/
float color_brightness(color_t color);

/*!
 * @function color_is_dark
 * @brief Determines if a color is considered dark.
 * @param color The input color.
 * @return 1 if the color is dark (luminance < 0.5), 0 if light.
 * @discussion This function uses perceptual luminance to determine if a color appears dark. Colors with luminance below 0.5 are considered dark.
*/
int color_is_dark(color_t color);

// Color properties
/*!
 * @function color_saturation
 * @brief Gets the saturation level of a color.
 * @param color The input color.
 * @return The saturation value (0.0-1.0) in HSV color space.
 * @discussion This function converts the color to HSV space and returns the saturation component, which represents color purity or intensity.
*/
float color_saturation(color_t color);

/*!
 * @function color_hue
 * @brief Gets the hue of a color in degrees.
 * @param color The input color.
 * @return The hue angle in degrees (0.0-360.0).
 * @discussion This function converts the color to HSV space and returns the hue as an angle in degrees, where 0° is red, 120° is green, and 240° is blue.
*/
float color_hue(color_t color);

/*!
 * @function color_grayscale
 * @brief Converts a color to grayscale.
 * @param color The input color.
 * @return A grayscale version of the input color.
 * @discussion This function converts the color to grayscale using perceptual luminance coefficients, preserving the alpha channel.
*/
color_t color_grayscale(color_t color);

/*!
 * @function color_invert
 * @brief Inverts the RGB channels of a color.
 * @param color The input color.
 * @return The color with inverted RGB values.
 * @discussion This function inverts each RGB channel (255 - value) while preserving the alpha channel. This creates the photographic negative of the color.
*/
color_t color_invert(color_t color);

/*!
 * @function color_complement
 * @brief Gets the complementary color (opposite hue).
 * @param color The input color.
 * @return The complementary color.
 * @discussion This function shifts the hue by 180° in HSV color space to find the complementary color, which provides maximum contrast.
*/
color_t color_complement(color_t color);

// Additional analysis functions
/*!
 * @function color_dominant_channel
 * @brief Determines the dominant color channel.
 * @param color The input color.
 * @return 0 for red-dominant, 1 for green-dominant, 2 for blue-dominant.
 * @discussion This function compares RGB channel values to determine which color channel has the highest intensity.
*/
int color_dominant_channel(color_t color);

/*!
 * @function color_is_grayscale
 * @brief Checks if a color is effectively grayscale.
 * @param color The input color.
 * @return 1 if the color is grayscale, 0 otherwise.
 * @discussion This function checks if all RGB channels are within 2 units of each other, indicating the color has no significant hue.
*/
int color_is_grayscale(color_t color);

/*!
 * @function color_temperature_estimate
 * @brief Estimates the color temperature in Kelvin.
 * @param color The input color.
 * @return Estimated color temperature (1000K-10000K).
 * @discussion This function provides a rough approximation of color temperature based on the blue-to-red ratio, where higher blue content indicates cooler (higher) temperatures.
*/
float color_temperature_estimate(color_t color);

/*!
 * @function color_is_warm
 * @brief Determines if a color is warm (reddish/yellowish).
 * @param color The input color.
 * @return 1 if warm, 0 if cool.
 * @discussion This function considers a color warm if red dominates and the red+green sum is significantly higher than blue.
*/
int color_is_warm(color_t color);

/*!
 * @function color_is_cool
 * @brief Determines if a color is cool (bluish/greenish).
 * @param color The input color.
 * @return 1 if cool, 0 if warm.
 * @discussion This function considers a color cool if blue dominates and the blue+green sum is significantly higher than red.
*/
int color_is_cool(color_t color);

/*!
 * @function color_purity
 * @brief Calculates the color purity (saturation).
 * @param color The input color.
 * @return Color purity value (0.0-1.0).
 * @discussion This function measures how far the color is from the grayscale axis in RGB space, indicating color intensity or vividness.
*/
float color_purity(color_t color);

/*!
 * @function color_energy
 * @brief Calculates the total energy of a color.
 * @param color The input color.
 * @return Color energy value (0.0-1.0).
 * @discussion This function computes the average of all RGB channels, representing the overall intensity of the color.
*/
float color_energy(color_t color);

// Brightness and contrast
/*!
 * @function color_adjust_brightness
 * @brief Adjusts the brightness of a color.
 * @param color The input color.
 * @param amount Brightness adjustment amount (-1.0 to 1.0, where 0 = no change).
 * @return The color with adjusted brightness.
 * @discussion This function adds the specified amount to each RGB channel, effectively making the color lighter (positive values) or darker (negative values).
*/
color_t color_adjust_brightness(color_t color, float amount);

/*!
 * @function color_adjust_contrast
 * @brief Adjusts the contrast of a color.
 * @param color The input color.
 * @param amount Contrast adjustment amount (-1.0 to 1.0, where 0 = no change).
 * @return The color with adjusted contrast.
 * @discussion This function applies a contrast adjustment by scaling RGB values around the midpoint (0.5), making colors more vivid (positive values) or more muted (negative values).
*/
color_t color_adjust_contrast(color_t color, float amount);

/*!
 * @function color_adjust_gamma
 * @brief Applies gamma correction to a color.
 * @param color The input color.
 * @param gamma Gamma correction value (must be > 0).
 * @return The color with gamma correction applied.
 * @discussion This function applies gamma correction using the formula: output = input^(1/gamma). Values > 1.0 make the image darker, values < 1.0 make it lighter.
*/
color_t color_adjust_gamma(color_t color, float gamma);

// Saturation and hue
/*!
 * @function color_saturate
 * @brief Increases the saturation of a color.
 * @param color The input color.
 * @param amount Saturation multiplier (0.0 to 2.0+, where 1.0 = no change).
 * @return The color with increased saturation.
 * @discussion This function multiplies the saturation component in HSV color space by the specified amount, making colors more vivid.
*/
color_t color_saturate(color_t color, float amount);

/*!
 * @function color_desaturate
 * @brief Decreases the saturation of a color.
 * @param color The input color.
 * @param amount Saturation reduction factor (0.0 to 1.0, where 0.0 = grayscale, 1.0 = no change).
 * @return The color with reduced saturation.
 * @discussion This function scales down the saturation component in HSV color space, moving colors toward grayscale.
*/
color_t color_desaturate(color_t color, float amount);

/*!
 * @function color_hue_shift
 * @brief Shifts the hue of a color by a specified number of degrees.
 * @param color The input color.
 * @param degrees Degrees to shift the hue (-360 to 360).
 * @return The color with shifted hue.
 * @discussion This function rotates the hue component in HSV color space by the specified number of degrees, cycling through the color wheel.
*/
color_t color_hue_shift(color_t color, float degrees);

// Temperature and tint
/*!
 * @function color_adjust_temperature
 * @brief Adjusts the color temperature of a color.
 * @param color The input color.
 * @param kelvin Color temperature in Kelvin (1000-40000K, 6500K = daylight).
 * @return The color with adjusted temperature.
 * @discussion This function simulates color temperature changes by blending the color with the RGB equivalent of the specified blackbody temperature.
*/
color_t color_adjust_temperature(color_t color, float kelvin);

/*!
 * @function color_tint
 * @brief Applies a tint adjustment to a color.
 * @param color The input color.
 * @param amount Tint amount (-1.0 to 1.0).
 * @return The color with applied tint.
 * @discussion This function adjusts the magenta-green balance, adding magenta (positive values) or green (negative values) to the color.
*/
color_t color_tint(color_t color, float amount);

// Additional adjustments
/*!
 * @function color_adjust_exposure
 * @brief Adjusts the exposure of a color in stops.
 * @param color The input color.
 * @param stops Exposure adjustment in stops (-3.0 to 3.0, where 0 = no change).
 * @return The color with adjusted exposure.
 * @discussion This function multiplies RGB values by 2^stops, simulating camera exposure changes. Each stop doubles or halves the brightness.
*/
color_t color_adjust_exposure(color_t color, float stops);

/*!
 * @function color_adjust_highlights
 * @brief Adjusts highlight areas of a color.
 * @param color The input color.
 * @param amount Highlight adjustment amount (-1.0 to 1.0).
 * @return The color with adjusted highlights.
 * @discussion This function selectively adjusts pixels with luminance above 50%, making bright areas brighter (positive values) or darker (negative values).
*/
color_t color_adjust_highlights(color_t color, float amount);

/*!
 * @function color_adjust_shadows
 * @brief Adjusts shadow areas of a color.
 * @param color The input color.
 * @param amount Shadow adjustment amount (-1.0 to 1.0).
 * @return The color with adjusted shadows.
 * @discussion This function selectively adjusts pixels with luminance below 50%, making dark areas brighter (positive values) or darker (negative values).
*/
color_t color_adjust_shadows(color_t color, float amount);

/*!
 * @function color_adjust_whites
 * @brief Adjusts very bright areas of a color.
 * @param color The input color.
 * @param amount White adjustment amount (-1.0 to 1.0).
 * @return The color with adjusted whites.
 * @discussion This function selectively adjusts pixels with luminance above 80%, affecting only the brightest parts of the image.
*/
color_t color_adjust_whites(color_t color, float amount);

/*!
 * @function color_adjust_blacks
 * @brief Adjusts very dark areas of a color.
 * @param color The input color.
 * @param amount Black adjustment amount (-1.0 to 1.0).
 * @return The color with adjusted blacks.
 * @discussion This function selectively adjusts pixels with luminance below 20%, affecting only the darkest parts of the image.
*/
color_t color_adjust_blacks(color_t color, float amount);

/*!
 * @function color_adjust_clarity
 * @brief Enhances local contrast (clarity/structure).
 * @param color The input color.
 * @param amount Clarity adjustment amount (-1.0 to 1.0).
 * @return The color with enhanced clarity.
 * @discussion This function boosts contrast in mid-tone areas, simulating the clarity/structure adjustment found in photo editing software.
*/
color_t color_adjust_clarity(color_t color, float amount);

/*!
 * @function color_adjust_vibrance
 * @brief Applies smart saturation adjustment.
 * @param color The input color.
 * @param amount Vibrance adjustment amount (-1.0 to 1.0).
 * @return The color with adjusted vibrance.
 * @discussion This function intelligently adjusts saturation, applying more effect to less saturated colors while protecting skin tones and already vivid colors.
*/
color_t color_adjust_vibrance(color_t color, float amount);

// Blending modes
/*!
 * @function color_multiply
 * @brief Multiplies two colors together.
 * @param a First color (base layer).
 * @param b Second color (blend layer).
 * @return The blended color result.
 * @discussion This function multiplies the RGB channels of the two colors, creating a darker result. Multiply mode is commonly used for shadows and darkening effects.
*/
color_t color_multiply(color_t a, color_t b);

/*!
 * @function color_screen
 * @brief Screens two colors together.
 * @param a First color (base layer).
 * @param b Second color (blend layer).
 * @return The blended color result.
 * @discussion This function inverts both colors, multiplies them, then inverts the result, creating a lighter effect. Screen mode is commonly used for highlights and lightening effects.
*/
color_t color_screen(color_t a, color_t b);

/*!
 * @function color_overlay
 * @brief Applies overlay blending mode.
 * @param a First color (base layer).
 * @param b Second color (blend layer).
 * @return The blended color result.
 * @discussion This function combines multiply and screen modes: for each channel, if the base is < 128 it multiplies, otherwise it screens. Overlay enhances contrast and saturation.
*/
color_t color_overlay(color_t a, color_t b);

/*!
 * @function color_soft_light
 * @brief Applies soft light blending mode.
 * @param a First color (base layer).
 * @param b Second color (blend layer).
 * @return The blended color result.
 * @discussion This function simulates the effect of shining a diffused spotlight on the base color. It creates a softer, more subtle lightening/darkening effect than hard light.
*/
color_t color_soft_light(color_t a, color_t b);

/*!
 * @function color_hard_light
 * @brief Applies hard light blending mode.
 * @param a First color (base layer).
 * @param b Second color (blend layer).
 * @return The blended color result.
 * @discussion This function is the inverse of overlay: if the blend color is < 128 it multiplies, otherwise it screens. Hard light creates more dramatic lightening/darkening effects.
*/
color_t color_hard_light(color_t a, color_t b);

/*!
 * @function color_color_dodge
 * @brief Applies color dodge blending mode.
 * @param a First color (base layer).
 * @param b Second color (blend layer).
 * @return The blended color result.
 * @discussion This function brightens the base color based on the blend color. The brighter the blend color, the more the base color is lightened. Pure white blend produces no change.
*/
color_t color_color_dodge(color_t a, color_t b);

/*!
 * @function color_color_burn
 * @brief Applies color burn blending mode.
 * @param a First color (base layer).
 * @param b Second color (blend layer).
 * @return The blended color result.
 * @discussion This function darkens the base color based on the blend color. The darker the blend color, the more the base color is darkened. Pure black blend produces no change.
*/
color_t color_color_burn(color_t a, color_t b);

/*!
 * @function color_darken
 * @brief Selects the darker of two colors for each channel.
 * @param a First color.
 * @param b Second color.
 * @return Color with minimum values from each channel.
 * @discussion This function compares corresponding channels and selects the darker (lower) value for each. Alpha is blended using standard alpha blending rules.
*/
color_t color_darken(color_t a, color_t b);

/*!
 * @function color_lighten
 * @brief Selects the lighter of two colors for each channel.
 * @param a First color.
 * @param b Second color.
 * @return Color with maximum values from each channel.
 * @discussion This function compares corresponding channels and selects the lighter (higher) value for each. Alpha is blended using standard alpha blending rules.
*/
color_t color_lighten(color_t a, color_t b);

/*!
 * @function color_difference
 * @brief Calculates the absolute difference between two colors.
 * @param a First color.
 * @param b Second color.
 * @return Color representing the absolute difference.
 * @discussion This function subtracts the darker color from the lighter color for each channel, creating high-contrast results often used for special effects.
*/
color_t color_difference(color_t a, color_t b);

/*!
 * @function color_exclusion
 * @brief Applies exclusion blending mode.
 * @param a First color (base layer).
 * @param b Second color (blend layer).
 * @return The blended color result.
 * @discussion This function is similar to difference mode but with lower contrast. It produces a result similar to the base color with the blend color's complementary colors subtracted.
*/
color_t color_exclusion(color_t a, color_t b);

// Alpha blending
/*!
 * @function color_alpha_blend
 * @brief Performs standard alpha blending (Porter-Duff "over" operation).
 * @param fg Foreground color (source).
 * @param bg Background color (destination).
 * @return The alpha-blended result.
 * @discussion This function composites the foreground color over the background color using standard alpha blending equations, properly handling premultiplied alpha.
*/
color_t color_alpha_blend(color_t fg, color_t bg);

/*!
 * @function color_premultiply_alpha
 * @brief Premultiplies RGB channels by alpha.
 * @param color The input color.
 * @return Color with RGB channels premultiplied by alpha.
 * @discussion This function multiplies each RGB channel by the alpha value, preparing the color for use in blending operations that expect premultiplied alpha.
*/
color_t color_premultiply_alpha(color_t color);

/*!
 * @function color_unpremultiply_alpha
 * @brief Unpremultiplies RGB channels by alpha.
 * @param color The input color.
 * @return Color with RGB channels unpremultiplied by alpha.
 * @discussion This function divides each RGB channel by the alpha value, converting from premultiplied alpha format back to straight alpha format.
*/
color_t color_unpremultiply_alpha(color_t color);

// Color harmony
/*!
 * @function color_analogous
 * @brief Generates analogous colors (adjacent hues on the color wheel).
 * @param base The base color to generate variations from.
 * @param colors Pointer to array where generated colors will be stored.
 * @param count Number of analogous colors to generate.
 * @discussion This function creates colors that are adjacent to the base color on the color wheel, typically within ±30° of the base hue. Analogous color schemes are harmonious and pleasing to the eye.
*/
void color_analogous(color_t base, color_t* colors, int count);                       // Adjacent hues

/*!
 * @function color_triadic
 * @brief Generates triadic colors (120° apart on the color wheel).
 * @param base The base color to generate variations from.
 * @param color1 Pointer to store the first triadic color.
 * @param color2 Pointer to store the second triadic color.
 * @discussion This function creates two colors that are 120° apart from the base color on the color wheel. Triadic color schemes provide vibrant contrast while maintaining harmony.
*/
void color_triadic(color_t base, color_t* color1, color_t* color2);                   // 120° apart

/*!
 * @function color_tetradic
 * @brief Generates tetradic colors (rectangle scheme on the color wheel).
 * @param base The base color to generate variations from.
 * @param color1 Pointer to store the first tetradic color.
 * @param color2 Pointer to store the second tetradic color.
 * @param color3 Pointer to store the third tetradic color.
 * @discussion This function creates three colors that form a rectangle on the color wheel (90° apart). Tetradic color schemes offer rich color variety while maintaining balance.
*/
void color_tetradic(color_t base, color_t* color1, color_t* color2, color_t* color3); // Rectangle scheme

/*!
 * @function color_split_complementary
 * @brief Generates split-complementary colors.
 * @param base The base color to generate variations from.
 * @param color1 Pointer to store the first split-complementary color.
 * @param color2 Pointer to store the second split-complementary color.
 * @discussion This function creates colors using the base color and two colors adjacent to its complement. This scheme provides high contrast while maintaining harmony.
*/
void color_split_complementary(color_t base, color_t* color1, color_t* color2);       // Split complement

/*!
 * @function color_monochromatic
 * @brief Generates monochromatic colors (same hue, varying saturation/value).
 * @param base The base color to generate variations from.
 * @param colors Pointer to array where generated colors will be stored.
 * @param count Number of monochromatic colors to generate.
 * @discussion This function creates colors with the same hue as the base color but varying saturation and brightness levels. Monochromatic schemes are elegant and sophisticated.
*/
void color_monochromatic(color_t base, color_t* colors, int count);                   // Same hue, different lightness

// Gradient generation
/*!
 * @function color_gradient
 * @brief Generates a linear gradient between two colors.
 * @param start The starting color of the gradient.
 * @param end The ending color of the gradient.
 * @param colors Pointer to array where gradient colors will be stored.
 * @param count Number of colors to generate in the gradient.
 * @discussion This function creates a smooth transition of colors from start to end, with the specified number of intermediate steps. Useful for creating color ramps and smooth color transitions.
*/
void color_gradient(color_t start, color_t end, color_t* colors, int count); // 1D gradient

// Color space conversions with custom white points
/*!
 * @function rgba_to_xyz_custom
 * @brief Converts an RGBA color to CIEXYZ color space using a custom white point.
 * @param rgba The input RGBA color.
 * @param wx The X component of the custom white point.
 * @param wy The Y component of the custom white point.
 * @param wz The Z component of the custom white point.
 * @return A color_xyz_t structure with XYZ tristimulus values and alpha.
 * @discussion This function converts RGBA to CIEXYZ color space using the specified custom white point instead of the standard D65 illuminant. This allows for color space conversions under different lighting conditions or for specific display characteristics.
*/
color_xyz_t rgba_to_xyz_custom(color_t rgba, float wx, float wy, float wz);

/*!
 * @function rgba_to_lab_custom
 * @brief Converts an RGBA color to CIELAB color space using a custom white point.
 * @param rgba The input RGBA color.
 * @param wx The X component of the custom white point.
 * @param wy The Y component of the custom white point.
 * @param wz The Z component of the custom white point.
 * @return A color_lab_t structure with L*, a*, b* components and alpha.
 * @discussion This function converts RGBA to CIELAB color space using the specified custom white point. CIELAB is designed to be perceptually uniform, making it ideal for color difference calculations under specific lighting conditions.
*/
color_lab_t rgba_to_lab_custom(color_t rgba, float wx, float wy, float wz);

// Delta E calculations (color difference)
/*!
 * @function color_delta_e_76
 * @brief Calculates the color difference using the CIE76 formula (Delta E CIE76).
 * @param a First color in CIELAB space.
 * @param b Second color in CIELAB space.
 * @return The Euclidean distance in CIELAB space (Delta E CIE76).
 * @discussion This function computes the straight-line Euclidean distance between two colors in CIELAB color space. This is a simple but effective color difference metric, though not as perceptually accurate as CIEDE2000.
*/
float color_delta_e_76(color_lab_t a, color_lab_t b);     // CIE76 formula

/*!
 * @function color_delta_e_94
 * @brief Calculates the color difference using the CIE94 formula (Delta E CIE94).
 * @param a First color in CIELAB space.
 * @param b Second color in CIELAB space.
 * @return The color difference value using CIE94 weighting (Delta E CIE94).
 * @discussion This function computes color difference using the CIE94 formula, which applies different weighting factors to lightness, chroma, and hue differences. It provides better perceptual accuracy than CIE76, especially for small color differences.
*/
float color_delta_e_94(color_lab_t a, color_lab_t b);     // CIE94 formula

/*!
 * @function color_delta_e_2000
 * @brief Calculates the color difference using the CIEDE2000 formula (Delta E CIEDE2000).
 * @param a First color in CIELAB space.
 * @param b Second color in CIELAB space.
 * @return The color difference value using CIEDE2000 weighting (Delta E CIEDE2000).
 * @discussion This function computes color difference using the CIEDE2000 formula, which is the most perceptually accurate color difference metric currently available. It accounts for perceptual non-uniformities in CIELAB space and provides excellent correlation with visual judgments.
*/
float color_delta_e_2000(color_lab_t a, color_lab_t b);   // CIEDE2000 formula

// Levels adjustment
/*!
 * @function color_levels
 * @brief Applies levels adjustment to a color (black point, white point, gamma).
 * @param color The input color to adjust.
 * @param black_point The black point value (0.0-1.0, where 0 = no change).
 * @param white_point The white point value (0.0-1.0, where 1 = no change).
 * @param gamma The gamma correction value (must be > 0).
 * @return The color with levels adjustment applied.
 * @discussion This function applies a levels adjustment similar to photo editing software. The black point remaps dark tones, the white point remaps bright tones, and gamma adjusts the midtones. Values are clamped to prevent clipping.
*/
color_t color_levels(color_t color, float black_point, float white_point, float gamma);

/*!
 * @function color_curves
 * @brief Applies curves adjustment to a color using lookup tables.
 * @param color The input color to adjust.
 * @param curve_r Pointer to a 256-element array defining the red channel curve (0.0-1.0 values).
 * @param curve_g Pointer to a 256-element array defining the green channel curve (0.0-1.0 values).
 * @param curve_b Pointer to a 256-element array defining the blue channel curve (0.0-1.0 values).
 * @return The color with curves adjustment applied.
 * @discussion This function applies tone curves to each RGB channel independently using lookup tables. Each curve array should contain 256 float values mapping input levels (0-255) to output levels (0.0-1.0). This provides precise control over tonal adjustments.
*/
color_t color_curves(color_t color, float* curve_r, float* curve_g, float* curve_b);

// Color balance
/*!
 * @function color_shadow_highlight
 * @brief Adjusts shadow and highlight regions of a color.
 * @param color The input color to adjust.
 * @param shadow Shadow adjustment amount (-1.0 to 1.0).
 * @param highlight Highlight adjustment amount (-1.0 to 1.0).
 * @return The color with shadow/highlight adjustment applied.
 * @discussion This function selectively adjusts shadow (dark) and highlight (bright) regions based on luminance. Positive values brighten the respective regions, negative values darken them. The adjustment strength varies with luminance level.
*/
color_t color_shadow_highlight(color_t color, float shadow, float highlight);

/*!
 * @function color_color_balance
 * @brief Applies color balance adjustment to a color.
 * @param color The input color to adjust.
 * @param cyan_red Cyan/red balance adjustment (-1.0 to 1.0).
 * @param magenta_green Magenta/green balance adjustment (-1.0 to 1.0).
 * @param yellow_blue Yellow/blue balance adjustment (-1.0 to 1.0).
 * @return The color with color balance adjustment applied.
 * @discussion This function adjusts the color balance by adding or subtracting from the RGB channels. Positive cyan_red values add cyan (reduce red), negative values add red. Similar logic applies to the other color pairs, allowing fine control over color temperature and tint.
*/
color_t color_color_balance(color_t color, float cyan_red, float magenta_green, float yellow_blue);

// Vibrance and saturation
/*!
 * @function color_vibrance
 * @brief Applies vibrance adjustment (smart saturation) to a color.
 * @param color The input color to adjust.
 * @param amount Vibrance adjustment amount (-1.0 to 1.0).
 * @return The color with vibrance adjustment applied.
 * @discussion This function applies intelligent saturation adjustment that affects less saturated colors more than already vivid colors. Positive values increase saturation, negative values decrease it. This helps avoid oversaturation of already colorful areas.
*/
color_t color_vibrance(color_t color, float amount);      // Smart saturation

/*!
 * @function color_selective_color
 * @brief Applies selective color adjustment to specific color ranges.
 * @param color The input color to adjust.
 * @param channel The color channel to adjust (0=reds, 1=yellows, 2=greens, 3=cyans, 4=blues, 5=magentas).
 * @param cyan Cyan adjustment amount (-1.0 to 1.0).
 * @param magenta Magenta adjustment amount (-1.0 to 1.0).
 * @param yellow Yellow adjustment amount (-1.0 to 1.0).
 * @param black Black adjustment amount (-1.0 to 1.0).
 * @return The color with selective color adjustment applied.
 * @discussion This function adjusts specific color ranges in CMY color space. The channel parameter determines which colors are affected based on their dominant CMY components. This allows precise color corrections similar to professional photo editing software.
*/
color_t color_selective_color(color_t color, int channel, float cyan, float magenta, float yellow, float black);

// Quantization
/*!
 * @function color_quantize
 * @brief Quantizes a color to reduce the number of bits per channel.
 * @param color The input color to quantize.
 * @param bits_per_channel The number of bits to use per channel (1-8).
 * @return The quantized color.
 * @discussion This function reduces color precision by limiting each RGB channel to the specified number of bits. This creates a posterized effect and can be used for retro graphics, dithering preparation, or reducing color palette size.
*/
color_t color_quantize(color_t color, int bits_per_channel);

/*!
 * @function color_posterize
 * @brief Applies posterization effect by reducing the number of tonal levels.
 * @param color The input color to posterize.
 * @param levels The number of tonal levels per channel (2-256).
 * @return The posterized color.
 * @discussion This function reduces the number of available brightness levels per channel, creating a poster-like effect with distinct tonal bands. Lower levels values produce more dramatic posterization effects.
*/
color_t color_posterize(color_t color, int levels);

// Dithering
/*!
 * @function color_dither_floyd_steinberg
 * @brief Applies Floyd-Steinberg dithering to quantize a color against a palette.
 * @param color The input color to dither.
 * @param palette Pointer to an array of available colors.
 * @param palette_size The number of colors in the palette.
 * @param x The x-coordinate of the pixel (used for dithering pattern).
 * @param y The y-coordinate of the pixel (used for dithering pattern).
 * @return The dithered color from the palette.
 * @discussion This function implements the classic Floyd-Steinberg error diffusion algorithm. It finds the closest color in the palette and distributes the quantization error to neighboring pixels. The x,y coordinates are used to simulate the error diffusion pattern.
*/
color_t color_dither_floyd_steinberg(color_t color, color_t* palette, int palette_size, int x, int y);

/*!
 * @function color_dither_ordered
 * @brief Applies ordered dithering to quantize a color against a palette.
 * @param color The input color to dither.
 * @param palette Pointer to an array of available colors.
 * @param palette_size The number of colors in the palette.
 * @param x The x-coordinate of the pixel (used for dithering pattern).
 * @param y The y-coordinate of the pixel (used for dithering pattern).
 * @return The dithered color from the palette.
 * @discussion This function implements ordered dithering using a Bayer matrix pattern. It compares the color against a threshold matrix to determine which palette color to use. This creates a regular dithering pattern that works well for textures and gradients.
*/
color_t color_dither_ordered(color_t color, color_t* palette, int palette_size, int x, int y);

// Color blindness simulation
/*!
 * @function color_protanopia
 * @brief Simulates protanopia (red-blind) color vision deficiency.
 * @param color The input color to simulate.
 * @return The color as seen by someone with protanopia.
 * @discussion This function simulates red-blind color vision by applying the appropriate color transformation matrix. Protanopia affects the red color channel, making reds appear darker and causing confusion between red and green hues.
*/
color_t color_protanopia(color_t color);      // Red-blind

/*!
 * @function color_deuteranopia
 * @brief Simulates deuteranopia (green-blind) color vision deficiency.
 * @param color The input color to simulate.
 * @return The color as seen by someone with deuteranopia.
 * @discussion This function simulates green-blind color vision by applying the appropriate color transformation matrix. Deuteranopia affects the green color channel and is the most common form of color blindness.
*/
color_t color_deuteranopia(color_t color);    // Green-blind

/*!
 * @function color_tritanopia
 * @brief Simulates tritanopia (blue-blind) color vision deficiency.
 * @param color The input color to simulate.
 * @return The color as seen by someone with tritanopia.
 * @discussion This function simulates blue-blind color vision by applying the appropriate color transformation matrix. Tritanopia affects the blue color channel and is relatively rare.
*/
color_t color_tritanopia(color_t color);      // Blue-blind

/*!
 * @function color_achromatopsia
 * @brief Simulates achromatopsia (complete color blindness).
 * @param color The input color to simulate.
 * @return The color as seen by someone with achromatopsia.
 * @discussion This function simulates complete color blindness by converting the color to grayscale using luminance coefficients. Achromatopsia results in monochromatic vision with only brightness information.
*/
color_t color_achromatopsia(color_t color);   // Complete color blindness

// Accessibility
/*!
 * @function color_contrast_ratio
 * @brief Calculates the WCAG contrast ratio between two colors.
 * @param a First color.
 * @param b Second color.
 * @return The contrast ratio (1.0 to 21.0+).
 * @discussion This function calculates the contrast ratio according to WCAG guidelines using relative luminance. A ratio of 1.0 means no contrast (same color), while higher ratios indicate better contrast. Ratios of 4.5:1 or 7:1 are required for AA/AAA compliance respectively.
*/
float color_contrast_ratio(color_t a, color_t b);          // WCAG contrast ratio

/*!
 * @function color_wcag_aa_compliant
 * @brief Checks if two colors meet WCAG AA contrast requirements.
 * @param fg Foreground color.
 * @param bg Background color.
 * @return 1 if compliant with WCAG AA standards, 0 otherwise.
 * @discussion This function checks if the contrast ratio between foreground and background colors meets WCAG AA requirements (4.5:1 for normal text, 3:1 for large text). Returns 1 if compliant, 0 if not.
*/
int color_wcag_aa_compliant(color_t fg, color_t bg);       // AA compliance

/*!
 * @function color_wcag_aaa_compliant
 * @brief Checks if two colors meet WCAG AAA contrast requirements.
 * @param fg Foreground color.
 * @param bg Background color.
 * @return 1 if compliant with WCAG AAA standards, 0 otherwise.
 * @discussion This function checks if the contrast ratio between foreground and background colors meets WCAG AAA requirements (7:1 for normal text, 4.5:1 for large text). Returns 1 if compliant, 0 if not.
*/
int color_wcag_aaa_compliant(color_t fg, color_t bg);      // AAA compliance

// Color matching
/*!
 * @function color_match_closest
 * @brief Finds the closest color in a palette to the target color.
 * @param target The target color to match.
 * @param palette Pointer to an array of colors to search.
 * @param palette_size The number of colors in the palette.
 * @return The closest matching color from the palette.
 * @discussion This function searches through the color palette and returns the color with the smallest Euclidean distance in RGB space to the target color. Useful for color quantization and palette-based rendering.
*/
color_t color_match_closest(color_t target, color_t* palette, int palette_size);

// Color comparison
/*!
 * @function color_similarity
 * @brief Calculates the similarity between two colors (0.0-1.0).
 * @param a First color to compare.
 * @param b Second color to compare.
 * @return Similarity value where 1.0 means identical, 0.0 means completely different.
 * @discussion This function calculates color similarity based on Euclidean distance in RGB space, normalized to a 0.0-1.0 range. Higher values indicate more similar colors.
*/
float color_similarity(color_t a, color_t b);

/*!
 * @function color_is_similar
 * @brief Checks if two colors are similar within a threshold.
 * @param a First color to compare.
 * @param b Second color to compare.
 * @param threshold Similarity threshold (0.0-1.0, where 1.0 = identical).
 * @return 1 if colors are similar within the threshold, 0 otherwise.
 * @discussion This function compares two colors and returns whether they are similar enough based on the given threshold. A threshold of 0.95 would consider colors very close, while 0.5 would be more lenient.
*/
int color_is_similar(color_t a, color_t b, float threshold);

// Color grading
/*!
 * @function color_lift_gamma_gain
 * @brief Applies lift-gamma-gain color grading to a color.
 * @discussion This function implements the classic lift-gamma-gain color grading technique commonly used in film and video post-production. Lift affects shadows and blacks, gamma affects midtones, and gain affects highlights and whites. Each parameter is a color_rgbaf_t struct where values represent the adjustment strength for each RGB channel.
 * @param color The input color to grade.
 * @param lift Color adjustment for shadows/blacks (additive effect in dark areas).
 * @param gamma Gamma correction for midtones (power function applied to mid-range values).
 * @param gain Color adjustment for highlights/whites (multiplicative effect in bright areas).
 * @return The color graded result.
*/
color_t color_lift_gamma_gain(color_t color, color_rgbaf_t lift, color_rgbaf_t gamma, color_rgbaf_t gain);

/*!
 * @function color_shadow_midtone_highlight
 * @brief Applies shadow-midtone-highlight color grading using luminance-based weighting.
 * @discussion This function provides an alternative color grading approach that uses the image's luminance to determine how much each correction affects different tonal ranges. Shadows are weighted toward dark areas, midtones follow a bell curve, and highlights are weighted toward bright areas.
 * @param color The input color to grade.
 * @param shadow Color adjustment applied primarily to shadow/dark areas.
 * @param midtone Color adjustment applied primarily to midtone areas.
 * @param highlight Color adjustment applied primarily to highlight/bright areas.
 * @return The color graded result.
*/
color_t color_shadow_midtone_highlight(color_t color, color_rgbaf_t shadow, color_rgbaf_t midtone, color_rgbaf_t highlight);

// Color spaces for specific industries
/*!
 * @function color_rec709_to_rec2020
 * @brief Converts Rec.709 (standard HD) color space to Rec.2020 (ultra HD/HDR).
 * @discussion This function converts colors from the Rec.709 color space (used in standard HD television and video) to the Rec.2020 color space (used in ultra HD and HDR content). Rec.2020 has a wider color gamut and is designed for high dynamic range applications.
 * @param color The input color in Rec.709 color space.
 * @return The color converted to Rec.2020 color space.
*/
color_t color_rec709_to_rec2020(color_t color);    // HDR conversion

/*!
 * @function color_prophoto_to_srgb
 * @brief Converts ProPhoto RGB color space to sRGB.
 * @discussion This function converts colors from the ProPhoto RGB color space (commonly used in professional photography due to its wide color gamut) to the standard sRGB color space used for most displays and web content.
 * @param color The input color in ProPhoto RGB color space.
 * @return The color converted to sRGB color space.
*/
color_t color_prophoto_to_srgb(color_t color);     // Photography

/*!
 * @function color_adobe_rgb_to_srgb
 * @brief Converts Adobe RGB color space to sRGB.
 * @discussion This function converts colors from the Adobe RGB color space (designed for print workflows with a wider gamut than sRGB) to the standard sRGB color space used for most displays and web content.
 * @param color The input color in Adobe RGB color space.
 * @return The color converted to sRGB color space.
*/
color_t color_adobe_rgb_to_srgb(color_t color);    // Print/web

// Fast approximations
/*!
 * @function color_fast_grayscale
 * @brief Converts a color to grayscale using fast integer-only arithmetic.
 * @discussion This function provides a high-performance grayscale conversion that avoids floating-point operations. It uses integer arithmetic to convert RGB values to grayscale while preserving the alpha channel.
 * @param color The input color to convert.
 * @return The grayscale version of the input color.
*/
color_t color_fast_grayscale(color_t color);       // Integer-only grayscale

/*!
 * @function color_fast_sepia
 * @brief Applies a sepia tone effect using fast integer arithmetic.
 * @discussion This function creates a sepia-toned version of the input color using optimized integer calculations. Sepia toning gives images a warm, antique appearance reminiscent of old photographs.
 * @param color The input color to apply sepia toning to.
 * @return The sepia-toned version of the input color.
*/
color_t color_fast_sepia(color_t color);           // Fast sepia tone

/*!
 * @function color_fast_invert
 * @brief Inverts RGB channels using fast bitwise operations.
 * @discussion This function creates a photographic negative by inverting the RGB channels using bitwise operations. This is faster than arithmetic inversion and preserves the alpha channel.
 * @param color The input color to invert.
 * @return The inverted version of the input color.
*/
color_t color_fast_invert(color_t color);          // Bitwise invert

#ifdef __cplusplus
}
#endif
#endif // PAUL_COLOR_H

#if defined(PAUL_COLOR_IMPLEMENTATION) || defined(PAUL_IMPLEMENTATION)
#define _RGBA(R, G, B, A) (((unsigned int)(R) << 24) | ((unsigned int)(B) << 16) | ((unsigned int)(G) << 8) | (A))
#define _MIN(A, B) ((A) < (B) ? (A) : (B))
#define _MAX(A, B) ((A) > (B) ? (A) : (B))
#define _CLAMP(x, low, high) _MIN(_MAX(x, low), high)
#define _CLAMP_UINT8(V) ((uint8_t)_CLAMP((V), 0, 255))
#define _CLAMP_FLOAT(V) ((float)_CLAMP((V), 0.0f, 1.0f))
#define _CLAMP_FLOAT_RANGE(V, _MINV, _MAXV) (fminf(fmaxf(V, _MINV), _MAXV))
#define _FMIN3(A, B, C) (fminf(fminf((A), (B)), (C)))
#define _FMAX3(A, B, C) (fmaxf(fmaxf((A), (B)), (C)))

color_t rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (color_t){ r, g, b, a };
}

color_t rgb(uint8_t r, uint8_t g, uint8_t b) {
    return rgba(r, g, b, 255);
}

color_t rgbaf(float r, float g, float b, float a) {
    return rgbaf_to_rgba((color_rgbaf_t){ r, g, b, a });
}
color_t rgbf(float r, float g, float b) {
    return rgbaf(r, g, b, 1.f);
}

color_t hsva(float h, float s, float v, float a) {
    return hsva_to_rgba((color_hsva_t){ h, s, v, a });
}

color_t hsv(float h, float s, float v) {
    return hsva(h, s, v, 1.f);
}

color_t hsla(float h, float s, float l, float a) {
    return hsla_to_rgba((color_hsla_t){ h, s, l, a });
}

color_t hsl(float h, float s, float l) {
    return hsla(h, s, l, 1.f);
}

color_t lab(float l, float a, float b, float alpha) {
    return lab_to_rgba((color_lab_t){ l, a, b, alpha });
}

color_t xyz(float x, float y, float z, float a) {
    return xyz_to_rgba((color_xyz_t){ x, y, z, a });
}

color_t yuv(float y, float u, float v, float a) {
    return yuv_to_rgba((color_yuv_t){ y, u, v, a });
}

color_t cmyk(float c, float m, float y, float k, float a) {
    return cmyk_to_rgba((color_cmyk_t){ c, m, y, k, a });
}

color_t rgb_565(uint16_t rgb565, uint8_t a) {
    return rgb565_to_rgba((color_rgb_t565){ rgb565, a });
}

// Basic RGBA <-> RGBAf conversions
color_rgbaf_t rgba_to_rgbaf(color_t rgba) {
    color_rgbaf_t result;
    result.r = rgba.r / 255.0f;
    result.g = rgba.g / 255.0f;
    result.b = rgba.b / 255.0f;
    result.a = rgba.a / 255.0f;
    return result;
}

color_t rgbaf_to_rgba(color_rgbaf_t rgbaf) {
    color_t result;
    result.r = _CLAMP_UINT8(rgbaf.r);
    result.g = _CLAMP_UINT8(rgbaf.g);
    result.b = _CLAMP_UINT8(rgbaf.b);
    result.a = _CLAMP_UINT8(rgbaf.a);
    return result;
}

// HSV conversions
color_hsva_t rgba_to_hsva(color_t rgba) {
    color_rgbaf_t rgbaf = rgba_to_rgbaf(rgba);
    return rgbaf_to_hsva(rgbaf);
}

color_hsva_t rgbaf_to_hsva(color_rgbaf_t rgbaf) {
    color_hsva_t hsva;
    float max = _FMAX3(rgbaf.r, rgbaf.g, rgbaf.b);
    float min = _FMIN3(rgbaf.r, rgbaf.g, rgbaf.b);
    float delta = max - min;

    // Value
    hsva.v = max;

    // Saturation
    hsva.s = (max == 0) ? 0 : delta / max;

    // Hue
    if (delta == 0) {
        hsva.h = 0; // achromatic
    } else {
        if (max == rgbaf.r) {
            hsva.h = (rgbaf.g - rgbaf.b) / delta + (rgbaf.g < rgbaf.b ? 6 : 0);
        } else if (max == rgbaf.g) {
            hsva.h = (rgbaf.b - rgbaf.r) / delta + 2;
        } else {
            hsva.h = (rgbaf.r - rgbaf.g) / delta + 4;
        }
        hsva.h /= 6.0f;
    }

    hsva.a = rgbaf.a;
    return hsva;
}

color_t hsva_to_rgba(color_hsva_t hsva) {
    color_rgbaf_t rgbaf = hsva_to_rgbaf(hsva);
    return rgbaf_to_rgba(rgbaf);
}

color_rgbaf_t hsva_to_rgbaf(color_hsva_t hsva) {
    color_rgbaf_t rgbaf;

    float c = hsva.v * hsva.s;
    float x = c * (1 - fabsf(fmodf(hsva.h * 6.0f, 2.0f) - 1));
    float m = hsva.v - c;

    float r1, g1, b1;

    if (hsva.h < 1.0f/6.0f) {
        r1 = c; g1 = x; b1 = 0;
    } else if (hsva.h < 2.0f/6.0f) {
        r1 = x; g1 = c; b1 = 0;
    } else if (hsva.h < 3.0f / 6.0f) {
        r1 = 0; g1 = c; b1 = x;
    } else if (hsva.h < 4.0f/6.0f) {
        r1 = 0; g1 = x; b1 = c;
    } else if (hsva.h < 5.0f/6.0f) {
        r1 = x; g1 = 0; b1 = c;
    } else {
        r1 = c; g1 = 0; b1 = x;
    }

    rgbaf.r = r1 + m;
    rgbaf.g = g1 + m;
    rgbaf.b = b1 + m;
    rgbaf.a = hsva.a;
    return rgbaf;
}

// HSL conversions
color_hsla_t rgba_to_hsla(color_t rgba) {
    color_rgbaf_t rgbaf = rgba_to_rgbaf(rgba);
    return rgbaf_to_hsla(rgbaf);
}

color_hsla_t rgbaf_to_hsla(color_rgbaf_t rgbaf) {
    color_hsla_t hsla;
    float max = _FMAX3(rgbaf.r, rgbaf.g, rgbaf.b);
    float min = _FMIN3(rgbaf.r, rgbaf.g, rgbaf.b);
    float delta = max - min;

    // Lightness
    hsla.l = (max + min) / 2.0f;

    if (delta == 0)
        hsla.h = hsla.s = 0; // achromatic
    else {
        // Saturation
        hsla.s = hsla.l > 0.5f ? delta / (2.0f - max - min) : delta / (max + min);

        // Hue
        if (max == rgbaf.r)
            hsla.h = (rgbaf.g - rgbaf.b) / delta + (rgbaf.g < rgbaf.b ? 6 : 0);
        else if (max == rgbaf.g)
            hsla.h = (rgbaf.b - rgbaf.r) / delta + 2;
        else
            hsla.h = (rgbaf.r - rgbaf.g) / delta + 4;
        hsla.h /= 6.0f;
    }

    hsla.a = rgbaf.a;
    return hsla;
}

color_t hsla_to_rgba(color_hsla_t hsla) {
    color_rgbaf_t rgbaf = hsla_to_rgbaf(hsla);
    return rgbaf_to_rgba(rgbaf);
}

static inline float hue_to_rgb(float p, float q, float t) {
    if (t < 0)
        t += 1;
    if (t > 1)
        t -= 1;
    if (t < 1.0f/6.0f)
        return p + (q - p) * 6 * t;
    if (t < 1.0f/2.0f)
        return q;
    if (t < 2.0f/3.0f)
        return p + (q - p) * (2.0f/3.0f - t) * 6;
    return p;
}

color_rgbaf_t hsla_to_rgbaf(color_hsla_t hsla) {
    color_rgbaf_t rgbaf;

    if (hsla.s == 0)
        rgbaf.r = rgbaf.g = rgbaf.b = hsla.l; // achromatic
    else {
        float q = hsla.l < 0.5f ? hsla.l * (1 + hsla.s) : hsla.l + hsla.s - hsla.l * hsla.s;
        float p = 2 * hsla.l - q;

        rgbaf.r = hue_to_rgb(p, q, hsla.h + 1.0f/3.0f);
        rgbaf.g = hue_to_rgb(p, q, hsla.h);
        rgbaf.b = hue_to_rgb(p, q, hsla.h - 1.0f/3.0f);
    }

    rgbaf.a = hsla.a;
    return rgbaf;
}

// XYZ conversions (sRGB D65 white point)
color_xyz_t rgba_to_xyz(color_t rgba) {
    color_rgbaf_t rgbaf = rgba_to_rgbaf(rgba);

    // Apply gamma correction (sRGB to linear RGB)
    float r = (rgbaf.r > 0.04045f) ? powf((rgbaf.r + 0.055f) / 1.055f, 2.4f) : rgbaf.r / 12.92f;
    float g = (rgbaf.g > 0.04045f) ? powf((rgbaf.g + 0.055f) / 1.055f, 2.4f) : rgbaf.g / 12.92f;
    float b = (rgbaf.b > 0.04045f) ? powf((rgbaf.b + 0.055f) / 1.055f, 2.4f) : rgbaf.b / 12.92f;

    color_xyz_t xyz;

    // sRGB to XYZ matrix (D65)
    xyz.x = r * 0.4124564f + g * 0.3575761f + b * 0.1804375f;
    xyz.y = r * 0.2126729f + g * 0.7151522f + b * 0.0721750f;
    xyz.z = r * 0.0193339f + g * 0.1191920f + b * 0.9503041f;
    xyz.a = rgbaf.a;

    return xyz;
}

color_t xyz_to_rgba(color_xyz_t xyz) {
    // XYZ to sRGB matrix (D65)
    float r = xyz.x *  3.2404542f + xyz.y * -1.5371385f + xyz.z * -0.4985314f;
    float g = xyz.x * -0.9692660f + xyz.y *  1.8760108f + xyz.z *  0.0415560f;
    float b = xyz.x *  0.0556434f + xyz.y * -0.2040259f + xyz.z *  1.0572252f;

    // Apply gamma correction (linear RGB to sRGB)
    r = (r > 0.0031308f) ? 1.055f * powf(r, 1.0f/2.4f) - 0.055f : 12.92f * r;
    g = (g > 0.0031308f) ? 1.055f * powf(g, 1.0f/2.4f) - 0.055f : 12.92f * g;
    b = (b > 0.0031308f) ? 1.055f * powf(b, 1.0f/2.4f) - 0.055f : 12.92f * b;

    color_rgbaf_t rgbaf = {
        _CLAMP_FLOAT(r),
        _CLAMP_FLOAT(g),
        _CLAMP_FLOAT(b),
        xyz.a
    };
    return rgbaf_to_rgba(rgbaf);
}

// Lab conversions
color_lab_t xyz_to_lab(color_xyz_t xyz) {
    // D65 white point
    const float xn = 0.95047f;
    const float yn = 1.00000f;
    const float zn = 1.08883f;

    float x = xyz.x / xn;
    float y = xyz.y / yn;
    float z = xyz.z / zn;

    // Apply Lab transformation
    x = (x > 0.008856f) ? cbrtf(x) : (7.787f * x + 16.0f/116.0f);
    y = (y > 0.008856f) ? cbrtf(y) : (7.787f * y + 16.0f/116.0f);
    z = (z > 0.008856f) ? cbrtf(z) : (7.787f * z + 16.0f/116.0f);

    color_lab_t lab;
    lab.l = 116.0f * y - 16.0f;
    lab.a = 500.0f * (x - y);
    lab.b = 200.0f * (y - z);
    lab.alpha = xyz.a;

    return lab;
}

color_xyz_t lab_to_xyz(color_lab_t lab) {
    // D65 white point
    const float xn = 0.95047f;
    const float yn = 1.00000f;
    const float zn = 1.08883f;

    float fy = (lab.l + 16.0f) / 116.0f;
    float fx = lab.a / 500.0f + fy;
    float fz = fy - lab.b / 200.0f;

    float x = (fx > 0.206897f) ? fx*fx*fx : (fx - 16.0f/116.0f) / 7.787f;
    float y = (fy > 0.206897f) ? fy*fy*fy : (fy - 16.0f/116.0f) / 7.787f;
    float z = (fz > 0.206897f) ? fz*fz*fz : (fz - 16.0f/116.0f) / 7.787f;

    color_xyz_t xyz;
    xyz.x = x * xn;
    xyz.y = y * yn;
    xyz.z = z * zn;
    xyz.a = lab.alpha;

    return xyz;
}

color_lab_t rgba_to_lab(color_t rgba) {
    color_xyz_t xyz = rgba_to_xyz(rgba);
    return xyz_to_lab(xyz);
}

color_t lab_to_rgba(color_lab_t lab) {
    color_xyz_t xyz = lab_to_xyz(lab);
    return xyz_to_rgba(xyz);
}

// YUV conversions (BT.601)
color_yuv_t rgba_to_yuv(color_t rgba) {
    color_rgbaf_t rgbaf = rgba_to_rgbaf(rgba);

    color_yuv_t yuv;
    yuv.y = 0.299f * rgbaf.r + 0.587f * rgbaf.g + 0.114f * rgbaf.b;
    yuv.u = -0.14713f * rgbaf.r - 0.28886f * rgbaf.g + 0.436f * rgbaf.b;
    yuv.v = 0.615f * rgbaf.r - 0.51499f * rgbaf.g - 0.10001f * rgbaf.b;
    yuv.a = rgbaf.a;

    return yuv;
}

color_t yuv_to_rgba(color_yuv_t yuv) {
    color_rgbaf_t rgbaf;

    rgbaf.r = yuv.y + 1.13983f * yuv.v;
    rgbaf.g = yuv.y - 0.39465f * yuv.u - 0.58060f * yuv.v;
    rgbaf.b = yuv.y + 2.03211f * yuv.u;
    rgbaf.a = yuv.a;

    // Clamp values
    rgbaf.r = _CLAMP_FLOAT(rgbaf.r);
    rgbaf.g = _CLAMP_FLOAT(rgbaf.g);
    rgbaf.b = _CLAMP_FLOAT(rgbaf.b);

    return rgbaf_to_rgba(rgbaf);
}

// CMYK conversions
color_cmyk_t rgba_to_cmyk(color_t rgba) {
    color_rgbaf_t rgbaf = rgba_to_rgbaf(rgba);

    color_cmyk_t cmyk;
    // Find K (black)
    cmyk.k = 1.0f - _FMAX3(rgbaf.r, rgbaf.g, rgbaf.b);

    if (cmyk.k == 1.0f) // Pure black
        cmyk.c = cmyk.m = cmyk.y = 0.0f;
    else {
        float inv_k = 1.0f - cmyk.k;
        cmyk.c = (1.0f - rgbaf.r - cmyk.k) / inv_k;
        cmyk.m = (1.0f - rgbaf.g - cmyk.k) / inv_k;
        cmyk.y = (1.0f - rgbaf.b - cmyk.k) / inv_k;
    }

    cmyk.a = rgbaf.a;
    return cmyk;
}

color_t cmyk_to_rgba(color_cmyk_t cmyk) {
    color_rgbaf_t rgbaf;

    float inv_k = 1.0f - cmyk.k;
    rgbaf.r = (1.0f - cmyk.c) * inv_k;
    rgbaf.g = (1.0f - cmyk.m) * inv_k;
    rgbaf.b = (1.0f - cmyk.y) * inv_k;
    rgbaf.a = cmyk.a;

    return rgbaf_to_rgba(rgbaf);
}

// RGB565 conversions
color_rgb_t565 rgba_to_rgb565(color_t rgba) {
    color_rgb_t565 rgb565;

    // Convert to 5-6-5 format
    uint16_t r = (rgba.r >> 3) & 0x1F;
    uint16_t g = (rgba.g >> 2) & 0x3F;
    uint16_t b = (rgba.b >> 3) & 0x1F;

    rgb565.rgb565 = (r << 11) | (g << 5) | b;
    rgb565.a = rgba.a;

    return rgb565;
}

color_t rgb565_to_rgba(color_rgb_t565 rgb565) {
    color_t rgba;

    // Extract components
    uint16_t r = (rgb565.rgb565 >> 11) & 0x1F;
    uint16_t g = (rgb565.rgb565 >> 5) & 0x3F;
    uint16_t b = rgb565.rgb565 & 0x1F;

    // Scale back to 8-bit
    rgba.r = (r << 3) | (r >> 2);
    rgba.g = (g << 2) | (g >> 4);
    rgba.b = (b << 3) | (b >> 2);
    rgba.a = rgb565.a;

    return rgba;
}

float color_distance_lab(color_lab_t a, color_lab_t b) {
    float dl = a.l - b.l;
    float da = a.a - b.a;
    float db = a.b - b.b;
    return sqrtf(dl*dl + da*da + db*db);
}

float color_distance(color_t a, color_t b) {
    int dr = a.r - b.r;
    int dg = a.g - b.g;
    int db = a.b - b.b;
    return sqrtf(dr*dr + dg*dg + db*db);
}

color_t color_lerp(color_t a, color_t b, float t) {
    t = _CLAMP_FLOAT(t);
    color_t result;
    result.r = (uint8_t)(a.r + t * (b.r - a.r));
    result.g = (uint8_t)(a.g + t * (b.g - a.g));
    result.b = (uint8_t)(a.b + t * (b.b - a.b));
    result.a = (uint8_t)(a.a + t * (b.a - a.a));
    return result;
}

// Perceptual luminance using sRGB coefficients
float color_luminance(color_t color) {
    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    return 0.299f * rgbaf.r + 0.587f * rgbaf.g + 0.114f * rgbaf.b;
}

// Relative luminance for WCAG calculations (uses gamma-corrected values)
float color_relative_luminance(color_t color) {
    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);

    // Apply gamma correction (sRGB to linear RGB)
    float r = (rgbaf.r > 0.04045f) ? powf((rgbaf.r + 0.055f) / 1.055f, 2.4f) : rgbaf.r / 12.92f;
    float g = (rgbaf.g > 0.04045f) ? powf((rgbaf.g + 0.055f) / 1.055f, 2.4f) : rgbaf.g / 12.92f;
    float b = (rgbaf.b > 0.04045f) ? powf((rgbaf.b + 0.055f) / 1.055f, 2.4f) : rgbaf.b / 12.92f;

    return 0.2126f * r + 0.7152f * g + 0.0722f * b;
}

// Simple average brightness
float color_brightness(color_t color) {
    return (color.r + color.g + color.b) / (3.0f * 255.0f);
}

// Check if color is considered dark (using perceptual luminance)
int color_is_dark(color_t color) {
    return color_luminance(color) < 0.5f;
}

// Get saturation level (0-1)
float color_saturation(color_t color) {
    color_hsva_t hsva = rgba_to_hsva(color);
    return hsva.s;
}

// Get hue in degrees (0-360)
float color_hue(color_t color) {
    color_hsva_t hsva = rgba_to_hsva(color);
    return hsva.h * 360.0f;
}

// Convert to grayscale using perceptual luminance
color_t color_grayscale(color_t color) {
    uint8_t gray = (uint8_t)(color_luminance(color) * 255.0f);
    color_t result = {gray, gray, gray, color.a};
    return result;
}

// Invert RGB channels (keeping alpha)
color_t color_invert(color_t color) {
    color_t result = {
        255 - color.r,
        255 - color.g,
        255 - color.b,
        color.a
    };
    return result;
}

// Get complementary color (opposite hue)
color_t color_complement(color_t color) {
    color_hsva_t hsva = rgba_to_hsva(color);
    hsva.h = fmodf(hsva.h + 0.5f, 1.0f);  // Add 180 degrees (0.5 in normalized hue)
    return hsva_to_rgba(hsva);
}

// Additional analysis functions

// Get the dominant color channel
int color_dominant_channel(color_t color) {
    if (color.r >= color.g && color.r >= color.b) return 0; // Red
    if (color.g >= color.b) return 1; // Green
    return 2; // Blue
}

// Check if color is grayscale (all channels equal within tolerance)
int color_is_grayscale(color_t color) {
    int max_diff = abs(color.r - color.g);
    max_diff = fmax(max_diff, abs(color.r - color.b));
    max_diff = fmax(max_diff, abs(color.g - color.b));
    return max_diff <= 2; // Allow small tolerance for rounding errors
}

// Get color temperature estimate (very rough approximation)
float color_temperature_estimate(color_t color) {
    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);

    // Rough approximation based on blue/red ratio
    if (rgbaf.r == 0.0f) return 6500.0f; // Default daylight

    float ratio = rgbaf.b / rgbaf.r;
    if (ratio > 1.0f) {
        // More blue than red - cooler
        return 6500.0f + (ratio - 1.0f) * 3500.0f; // Up to 10000K
    } else {
        // More red than blue - warmer
        return 6500.0f - (1.0f - ratio) * 3500.0f; // Down to 3000K
    }
}

// Check if color is "warm" (reddish/yellowish)
int color_is_warm(color_t color) {
    return color.r > color.b && (color.r + color.g) > color.b * 1.5f;
}

// Check if color is "cool" (blueish/greenish)
int color_is_cool(color_t color) {
    return color.b > color.r && (color.b + color.g) > color.r * 1.5f;
}

// Get color purity (distance from gray)
float color_purity(color_t color) {
    uint8_t gray = (uint8_t)(color_luminance(color) * 255.0f);
    int dr = abs(color.r - gray);
    int dg = abs(color.g - gray);
    int db = abs(color.b - gray);
    return sqrtf(dr*dr + dg*dg + db*db) / (255.0f * sqrtf(3.0f));
}

// Get color energy (sum of all channels)
float color_energy(color_t color) {
    return (color.r + color.g + color.b) / (3.0f * 255.0f);
}

// Adjust brightness (-1.0 to 1.0, where 0 = no change)
color_t color_adjust_brightness(color_t color, float amount) {
    amount = _CLAMP_FLOAT_RANGE(amount, -1.0f, 1.0f);

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    rgbaf.r = _CLAMP_FLOAT(rgbaf.r + amount);
    rgbaf.g = _CLAMP_FLOAT(rgbaf.g + amount);
    rgbaf.b = _CLAMP_FLOAT(rgbaf.b + amount);

    return rgbaf_to_rgba(rgbaf);
}

// Adjust contrast (-1.0 to 1.0, where 0 = no change)
color_t color_adjust_contrast(color_t color, float amount) {
    amount = _CLAMP_FLOAT_RANGE(amount, -1.0f, 1.0f);
    float factor = (1.0f + amount) / (1.0f - amount);

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    rgbaf.r = _CLAMP_FLOAT((rgbaf.r - 0.5f) * factor + 0.5f);
    rgbaf.g = _CLAMP_FLOAT((rgbaf.g - 0.5f) * factor + 0.5f);
    rgbaf.b = _CLAMP_FLOAT((rgbaf.b - 0.5f) * factor + 0.5f);

    return rgbaf_to_rgba(rgbaf);
}

// Apply gamma correction
color_t color_adjust_gamma(color_t color, float gamma) {
    if (gamma <= 0.0f) gamma = 0.01f; // Prevent division by zero

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    rgbaf.r = powf(rgbaf.r, 1.0f / gamma);
    rgbaf.g = powf(rgbaf.g, 1.0f / gamma);
    rgbaf.b = powf(rgbaf.b, 1.0f / gamma);

    return rgbaf_to_rgba(rgbaf);
}

// Increase saturation (0.0 to 2.0+, where 1.0 = no change)
color_t color_saturate(color_t color, float amount) {
    if (amount < 0.0f) amount = 0.0f;

    color_hsva_t hsva = rgba_to_hsva(color);
    hsva.s = _CLAMP_FLOAT(hsva.s * amount);

    return hsva_to_rgba(hsva);
}

// Decrease saturation (0.0 to 1.0, where 0.0 = grayscale, 1.0 = no change)
color_t color_desaturate(color_t color, float amount) {
    amount = _CLAMP_FLOAT(amount);

    color_hsva_t hsva = rgba_to_hsva(color);
    hsva.s *= amount;

    return hsva_to_rgba(hsva);
}

// Shift hue by degrees (-360 to 360)
color_t color_hue_shift(color_t color, float degrees) {
    float shift = fmodf(degrees / 360.0f, 1.0f);
    if (shift < 0.0f) shift += 1.0f;

    color_hsva_t hsva = rgba_to_hsva(color);
    hsva.h = fmodf(hsva.h + shift, 1.0f);

    return hsva_to_rgba(hsva);
}

// Adjust color temperature (1000K to 40000K, 6500K = daylight)
color_t color_adjust_temperature(color_t color, float kelvin) {
    kelvin = _CLAMP_FLOAT_RANGE(kelvin, 1000.0f, 40000.0f);

    // Temperature to RGB conversion (rough approximation)
    float temp = kelvin / 100.0f;
    float r, g, b;

    if (temp <= 66.0f) {
        r = 255.0f;
        g = temp;
        g = 99.4708025861f * logf(g) - 161.1195681661f;
    } else {
        r = temp - 60.0f;
        r = 329.698727446f * powf(r, -0.1332047592f);
        g = temp - 60.0f;
        g = 288.1221695283f * powf(g, -0.0755148492f);
    }

    if (temp >= 66.0f) {
        b = 255.0f;
    } else if (temp <= 19.0f) {
        b = 0.0f;
    } else {
        b = temp - 10.0f;
        b = 138.5177312231f * logf(b) - 305.0447927307f;
    }

    // Normalize and blend with original color
    r = _CLAMP_FLOAT_RANGE(r, 0.0f, 255.0f) / 255.0f;
    g = _CLAMP_FLOAT_RANGE(g, 0.0f, 255.0f) / 255.0f;
    b = _CLAMP_FLOAT_RANGE(b, 0.0f, 255.0f) / 255.0f;

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    rgbaf.r *= r;
    rgbaf.g *= g;
    rgbaf.b *= b;

    return rgbaf_to_rgba(rgbaf);
}

// Adjust tint (magenta-green balance, -1.0 to 1.0)
color_t color_tint(color_t color, float amount) {
    amount = _CLAMP_FLOAT_RANGE(amount, -1.0f, 1.0f);

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);

    if (amount > 0.0f) {
        // Add magenta (increase red and blue, decrease green)
        rgbaf.r += amount * 0.1f;
        rgbaf.b += amount * 0.1f;
        rgbaf.g -= amount * 0.05f;
    } else {
        // Add green (increase green, decrease red and blue)
        rgbaf.g += (-amount) * 0.1f;
        rgbaf.r -= (-amount) * 0.05f;
        rgbaf.b -= (-amount) * 0.05f;
    }

    rgbaf.r = _CLAMP_FLOAT(rgbaf.r);
    rgbaf.g = _CLAMP_FLOAT(rgbaf.g);
    rgbaf.b = _CLAMP_FLOAT(rgbaf.b);

    return rgbaf_to_rgba(rgbaf);
}

// Adjust exposure in stops (-3.0 to 3.0, where 0 = no change)
color_t color_adjust_exposure(color_t color, float stops) {
    stops = _CLAMP_FLOAT_RANGE(stops, -3.0f, 3.0f);
    float factor = powf(2.0f, stops);

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    rgbaf.r = _CLAMP_FLOAT(rgbaf.r * factor);
    rgbaf.g = _CLAMP_FLOAT(rgbaf.g * factor);
    rgbaf.b = _CLAMP_FLOAT(rgbaf.b * factor);

    return rgbaf_to_rgba(rgbaf);
}

// Adjust highlights (-1.0 to 1.0, affects bright areas)
color_t color_adjust_highlights(color_t color, float amount) {
    amount = _CLAMP_FLOAT_RANGE(amount, -1.0f, 1.0f);

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    float lum = color_luminance(color);

    // Only affect pixels above 50% luminance
    if (lum > 0.5f) {
        float weight = (lum - 0.5f) * 2.0f; // 0 to 1
        rgbaf.r = _CLAMP_FLOAT(rgbaf.r + amount * weight * 0.2f);
        rgbaf.g = _CLAMP_FLOAT(rgbaf.g + amount * weight * 0.2f);
        rgbaf.b = _CLAMP_FLOAT(rgbaf.b + amount * weight * 0.2f);
    }

    return rgbaf_to_rgba(rgbaf);
}

// Adjust shadows (-1.0 to 1.0, affects dark areas)
color_t color_adjust_shadows(color_t color, float amount) {
    amount = _CLAMP_FLOAT_RANGE(amount, -1.0f, 1.0f);

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    float lum = color_luminance(color);

    // Only affect pixels below 50% luminance
    if (lum < 0.5f) {
        float weight = (0.5f - lum) * 2.0f; // 0 to 1
        rgbaf.r = _CLAMP_FLOAT(rgbaf.r + amount * weight * 0.2f);
        rgbaf.g = _CLAMP_FLOAT(rgbaf.g + amount * weight * 0.2f);
        rgbaf.b = _CLAMP_FLOAT(rgbaf.b + amount * weight * 0.2f);
    }

    return rgbaf_to_rgba(rgbaf);
}

// Adjust whites (-1.0 to 1.0, affects very bright areas)
color_t color_adjust_whites(color_t color, float amount) {
    amount = _CLAMP_FLOAT_RANGE(amount, -1.0f, 1.0f);

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    float lum = color_luminance(color);

    // Only affect pixels above 80% luminance
    if (lum > 0.8f) {
        float weight = (lum - 0.8f) * 5.0f; // 0 to 1
        rgbaf.r = _CLAMP_FLOAT(rgbaf.r + amount * weight * 0.3f);
        rgbaf.g = _CLAMP_FLOAT(rgbaf.g + amount * weight * 0.3f);
        rgbaf.b = _CLAMP_FLOAT(rgbaf.b + amount * weight * 0.3f);
    }

    return rgbaf_to_rgba(rgbaf);
}

// Adjust blacks (-1.0 to 1.0, affects very dark areas)
color_t color_adjust_blacks(color_t color, float amount) {
    amount = _CLAMP_FLOAT_RANGE(amount, -1.0f, 1.0f);

    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    float lum = color_luminance(color);

    // Only affect pixels below 20% luminance
    if (lum < 0.2f) {
        float weight = (0.2f - lum) * 5.0f; // 0 to 1
        rgbaf.r = _CLAMP_FLOAT(rgbaf.r + amount * weight * 0.3f);
        rgbaf.g = _CLAMP_FLOAT(rgbaf.g + amount * weight * 0.3f);
        rgbaf.b = _CLAMP_FLOAT(rgbaf.b + amount * weight * 0.3f);
    }

    return rgbaf_to_rgba(rgbaf);
}

// Adjust clarity/structure (-1.0 to 1.0, enhances local contrast)
color_t color_adjust_clarity(color_t color, float amount) {
    amount = _CLAMP_FLOAT_RANGE(amount, -1.0f, 1.0f);

    // Simplified clarity - boost contrast in mid-tones
    color_rgbaf_t rgbaf = rgba_to_rgbaf(color);
    float lum = color_luminance(color);

    // Maximum effect at 50% luminance
    float weight = 1.0f - fabsf(lum - 0.5f) * 2.0f;
    weight = _CLAMP_FLOAT(weight);

    float contrast_factor = 1.0f + amount * weight * 0.5f;
    rgbaf.r = _CLAMP_FLOAT((rgbaf.r - 0.5f) * contrast_factor + 0.5f);
    rgbaf.g = _CLAMP_FLOAT((rgbaf.g - 0.5f) * contrast_factor + 0.5f);
    rgbaf.b = _CLAMP_FLOAT((rgbaf.b - 0.5f) * contrast_factor + 0.5f);

    return rgbaf_to_rgba(rgbaf);
}

// Adjust vibrance (-1.0 to 1.0, smart saturation that protects skin tones)
color_t color_adjust_vibrance(color_t color, float amount) {
    amount = _CLAMP_FLOAT_RANGE(amount, -1.0f, 1.0f);

    color_hsva_t hsva = rgba_to_hsva(color);

    // Reduce effect on skin tones (hue around 0.05-0.15, or 18-54 degrees)
    float skin_protection = 1.0f;
    if (hsva.h >= 0.05f && hsva.h <= 0.15f) {
        skin_protection = 0.3f; // Reduce vibrance effect on skin tones
    }

    // Reduce effect on already saturated colors
    float saturation_protection = 1.0f - hsva.s * 0.5f;

    float final_amount = amount * skin_protection * saturation_protection;
    hsva.s = _CLAMP_FLOAT(hsva.s + final_amount * 0.5f);

    return hsva_to_rgba(hsva);
}

// Helper function to blend alpha
static inline uint8_t blend_alpha(uint8_t a1, uint8_t a2) {
    return 255 - (((255 - a1) * (255 - a2)) / 255);
}

// Multiply: a * b / 255
color_t color_multiply(color_t a, color_t b) {
    color_t result;
    result.r = (a.r * b.r) / 255;
    result.g = (a.g * b.g) / 255;
    result.b = (a.b * b.b) / 255;
    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Screen: 255 - ((255-a) * (255-b) / 255)
color_t color_screen(color_t a, color_t b) {
    color_t result;
    result.r = 255 - (((255 - a.r) * (255 - b.r)) / 255);
    result.g = 255 - (((255 - a.g) * (255 - b.g)) / 255);
    result.b = 255 - (((255 - a.b) * (255 - b.b)) / 255);
    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Overlay: combines multiply and screen
color_t color_overlay(color_t a, color_t b) {
    color_t result;

    // For each channel: if base < 128, multiply*2, else screen*2-255
    result.r = (a.r < 128) ? (2 * a.r * b.r) / 255 : 255 - (2 * (255 - a.r) * (255 - b.r)) / 255;
    result.g = (a.g < 128) ? (2 * a.g * b.g) / 255 : 255 - (2 * (255 - a.g) * (255 - b.g)) / 255;
    result.b = (a.b < 128) ? (2 * a.b * b.b) / 255 : 255 - (2 * (255 - a.b) * (255 - b.b)) / 255;
    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Soft Light: complex blend mode
color_t color_soft_light(color_t a, color_t b) {
    color_t result;

    // Simplified soft light formula
    for (int i = 0; i < 3; i++) {
        uint8_t base = ((uint8_t*)&a)[i];
        uint8_t blend = ((uint8_t*)&b)[i];

        if (blend < 128) {
            ((uint8_t*)&result)[i] = (2 * base * blend) / 255 + (base * base * (255 - 2 * blend)) / (255 * 255);
        } else {
            int sqrt_base = (int)(255 * sqrt(base / 255.0));
            ((uint8_t*)&result)[i] = (2 * base * (255 - blend)) / 255 + sqrt_base * (2 * blend - 255) / 255;
        }
    }
    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Hard Light: reverse of overlay
color_t color_hard_light(color_t a, color_t b) {
    color_t result;

    // For each channel: if blend < 128, multiply*2, else screen*2-255
    result.r = (b.r < 128) ? (2 * a.r * b.r) / 255 : 255 - (2 * (255 - a.r) * (255 - b.r)) / 255;
    result.g = (b.g < 128) ? (2 * a.g * b.g) / 255 : 255 - (2 * (255 - a.g) * (255 - b.g)) / 255;
    result.b = (b.b < 128) ? (2 * a.b * b.b) / 255 : 255 - (2 * (255 - a.b) * (255 - b.b)) / 255;
    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Color Dodge: base / (255 - blend)
color_t color_color_dodge(color_t a, color_t b) {
    color_t result;

    result.r = (b.r == 255) ? 255 : (a.r * 255) / (255 - b.r);
    result.g = (b.g == 255) ? 255 : (a.g * 255) / (255 - b.g);
    result.b = (b.b == 255) ? 255 : (a.b * 255) / (255 - b.b);

    // Clamp to 255
    result.r = (result.r > 255) ? 255 : result.r;
    result.g = (result.g > 255) ? 255 : result.g;
    result.b = (result.b > 255) ? 255 : result.b;

    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Color Burn: 255 - (255 - base) / blend
color_t color_color_burn(color_t a, color_t b) {
    color_t result;

    result.r = (b.r == 0) ? 0 : 255 - ((255 - a.r) * 255) / b.r;
    result.g = (b.g == 0) ? 0 : 255 - ((255 - a.g) * 255) / b.g;
    result.b = (b.b == 0) ? 0 : 255 - ((255 - a.b) * 255) / b.b;

    // Clamp to valid range
    result.r = (result.r > 255) ? 255 : (result.r < 0) ? 0 : result.r;
    result.g = (result.g > 255) ? 255 : (result.g < 0) ? 0 : result.g;
    result.b = (result.b > 255) ? 255 : (result.b < 0) ? 0 : result.b;

    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Darken: min(a, b)
color_t color_darken(color_t a, color_t b) {
    color_t result;
    result.r = (a.r < b.r) ? a.r : b.r;
    result.g = (a.g < b.g) ? a.g : b.g;
    result.b = (a.b < b.b) ? a.b : b.b;
    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Lighten: max(a, b)
color_t color_lighten(color_t a, color_t b) {
    color_t result;
    result.r = (a.r > b.r) ? a.r : b.r;
    result.g = (a.g > b.g) ? a.g : b.g;
    result.b = (a.b > b.b) ? a.b : b.b;
    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Difference: |a - b|
color_t color_difference(color_t a, color_t b) {
    color_t result;
    result.r = (a.r > b.r) ? a.r - b.r : b.r - a.r;
    result.g = (a.g > b.g) ? a.g - b.g : b.g - a.g;
    result.b = (a.b > b.b) ? a.b - b.b : b.b - a.b;
    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Exclusion: a + b - 2*a*b/255
color_t color_exclusion(color_t a, color_t b) {
    color_t result;
    result.r = a.r + b.r - (2 * a.r * b.r) / 255;
    result.g = a.g + b.g - (2 * a.g * b.g) / 255;
    result.b = a.b + b.b - (2 * a.b * b.b) / 255;
    result.a = blend_alpha(a.a, b.a);
    return result;
}

// Alpha blending: standard Porter-Duff "over" operation
color_t color_alpha_blend(color_t fg, color_t bg) {
    color_t result;

    // Convert alpha to 0-1 range for calculations
    float fg_alpha = fg.a / 255.0f;
    float bg_alpha = bg.a / 255.0f;

    // Calculate output alpha: fg_alpha + bg_alpha * (1 - fg_alpha)
    float out_alpha = fg_alpha + bg_alpha * (1.0f - fg_alpha);

    if (out_alpha == 0) {
        // Completely transparent
        result.r = result.g = result.b = result.a = 0;
        return result;
    }

    // Alpha blend RGB channels: (fg * fg_alpha + bg * bg_alpha * (1 - fg_alpha)) / out_alpha
    result.r = (uint8_t)((fg.r * fg_alpha + bg.r * bg_alpha * (1.0f - fg_alpha)) / out_alpha);
    result.g = (uint8_t)((fg.g * fg_alpha + bg.g * bg_alpha * (1.0f - fg_alpha)) / out_alpha);
    result.b = (uint8_t)((fg.b * fg_alpha + bg.b * bg_alpha * (1.0f - fg_alpha)) / out_alpha);
    result.a = (uint8_t)(out_alpha * 255);

    return result;
}

// Premultiply alpha: multiply RGB channels by alpha
color_t color_premultiply_alpha(color_t color) {
    color_t result;

    float alpha = color.a / 255.0f;
    result.r = (uint8_t)(color.r * alpha);
    result.g = (uint8_t)(color.g * alpha);
    result.b = (uint8_t)(color.b * alpha);
    result.a = color.a;

    return result;
}

// Unpremultiply alpha: divide RGB channels by alpha
color_t color_unpremultiply_alpha(color_t color) {
    color_t result;

    if (color.a == 0) {
        // Completely transparent - RGB values are undefined
        result.r = result.g = result.b = result.a = 0;
        return result;
    }

    float alpha = color.a / 255.0f;
    result.r = (uint8_t)(color.r / alpha);
    result.g = (uint8_t)(color.g / alpha);
    result.b = (uint8_t)(color.b / alpha);
    result.a = color.a;

    // Clamp to prevent overflow
    result.r = (result.r > 255) ? 255 : result.r;
    result.g = (result.g > 255) ? 255 : result.g;
    result.b = (result.b > 255) ? 255 : result.b;

    return result;
}

// Normalize hue to 0-360 range
static float normalize_hue(float hue) {
    while (hue < 0) hue += 360;
    while (hue >= 360) hue -= 360;
    return hue;
}

// Analogous colors: adjacent hues (±30° typically)
void color_analogous(color_t base, color_t* colors, int count) {
    if (count <= 0) return;

    color_hsva_t base_hsv = rgba_to_hsva(base);
    float step = 60.0f / (count + 1); // Spread across ±30°

    for (int i = 0; i < count; i++) {
        color_hsva_t variant = base_hsv;
        variant.h = normalize_hue(base_hsv.h + (i + 1 - count/2.0f) * step);
        colors[i] = hsva_to_rgba(variant);
    }
}

// Triadic colors: 120° apart
void color_triadic(color_t base, color_t* color1, color_t* color2) {
    if (!color1 && !color2)
        return;

    color_hsva_t base_hsv = rgba_to_hsva(base);

    // First triadic color: +120°
    color_hsva_t triadic1 = base_hsv;
    triadic1.h = normalize_hue(base_hsv.h + 120);
    if (color1)
        *color1 = hsva_to_rgba(triadic1);

    // Second triadic color: +240°
    color_hsva_t triadic2 = base_hsv;
    triadic2.h = normalize_hue(base_hsv.h + 240);
    if (color2)
        *color2 = hsva_to_rgba(triadic2);
}

// Tetradic colors: rectangle scheme (90° apart)
void color_tetradic(color_t base, color_t* color1, color_t* color2, color_t* color3) {
    if (!color1 && !color2 && !color3)
        return;

    color_hsva_t base_hsv = rgba_to_hsva(base);
    // Four colors: +90°, +180°, +270°
    color_hsva_t tetradic = base_hsv;
    tetradic.h = normalize_hue(base_hsv.h + 90);
    if (color1)
        *color1 = hsva_to_rgba(tetradic);
    tetradic.h = normalize_hue(base_hsv.h + 180);
    if (color2)
        *color2 = hsva_to_rgba(tetradic);
    tetradic.h = normalize_hue(base_hsv.h + 270);
    if (color3)
        *color3 = hsva_to_rgba(tetradic);
}

// Split complementary: base complement ±30°
void color_split_complementary(color_t base, color_t* color1, color_t* color2) {
    if (!color1 && !color2)
        return;

    color_hsva_t base_hsv = rgba_to_hsva(base);
    float complement_hue = normalize_hue(base_hsv.h + 180);

    // First split complement: complement - 30°
    color_hsva_t split1 = base_hsv;
    split1.h = normalize_hue(complement_hue - 30);
    if (color1)
        *color1 = hsva_to_rgba(split1);

    // Second split complement: complement + 30°
    color_hsva_t split2 = base_hsv;
    split2.h = normalize_hue(complement_hue + 30);
    if (color2)
        *color2 = hsva_to_rgba(split2);
}

// Monochromatic colors: same hue, different saturation/value
void color_monochromatic(color_t base, color_t* colors, int count) {
    if (count <= 0) return;

    color_hsva_t base_hsv = rgba_to_hsva(base);

    for (int i = 0; i < count; i++) {
        color_hsva_t variant = base_hsv;
        float factor = (i + 1.0f) / (count + 1.0f);

        // Vary saturation and value
        variant.s = base_hsv.s * (0.3f + 0.7f * factor);
        variant.v = base_hsv.v * (0.4f + 0.6f * factor);

        // Clamp values
        variant.s = (variant.s > 1.0f) ? 1.0f : variant.s;
        variant.v = (variant.v > 1.0f) ? 1.0f : variant.v;

        colors[i] = hsva_to_rgba(variant);
    }
}

// Generate gradient between two colors
void color_gradient(color_t start, color_t end, color_t* colors, int count) {
    if (count <= 0) return;

    for (int i = 0; i < count; i++) {
        float t = (count == 1) ? 0.5f : (float)i / (count - 1);

        // Linear interpolation in RGB space
        colors[i].r = (uint8_t)(start.r + t * (end.r - start.r));
        colors[i].g = (uint8_t)(start.g + t * (end.g - start.g));
        colors[i].b = (uint8_t)(start.b + t * (end.b - start.b));
        colors[i].a = (uint8_t)(start.a + t * (end.a - start.a));
    }
}

// Gamma correction for sRGB
static float gamma_correct(float value) {
    if (value <= 0.04045f) {
        return value / 12.92f;
    } else {
        return powf((value + 0.055f) / 1.055f, 2.4f);
    }
}

// Inverse gamma correction for sRGB
static float inverse_gamma_correct(float value) {
    if (value <= 0.0031308f) {
        return 12.92f * value;
    } else {
        return 1.055f * powf(value, 1.0f / 2.4f) - 0.055f;
    }
}

// Convert RGBA to XYZ with custom white point
color_xyz_t rgba_to_xyz_custom(color_t rgba, float wx, float wy, float wz) {
    color_xyz_t xyz;

    // Convert to 0-1 range and apply gamma correction
    float r = gamma_correct(rgba.r / 255.0f);
    float g = gamma_correct(rgba.g / 255.0f);
    float b = gamma_correct(rgba.b / 255.0f);

    // sRGB to XYZ matrix (D65 illuminant)
    // Then scale by custom white point
    float x = (0.4124564f * r + 0.3575761f * g + 0.1804375f * b) * wx;
    float y = (0.2126729f * r + 0.7151522f * g + 0.0721750f * b) * wy;
    float z = (0.0193339f * r + 0.1191920f * g + 0.9503041f * b) * wz;

    xyz.x = x;
    xyz.y = y;
    xyz.z = z;
    xyz.a = rgba.a / 255.0f;

    return xyz;
}

// XYZ to LAB conversion helper
static float xyz_to_lab_f(float t) {
    const float delta = 6.0f / 29.0f;
    const float delta_cubed = delta * delta * delta;

    if (t > delta_cubed) {
        return powf(t, 1.0f / 3.0f);
    } else {
        return t / (3.0f * delta * delta) + 4.0f / 29.0f;
    }
}

// Convert RGBA to LAB with custom white point
color_lab_t rgba_to_lab_custom(color_t rgba, float wx, float wy, float wz) {
    color_lab_t lab;

    // First convert to XYZ
    color_xyz_t xyz = rgba_to_xyz_custom(rgba, wx, wy, wz);

    // Normalize by white point
    float xn = xyz.x / wx;
    float yn = xyz.y / wy;
    float zn = xyz.z / wz;

    // Convert to LAB
    float fx = xyz_to_lab_f(xn);
    float fy = xyz_to_lab_f(yn);
    float fz = xyz_to_lab_f(zn);

    lab.l = 116.0f * fy - 16.0f;
    lab.a = 500.0f * (fx - fy);
    lab.b = 200.0f * (fy - fz);
    lab.alpha = rgba.a / 255.0f;

    return lab;
}

// Delta E CIE76 (simple Euclidean distance in LAB)
float color_delta_e_76(color_lab_t a, color_lab_t b) {
    float dl = a.l - b.l;
    float da = a.a - b.a;
    float db = a.b - b.b;

    return sqrtf(dl*dl + da*da + db*db);
}

// Delta E CIE94 (improved formula with weighting)
float color_delta_e_94(color_lab_t a, color_lab_t b) {
    float dl = a.l - b.l;
    float da = a.a - b.a;
    float db = a.b - b.b;

    float c1 = sqrtf(a.a * a.a + a.b * a.b);
    float c2 = sqrtf(b.a * b.a + b.b * b.b);
    float dc = c1 - c2;

    float dh_squared = da*da + db*db - dc*dc;
    float dh = (dh_squared < 0) ? 0 : sqrtf(dh_squared);

    // Weighting factors for CIE94
    float kl = 1.0f;
    float kc = 1.0f;
    float kh = 1.0f;

    float sl = 1.0f;
    float sc = 1.0f + 0.045f * c1;
    float sh = 1.0f + 0.015f * c1;

    float dl_term = dl / (kl * sl);
    float dc_term = dc / (kc * sc);
    float dh_term = dh / (kh * sh);

    return sqrtf(dl_term*dl_term + dc_term*dc_term + dh_term*dh_term);
}

// Delta E CIEDE2000 (most perceptually accurate)
float color_delta_e_2000(color_lab_t a, color_lab_t b) {
    float l1 = a.l, a1 = a.a, b1 = a.b;
    float l2 = b.l, a2 = b.a, b2 = b.b;

    float lbar = (l1 + l2) / 2.0f;
    float c1 = sqrtf(a1*a1 + b1*b1);
    float c2 = sqrtf(a2*a2 + b2*b2);
    float cbar = (c1 + c2) / 2.0f;

    float cbar7 = powf(cbar, 7.0f);
    float g = 0.5f * (1.0f - sqrtf(cbar7 / (cbar7 + powf(25.0f, 7.0f))));

    float ap1 = (1.0f + g) * a1;
    float ap2 = (1.0f + g) * a2;
    float cp1 = sqrtf(ap1*ap1 + b1*b1);
    float cp2 = sqrtf(ap2*ap2 + b2*b2);

    float hp1 = (b1 == 0 && ap1 == 0) ? 0 : atan2f(b1, ap1) * 180.0f / M_PI;
    float hp2 = (b2 == 0 && ap2 == 0) ? 0 : atan2f(b2, ap2) * 180.0f / M_PI;

    if (hp1 < 0) hp1 += 360.0f;
    if (hp2 < 0) hp2 += 360.0f;

    float dl = l2 - l1;
    float dc = cp2 - cp1;
    float dhp = 0;

    if (cp1 * cp2 != 0) {
        dhp = hp2 - hp1;
        if (dhp > 180.0f) dhp -= 360.0f;
        if (dhp < -180.0f) dhp += 360.0f;
    }

    float dh = 2.0f * sqrtf(cp1 * cp2) * sinf(dhp * M_PI / 360.0f);

    float cpbar = (cp1 + cp2) / 2.0f;
    float hpbar = 0;

    if (cp1 * cp2 != 0) {
        hpbar = (hp1 + hp2) / 2.0f;
        if (fabsf(hp1 - hp2) > 180.0f) {
            if (hpbar < 180.0f) hpbar += 180.0f;
            else hpbar -= 180.0f;
        }
    }

    float t = 1.0f - 0.17f * cosf((hpbar - 30.0f) * M_PI / 180.0f) +
              0.24f * cosf(2.0f * hpbar * M_PI / 180.0f) +
              0.32f * cosf((3.0f * hpbar + 6.0f) * M_PI / 180.0f) -
              0.20f * cosf((4.0f * hpbar - 63.0f) * M_PI / 180.0f);

    float dt = 30.0f * expf(-powf((hpbar - 275.0f) / 25.0f, 2.0f));
    float cpbar7 = powf(cpbar, 7.0f);
    float rc = 2.0f * sqrtf(cpbar7 / (cpbar7 + powf(25.0f, 7.0f)));

    float sl = 1.0f + (0.015f * powf(lbar - 50.0f, 2.0f)) / sqrtf(20.0f + powf(lbar - 50.0f, 2.0f));
    float sc = 1.0f + 0.045f * cpbar;
    float sh = 1.0f + 0.015f * cpbar * t;
    float rt = -sinf(2.0f * dt * M_PI / 180.0f) * rc;

    float kl = 1.0f, kc = 1.0f, kh = 1.0f;

    float dl_term = dl / (kl * sl);
    float dc_term = dc / (kc * sc);
    float dh_term = dh / (kh * sh);

    return sqrtf(dl_term*dl_term + dc_term*dc_term + dh_term*dh_term + rt * dc_term * dh_term);
}

// Levels adjustment: black point, white point, gamma
color_t color_levels(color_t color, float black_point, float white_point, float gamma) {
    color_t result;

    // Normalize inputs to 0-1 range
    float r = color.r / 255.0f;
    float g = color.g / 255.0f;
    float b = color.b / 255.0f;

    // Apply levels adjustment to each channel
    r = _CLAMP_FLOAT((r - black_point) / (white_point - black_point));
    g = _CLAMP_FLOAT((g - black_point) / (white_point - black_point));
    b = _CLAMP_FLOAT((b - black_point) / (white_point - black_point));

    // Apply gamma correction
    r = powf(r, 1.0f / gamma);
    g = powf(g, 1.0f / gamma);
    b = powf(b, 1.0f / gamma);

    result.r = _CLAMP_UINT8(r * 255.0f);
    result.g = _CLAMP_UINT8(g * 255.0f);
    result.b = _CLAMP_UINT8(b * 255.0f);
    result.a = color.a;

    return result;
}

// Curves adjustment using lookup tables
color_t color_curves(color_t color, float* curve_r, float* curve_g, float* curve_b) {
    color_t result;

    // Apply curves (assuming curves are 256-element arrays)
    result.r = _CLAMP_UINT8(curve_r[color.r] * 255.0f);
    result.g = _CLAMP_UINT8(curve_g[color.g] * 255.0f);
    result.b = _CLAMP_UINT8(curve_b[color.b] * 255.0f);
    result.a = color.a;

    return result;
}

// Shadow/Highlight adjustment
color_t color_shadow_highlight(color_t color, float shadow, float highlight) {
    color_t result;

    // Convert to 0-1 range
    float r = color.r / 255.0f;
    float g = color.g / 255.0f;
    float b = color.b / 255.0f;

    // Calculate luminance
    float lum = 0.299f * r + 0.587f * g + 0.114f * b;

    // Apply shadow/highlight adjustments
    float shadow_factor = 1.0f + shadow * (1.0f - lum);
    float highlight_factor = 1.0f + highlight * lum;

    r *= shadow_factor * highlight_factor;
    g *= shadow_factor * highlight_factor;
    b *= shadow_factor * highlight_factor;

    result.r = _CLAMP_UINT8(r * 255.0f);
    result.g = _CLAMP_UINT8(g * 255.0f);
    result.b = _CLAMP_UINT8(b * 255.0f);
    result.a = color.a;

    return result;
}

// Color balance adjustment
color_t color_color_balance(color_t color, float cyan_red, float magenta_green, float yellow_blue) {
    color_t result;

    // Convert to 0-1 range
    float r = color.r / 255.0f;
    float g = color.g / 255.0f;
    float b = color.b / 255.0f;

    // Apply color balance adjustments
    r += cyan_red;
    g += magenta_green;
    b += yellow_blue;

    result.r = _CLAMP_UINT8(r * 255.0f);
    result.g = _CLAMP_UINT8(g * 255.0f);
    result.b = _CLAMP_UINT8(b * 255.0f);
    result.a = color.a;

    return result;
}

// Vibrance adjustment (smart saturation)
color_t color_vibrance(color_t color, float amount) {
    color_t result;

    // Convert to HSV for saturation manipulation
    color_hsva_t hsv = rgba_to_hsva(color);

    // Calculate existing saturation level
    float sat_factor = 1.0f - hsv.s;

    // Apply vibrance (more effect on less saturated colors)
    hsv.s += amount * sat_factor;
    hsv.s = _CLAMP_FLOAT(hsv.s);

    result = hsva_to_rgba(hsv);
    result.a = color.a;

    return result;
}

// Selective color adjustment
color_t color_selective_color(color_t color, int channel, float cyan, float magenta, float yellow, float black) {
    color_t result = color;

    // Convert to CMY for selective color work
    float c = 1.0f - color.r / 255.0f;
    float m = 1.0f - color.g / 255.0f;
    float y = 1.0f - color.b / 255.0f;

    // Determine which color channel to adjust based on dominant color
    float max_cmy = (c > m) ? ((c > y) ? c : y) : ((m > y) ? m : y);

    // Apply selective adjustments based on channel
    switch (channel) {
        case 0: // Reds (low cyan)
            if (c < 0.5f) {
                c += cyan * (1.0f - c);
                m += magenta * (1.0f - m);
                y += yellow * (1.0f - y);
            }
            break;
        case 1: // Yellows (high yellow)
            if (y > 0.5f) {
                c += cyan * (1.0f - c);
                m += magenta * (1.0f - m);
                y += yellow * (1.0f - y);
            }
            break;
        case 2: // Greens (high yellow, low magenta)
            if (y > 0.3f && m < 0.5f) {
                c += cyan * (1.0f - c);
                m += magenta * (1.0f - m);
                y += yellow * (1.0f - y);
            }
            break;
        case 3: // Cyans (high cyan)
            if (c > 0.5f) {
                c += cyan * (1.0f - c);
                m += magenta * (1.0f - m);
                y += yellow * (1.0f - y);
            }
            break;
        case 4: // Blues (high cyan, high magenta)
            if (c > 0.3f && m > 0.3f) {
                c += cyan * (1.0f - c);
                m += magenta * (1.0f - m);
                y += yellow * (1.0f - y);
            }
            break;
        case 5: // Magentas (high magenta)
            if (m > 0.5f) {
                c += cyan * (1.0f - c);
                m += magenta * (1.0f - m);
                y += yellow * (1.0f - y);
            }
            break;
    }

    // Apply black adjustment
    float k = black;
    c = _CLAMP_FLOAT(c + k);
    m = _CLAMP_FLOAT(m + k);
    y = _CLAMP_FLOAT(y + k);

    // Convert back to RGB
    result.r = _CLAMP_UINT8((1.0f - c) * 255.0f);
    result.g = _CLAMP_UINT8((1.0f - m) * 255.0f);
    result.b = _CLAMP_UINT8((1.0f - y) * 255.0f);

    return result;
}

// Quantize color to fewer bits per channel
color_t color_quantize(color_t color, int bits_per_channel) {
    color_t result;

    int levels = (1 << bits_per_channel) - 1;
    float scale = 255.0f / levels;

    result.r = (uint8_t)((color.r / (int)scale) * scale);
    result.g = (uint8_t)((color.g / (int)scale) * scale);
    result.b = (uint8_t)((color.b / (int)scale) * scale);
    result.a = color.a;

    return result;
}

// Posterize to specific number of levels
color_t color_posterize(color_t color, int levels) {
    color_t result;

    float scale = 255.0f / (levels - 1);

    result.r = (uint8_t)((int)(color.r / scale) * scale);
    result.g = (uint8_t)((int)(color.g / scale) * scale);
    result.b = (uint8_t)((int)(color.b / scale) * scale);
    result.a = color.a;

    return result;
}

// Find closest color in palette
static int find_closest_color(color_t color, color_t* palette, int palette_size) {
    int closest = 0;
    float min_distance = color_distance(color, palette[0]);

    for (int i = 1; i < palette_size; i++) {
        float distance = color_distance(color, palette[i]);
        if (distance < min_distance) {
            min_distance = distance;
            closest = i;
        }
    }

    return closest;
}

// Floyd-Steinberg dithering
color_t color_dither_floyd_steinberg(color_t color, color_t* palette, int palette_size, int x, int y) {
    // Find closest palette color
    int closest_idx = find_closest_color(color, palette, palette_size);
    color_t closest = palette[closest_idx];

    // Calculate error (this would normally be distributed to neighboring pixels)
    // For a single pixel function, we just return the closest color
    return closest;
}

// Ordered dithering using Bayer matrix
color_t color_dither_ordered(color_t color, color_t* palette, int palette_size, int x, int y) {
    // 4x4 Bayer matrix
    static const int bayer_matrix[4][4] = {
        { 0,  8,  2, 10},
        {12,  4, 14,  6},
        { 3, 11,  1,  9},
        {15,  7, 13,  5}
    };

    // Get threshold from Bayer matrix
    int threshold = bayer_matrix[y % 4][x % 4];
    float dither_value = (threshold / 15.0f - 0.5f) * 32.0f; // Scale dither amount

    // Apply dither to color
    color_t dithered;
    dithered.r = _CLAMP_UINT8(color.r + dither_value);
    dithered.g = _CLAMP_UINT8(color.g + dither_value);
    dithered.b = _CLAMP_UINT8(color.b + dither_value);
    dithered.a = color.a;

    // Find closest palette color
    int closest_idx = find_closest_color(dithered, palette, palette_size);
    return palette[closest_idx];
}

// Protanopia (red-blind) - affects L-cones
// Uses Brettel, Viénot and Mollon transformation matrix
color_t color_protanopia(color_t color) {
    // Transformation matrix for protanopia
    // Row 1: [0.567, 0.433, 0.000]
    // Row 2: [0.558, 0.442, 0.000]
    // Row 3: [0.000, 0.242, 0.758]

    int r = (567 * color.r + 433 * color.g) / 1000;
    int g = (558 * color.r + 442 * color.g) / 1000;
    int b = (242 * color.g + 758 * color.b) / 1000;

    color_t result;
    result.r = _CLAMP_UINT8(r);
    result.g = _CLAMP_UINT8(g);
    result.b = _CLAMP_UINT8(b);
    result.a = color.a;  // Preserve alpha

    return result;
}

// Deuteranopia (green-blind) - affects M-cones
// Uses Brettel, Viénot and Mollon transformation matrix
color_t color_deuteranopia(color_t color) {
    // Transformation matrix for deuteranopia
    // Row 1: [0.625, 0.375, 0.000]
    // Row 2: [0.700, 0.300, 0.000]
    // Row 3: [0.000, 0.300, 0.700]

    int r = (625 * color.r + 375 * color.g) / 1000;
    int g = (700 * color.r + 300 * color.g) / 1000;
    int b = (300 * color.g + 700 * color.b) / 1000;

    color_t result;
    result.r = _CLAMP_UINT8(r);
    result.g = _CLAMP_UINT8(g);
    result.b = _CLAMP_UINT8(b);
    result.a = color.a;  // Preserve alpha

    return result;
}

// Tritanopia (blue-blind) - affects S-cones
// Uses Brettel, Viénot and Mollon transformation matrix
color_t color_tritanopia(color_t color) {
    // Transformation matrix for tritanopia
    // Row 1: [0.950, 0.050, 0.000]
    // Row 2: [0.000, 0.433, 0.567]
    // Row 3: [0.000, 0.475, 0.525]

    int r = (950 * color.r + 50 * color.g) / 1000;
    int g = (433 * color.g + 567 * color.b) / 1000;
    int b = (475 * color.g + 525 * color.b) / 1000;

    color_t result;
    result.r = _CLAMP_UINT8(r);
    result.g = _CLAMP_UINT8(g);
    result.b = _CLAMP_UINT8(b);
    result.a = color.a;  // Preserve alpha

    return result;
}

// Achromatopsia (complete color blindness) - monochromacy
// Converts to grayscale using luminance formula
color_t color_achromatopsia(color_t color) {
    // Standard luminance formula: 0.299*R + 0.587*G + 0.114*B
    // Using integer arithmetic: (299*R + 587*G + 114*B) / 1000

    int luminance = (299 * color.r + 587 * color.g + 114 * color.b) / 1000;
    uint8_t gray = _CLAMP_UINT8(luminance);

    color_t result;
    result.r = gray;
    result.g = gray;
    result.b = gray;
    result.a = color.a;  // Preserve alpha

    return result;
}

// Helper function to calculate relative luminance according to WCAG
// Uses the sRGB color space formula
static float relative_luminance(color_t color) {
    // Convert RGB values to 0-1 range
    float r = color.r / 255.0f;
    float g = color.g / 255.0f;
    float b = color.b / 255.0f;

    // Apply gamma correction (sRGB to linear RGB)
    r = (r <= 0.03928f) ? r / 12.92f : powf((r + 0.055f) / 1.055f, 2.4f);
    g = (g <= 0.03928f) ? g / 12.92f : powf((g + 0.055f) / 1.055f, 2.4f);
    b = (b <= 0.03928f) ? b / 12.92f : powf((b + 0.055f) / 1.055f, 2.4f);

    // Calculate relative luminance using ITU-R BT.709 coefficients
    return 0.2126f * r + 0.7152f * g + 0.0722f * b;
}

// Calculate WCAG contrast ratio between two colors
float color_contrast_ratio(color_t a, color_t b) {
    float lum_a = relative_luminance(a);
    float lum_b = relative_luminance(b);

    // Ensure lighter color is in numerator
    float lighter = (lum_a > lum_b) ? lum_a : lum_b;
    float darker = (lum_a > lum_b) ? lum_b : lum_a;

    // WCAG contrast ratio formula: (L1 + 0.05) / (L2 + 0.05)
    return (lighter + 0.05f) / (darker + 0.05f);
}

// Check if color combination meets WCAG AA compliance
// AA requires contrast ratio of at least 4.5:1 for normal text, 3:1 for large text
int color_wcag_aa_compliant(color_t fg, color_t bg) {
    float ratio = color_contrast_ratio(fg, bg);
    return ratio >= 4.5f;
}

// Check if color combination meets WCAG AAA compliance
// AAA requires contrast ratio of at least 7:1 for normal text, 4.5:1 for large text
int color_wcag_aaa_compliant(color_t fg, color_t bg) {
    float ratio = color_contrast_ratio(fg, bg);
    return ratio >= 7.0f;
}

// Find the closest color in a palette to a target color
color_t color_match_closest(color_t target, color_t* palette, int palette_size) {
    if (palette_size <= 0 || palette == NULL) {
        return target;  // Return target if no palette provided
    }

    color_t closest = palette[0];
    float min_distance = color_distance(target, palette[0]);

    for (int i = 1; i < palette_size; i++) {
        float distance = color_distance(target, palette[i]);
        if (distance < min_distance) {
            min_distance = distance;
            closest = palette[i];
        }
    }

    return closest;
}

// Calculate color similarity as a normalized value (0.0 = identical, 1.0 = maximum difference)
float color_similarity(color_t a, color_t b) {
    // Use Euclidean distance in RGB space, normalized to 0-1 range
    float dr = (a.r - b.r) / 255.0f;
    float dg = (a.g - b.g) / 255.0f;
    float db = (a.b - b.b) / 255.0f;

    // Calculate distance and normalize by maximum possible distance (sqrt(3))
    float distance = sqrtf(dr * dr + dg * dg + db * db);
    return distance / sqrtf(3.0f);
}

// Check if two colors are similar within a given threshold
// threshold: 0.0 (identical) to 1.0 (maximum difference)
int color_is_similar(color_t a, color_t b, float threshold) {
    return color_similarity(a, b) <= threshold;
}

#define _C2F(V) ((float)(V) / 255.0f)
#define _F2C(V) ((uint8_t)((V) * 255.0f + 0.5f))

// Lift-Gamma-Gain color grading (common in film/video post-production)
// lift: affects shadows/blacks, gamma: affects midtones, gain: affects highlights/whites
color_t color_lift_gamma_gain(color_t color, color_rgbaf_t lift, color_rgbaf_t gamma, color_rgbaf_t gain) {
    // Convert to 0-1 range
    float r = _C2F(color.r);
    float g = _C2F(color.g);
    float b = _C2F(color.b);

    // Apply lift (additive in shadows)
    r = r + lift.r * (1.0f - r);
    g = g + lift.g * (1.0f - g);
    b = b + lift.b * (1.0f - b);

    // Apply gamma (power function for midtones)
    if (gamma.r != 0.0f) r = powf(r, 1.0f / gamma.r);
    if (gamma.g != 0.0f) g = powf(g, 1.0f / gamma.g);
    if (gamma.b != 0.0f) b = powf(b, 1.0f / gamma.b);

    // Apply gain (multiplicative in highlights)
    r *= gain.r;
    g *= gain.g;
    b *= gain.b;

    color_t result;
    result.r = _F2C(r);
    result.g = _F2C(g);
    result.b = _F2C(b);
    result.a = color.a;  // Preserve alpha

    return result;
}

// Shadow-Midtone-Highlight color grading (alternative approach)
// Uses luminance-based weighting to apply corrections
color_t color_shadow_midtone_highlight(color_t color, color_rgbaf_t shadow, color_rgbaf_t midtone, color_rgbaf_t highlight) {
    // Convert to 0-1 range
    float r = _C2F(color.r);
    float g = _C2F(color.g);
    float b = _C2F(color.b);

    // Calculate luminance for weighting
    float luminance = 0.299f * r + 0.587f * g + 0.114f * b;

    // Create weighting functions for shadow, midtone, and highlight
    // Shadow weight: stronger in dark areas
    float shadow_weight = 1.0f - powf(luminance, 2.0f);

    // Midtone weight: bell curve centered at 0.5
    float midtone_weight = 4.0f * luminance * (1.0f - luminance);

    // Highlight weight: stronger in bright areas
    float highlight_weight = powf(luminance, 2.0f);

    // Apply weighted color corrections
    r += shadow.r * shadow_weight + midtone.r * midtone_weight + highlight.r * highlight_weight;
    g += shadow.g * shadow_weight + midtone.g * midtone_weight + highlight.g * highlight_weight;
    b += shadow.b * shadow_weight + midtone.b * midtone_weight + highlight.b * highlight_weight;

    color_t result;
    result.r = _F2C(r);
    result.g = _F2C(g);
    result.b = _F2C(b);
    result.a = color.a;  // Preserve alpha

    return result;
}

// Helper function to apply 3x3 color space transformation matrix
static color_t apply_color_matrix(color_t color, const float matrix[3][3]) {
    // Convert to 0-1 range
    float r = _C2F(color.r);
    float g = _C2F(color.g);
    float b = _C2F(color.b);

    // Apply gamma correction (sRGB to linear) before color space conversion
    r = (r <= 0.04045f) ? r / 12.92f : powf((r + 0.055f) / 1.055f, 2.4f);
    g = (g <= 0.04045f) ? g / 12.92f : powf((g + 0.055f) / 1.055f, 2.4f);
    b = (b <= 0.04045f) ? b / 12.92f : powf((b + 0.055f) / 1.055f, 2.4f);

    // Apply matrix transformation
    float new_r = matrix[0][0] * r + matrix[0][1] * g + matrix[0][2] * b;
    float new_g = matrix[1][0] * r + matrix[1][1] * g + matrix[1][2] * b;
    float new_b = matrix[2][0] * r + matrix[2][1] * g + matrix[2][2] * b;

    // Apply inverse gamma correction (linear to sRGB)
    new_r = (new_r <= 0.0031308f) ? new_r * 12.92f : 1.055f * powf(new_r, 1.0f / 2.4f) - 0.055f;
    new_g = (new_g <= 0.0031308f) ? new_g * 12.92f : 1.055f * powf(new_g, 1.0f / 2.4f) - 0.055f;
    new_b = (new_b <= 0.0031308f) ? new_b * 12.92f : 1.055f * powf(new_b, 1.0f / 2.4f) - 0.055f;

    color_t result;
    result.r = _F2C(new_r);
    result.g = _F2C(new_g);
    result.b = _F2C(new_b);
    result.a = color.a;  // Preserve alpha

    return result;
}

// Convert Rec.709 (standard HD) to Rec.2020 (ultra HD/HDR)
// Used in broadcast and streaming for HDR content
color_t color_rec709_to_rec2020(color_t color) {
    // Transformation matrix from Rec.709 to Rec.2020
    // Based on ITU-R BT.2087 standard
    static const float matrix[3][3] = {
        {0.627404f, 0.329283f, 0.043313f},
        {0.069097f, 0.919540f, 0.011362f},
        {0.016391f, 0.088013f, 0.895595f}
    };

    return apply_color_matrix(color, matrix);
}

// Convert ProPhoto RGB to sRGB
// ProPhoto RGB has a much wider gamut, commonly used in professional photography
color_t color_prophoto_to_srgb(color_t color) {
    // Convert to 0-1 range
    float r = _C2F(color.r);
    float g = _C2F(color.g);
    float b = _C2F(color.b);

    // Apply ProPhoto RGB gamma correction (gamma 1.8) to linear
    r = powf(r, 1.8f);
    g = powf(g, 1.8f);
    b = powf(b, 1.8f);

    // ProPhoto RGB to XYZ transformation matrix
    float x = 0.7976749f * r + 0.1351917f * g + 0.0313534f * b;
    float y = 0.2880402f * r + 0.7118741f * g + 0.0000857f * b;
    float z = 0.0000000f * r + 0.0000000f * g + 0.8252100f * b;

    // XYZ to sRGB transformation matrix
    float new_r = 3.2404542f * x - 1.5371385f * y - 0.4985314f * z;
    float new_g = -0.9692660f * x + 1.8760108f * y + 0.0415560f * z;
    float new_b = 0.0556434f * x - 0.2040259f * y + 1.0572252f * z;

    // Apply sRGB gamma correction (linear to sRGB)
    new_r = (new_r <= 0.0031308f) ? new_r * 12.92f : 1.055f * powf(new_r, 1.0f / 2.4f) - 0.055f;
    new_g = (new_g <= 0.0031308f) ? new_g * 12.92f : 1.055f * powf(new_g, 1.0f / 2.4f) - 0.055f;
    new_b = (new_b <= 0.0031308f) ? new_b * 12.92f : 1.055f * powf(new_b, 1.0f / 2.4f) - 0.055f;

    color_t result;
    result.r = _F2C(new_r);
    result.g = _F2C(new_g);
    result.b = _F2C(new_b);
    result.a = color.a;  // Preserve alpha

    return result;
}

// Convert Adobe RGB to sRGB
// Adobe RGB has wider gamut than sRGB, commonly used in print and professional workflows
color_t color_adobe_rgb_to_srgb(color_t color) {
    // Convert to 0-1 range
    float r = _C2F(color.r);
    float g = _C2F(color.g);
    float b = _C2F(color.b);

    // Apply Adobe RGB gamma correction (gamma 2.2) to linear
    r = powf(r, 2.2f);
    g = powf(g, 2.2f);
    b = powf(b, 2.2f);

    // Adobe RGB to XYZ transformation matrix
    float x = 0.5767309f * r + 0.1855540f * g + 0.1881852f * b;
    float y = 0.2973769f * r + 0.6273491f * g + 0.0752741f * b;
    float z = 0.0270343f * r + 0.0706872f * g + 0.9911085f * b;

    // XYZ to sRGB transformation matrix
    float new_r = 3.2404542f * x - 1.5371385f * y - 0.4985314f * z;
    float new_g = -0.9692660f * x + 1.8760108f * y + 0.0415560f * z;
    float new_b = 0.0556434f * x - 0.2040259f * y + 1.0572252f * z;

    // Apply sRGB gamma correction (linear to sRGB)
    new_r = (new_r <= 0.0031308f) ? new_r * 12.92f : 1.055f * powf(new_r, 1.0f / 2.4f) - 0.055f;
    new_g = (new_g <= 0.0031308f) ? new_g * 12.92f : 1.055f * powf(new_g, 1.0f / 2.4f) - 0.055f;
    new_b = (new_b <= 0.0031308f) ? new_b * 12.92f : 1.055f * powf(new_b, 1.0f / 2.4f) - 0.055f;

    color_t result;
    result.r = _F2C(new_r);
    result.g = _F2C(new_g);
    result.b = _F2C(new_b);
    result.a = color.a;  // Preserve alpha

    return result;
}

// Fast grayscale conversion using integer arithmetic only
// Uses approximate luminance weights for speed
color_t color_fast_grayscale(color_t color) {
    // Fast integer approximation: (R + G + B) / 3
    // Or slightly better: (R*77 + G*151 + B*28) >> 8 (approximates 0.299, 0.587, 0.114)
    uint8_t gray = (uint8_t)((77 * color.r + 151 * color.g + 28 * color.b) >> 8);

    color_t result;
    result.r = gray;
    result.g = gray;
    result.b = gray;
    result.a = color.a;  // Preserve alpha

    return result;
}

// Fast sepia tone effect using integer arithmetic
// Creates warm brown tones typical of old photographs
color_t color_fast_sepia(color_t color) {
    // Calculate sepia values using integer arithmetic
    // Standard sepia transformation with bit shifting for speed
    int r = (color.r * 393 + color.g * 769 + color.b * 189) >> 10;  // / 1024
    int g = (color.r * 349 + color.g * 686 + color.b * 168) >> 10;  // / 1024
    int b = (color.r * 272 + color.g * 534 + color.b * 131) >> 10;  // / 1024

    color_t result;
    result.r = _CLAMP_UINT8(r);
    result.g = _CLAMP_UINT8(g);
    result.b = _CLAMP_UINT8(b);
    result.a = color.a;  // Preserve alpha

    return result;
}

// Fast color inversion using bitwise operations
// Simply inverts each color component
color_t color_fast_invert(color_t color) {
    color_t result;
    result.r = 255 - color.r;  // Equivalent to: color.r ^ 0xFF
    result.g = 255 - color.g;  // Equivalent to: color.g ^ 0xFF
    result.b = 255 - color.b;  // Equivalent to: color.b ^ 0xFF
    result.a = color.a;        // Preserve alpha

    return result;
}
#endif