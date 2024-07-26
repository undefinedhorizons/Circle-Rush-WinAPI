#include "Render.h"

#define BITS_ALPHA 24
#define BITS_RED 16
#define BITS_GREEN 8
#define BITS_BLUE 0
#define BYTES_PER_PIXEL 4
#define BUFFER_PITCH (SCREEN_WIDTH * BYTES_PER_PIXEL)

// converts rgb color to uint32_t bgra color
static uint32_t rgba_to_int(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    uint32_t color = b << BITS_BLUE;
    color += r << BITS_RED;
    color += g << BITS_GREEN;
    color += a << BITS_ALPHA;
    return color;
}

int Render::getWidth() {
    return SCREEN_WIDTH;
}

int Render::getHeigth() {
    return SCREEN_HEIGHT;
}

struct Point Render::getCenter() {
    return {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
}

void Render::setPixel(int x, int y, const RGBAColor& color) {

    // clipping
    if (x < 0 || x > SCREEN_WIDTH || y < 0 || y > SCREEN_HEIGHT)
        return;

    // convert (u8, u8, u8) rgb color to u32 representation
    uint32_t raw_color = rgba_to_int(color.red, color.green, color.blue, color.alpha);

    uint8_t* row = (uint8_t*)buffer + x * BYTES_PER_PIXEL + y * BUFFER_PITCH;
    uint32_t* pixel = (uint32_t*)row;
    *pixel = raw_color;
}

void Render::fillRectangle(const Rect& rect, const RGBAColor& color) {
    int minX = rect.x;
    int minY = rect.y;
    int maxX = rect.x + rect.width;
    int maxY = rect.y + rect.height;

    // clipping
    if (minX < 0)
        minX = 0;
    if (minY < 0)
        minY = 0;
    if (maxX > SCREEN_WIDTH)
        maxX = SCREEN_WIDTH;
    if (maxY > SCREEN_HEIGHT)
        maxY = SCREEN_HEIGHT;

    // convert (u8, u8, u8) rgb color to u32 representation
    uint32_t raw_color = rgba_to_int(color.red, color.green, color.blue, color.alpha);

    uint8_t* row = (uint8_t*)buffer + minX * BYTES_PER_PIXEL + minY * BUFFER_PITCH;

    for (int y = minY; y < maxY; y++) {
        uint32_t* pixel = (uint32_t*)row;
        for (int x = minX; x < maxX; x++) {
            *pixel++ = raw_color;
        }
        row += BUFFER_PITCH;
    }
}

void Render::fillCircle(int radius, const Point& center, const RGBAColor& color) {
    for (int y = -radius; y <= radius; y++)
        for (int x = -radius; x <= radius; x++)
            if (x * x + y * y < radius * radius + radius)
                setPixel(center.x + x, center.y + y, color);
}

#define CHAR_WIDTH 8
#define CHAR_HEIGHT 8
#define FONT_SCALE 4

// https:// jared.geek.nz/2014/01/custom-fonts-for-microcontrollers/
#include "fonts/HUNTER_font.h"

void Render::DrawChar(unsigned char c, int x, int y, const RGBAColor& color) {
    if (c < ' ')
        c = 0;
    else
        c -= ' ';
    const unsigned char* chr = font[c];

    // Draw pixels
    for (int j = 0; j < CHAR_WIDTH; j++)
        for (int i = 0; i < CHAR_HEIGHT; i++)
            if (chr[j] & (1 << i))
                for (int m = 0; m < FONT_SCALE; m++)
                    for (int n = 0; n < FONT_SCALE; n++)
                        setPixel(x + j * FONT_SCALE + m, y + i * FONT_SCALE + n, color);
}

void Render::DrawString(const char* str, int x, int y, const RGBAColor& color) {
    while (*str) {
        DrawChar(*str++, x, y, color);
        x += CHAR_WIDTH * FONT_SCALE;
    }
}

