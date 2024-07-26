#include <stdio.h>

#include "Board.h"


void Board::draw() {
    render.fillRectangle({0, 0, render.getWidth(), render.getHeight()}, BOARD_COLOR);

    render.fillCircle(100, render.getCenter(), BOARD_COLOR2);

    //render.DrawChar('1', 10, 10, FONT_COLOR);
    char str[64] = {0};
    snprintf(str, 64, "SCORE: %03d", score);

    render.DrawString(str, 10, 10, FONT_COLOR);
}