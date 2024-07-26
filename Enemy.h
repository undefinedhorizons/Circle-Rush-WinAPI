#pragma once

#include "Render.h"
#include <random>
class Enemy
{
public:
    const int BOX_SIZE = 34;
    const struct RGBAColor BOX_COLOR = { 0, 0, 0, 255 };
    const float ENEMY_SPEED = 0.5;
    const float REFRESH_TIME = 0.005;
    const std::pair<int, int> SPAWN_BOUNDS = {SCREEN_HEIGHT / 4, 3 * SCREEN_HEIGHT / 4};
    Rect rect;
    Render& render;

    Enemy(Render& render) : render{render} {
        rect.height = BOX_SIZE;
        rect.width = BOX_SIZE;
        rect.x = 0;
        rect.y = SCREEN_HEIGHT / 2;
        
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist(SPAWN_BOUNDS.first, SPAWN_BOUNDS.second);
        rect.y = dist(rng);
    }

    void act(float dt)
    {
        static float refresh_time = 0.;
        refresh_time += dt;

        if (refresh_time >= REFRESH_TIME) {

            refresh_time = 0.;

            if (rect.x < SCREEN_WIDTH) {
                rect.x++;
            }
        }

    }

    void draw() {
        render.fillRectangle(rect, BOX_COLOR);
    }
};

