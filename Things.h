#pragma once


#include <mutex>
#include <vector>
#include <random>

#include "Render.h"
#include "Pinwheel.h"


enum ThingType {
    NOTHING,
    BAD,
    GOOD=2
};

struct Thing {
    enum ThingType type;
    struct Point position;
};

class Things {

    const float REFRESH_TIME = 0.005f;
    const int COUNT_MAX = 3;
    const struct RGBAColor BAD_COLOR = {7, 25, 82, 0};
    const struct RGBAColor GOOD_COLOR = {255, 255, 255, 0};
    const int THING_RADIUS = 20;
    
    Render& render;

    int count;

    float min;
    float max;

    std::vector<Thing> array;
    std::mutex mutex;

public:
    Things(Render& render);
    void draw();
    enum ThingType act(float dt, const Pinwheel& pw);
};
