#pragma once

#include <cstdint>

#include "Engine.h"


struct RGBAColor {
    uint8_t red, green, blue, alpha;
};

struct Point {
    int x, y;
};

struct Rect {
    int x, y, width, height;
};

struct Render {
    int getWidth();
    int getHeigth();

    struct Point getCenter();

    void setPixel(int x, int y, const RGBAColor& color);
    void fillRectangle(const Rect& rect, const RGBAColor& color);
    void fillCircle(int radius, const Point& center, const RGBAColor& color);
    void DrawChar(unsigned char c, int x, int y, const RGBAColor& color);
    void DrawString(const char* str, int x, int y, const RGBAColor& color);
};


