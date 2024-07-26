#pragma once

#include "Render.h"


class Board {
    const struct RGBAColor BOARD_COLOR = { 8, 131, 149, 0 };
    const struct RGBAColor BOARD_COLOR2 = { 55, 183, 195, 0 };
    const struct RGBAColor FONT_COLOR = {255, 255, 255, 0};

    Render& render;
    int score;

public:
    Board(Render& render) : render(render), score(0){};
    void draw();
    void setScore(int score) {
        this->score = score;
    };

};

