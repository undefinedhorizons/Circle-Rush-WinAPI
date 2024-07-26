#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


#include <mutex>
#include <vector>

#include "Render.h"

struct Mark {
    int radius;
    struct Point point;
};

class Pinwheel {

    const int CIRCLE_RADIUS = 20;
    const int CIRCLE_DISTANCE = 100;
    const struct RGBAColor CIRCLE_COLOR = {255, 255, 255, 0};
    const struct RGBAColor CIRCLE_COLOR2 = {255, 255, 255, 0};
    const float REFRESH_TIME = 0.005f;
    const float CLICK_TIME = 0.1f;

    const int MARK_RADIUS = 5;
    const float MARK_TIME = 0.1f;

    Render& render;

    float ANGLE_DELTA = M_PI / 180.0f;
    float angle = 0.0f;
    float da = ANGLE_DELTA;
    struct Point center;
    std::vector<Mark> marks;
    std::mutex mutex;

public:
    struct Point pt1;
    struct Point pt2;

    Pinwheel(Render& render);
    void draw();
    void act(float dt);

};
