
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <debugapi.h>

#include "Board.h"
#include "Pinwheel.h"
#include "Things.h"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

Render* render;
Board* board;
Pinwheel* pinwheel;
Things* things;

int score = 0;
bool isGameOver = false;

// initialize game data in this function
void initialize()
{
    render = new Render();
    board = new Board(*render);
    pinwheel = new Pinwheel(*render);
    things = new Things(*render);

    isGameOver = false;
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    // OutputDebugString("Update\n");
    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();

    if (is_key_pressed(VK_SPACE) || is_key_pressed(VK_RETURN)) {
        finalize();
        initialize();
    }
        

    if (isGameOver)
        return;
    
    // logic
    switch (things->act(dt, *pinwheel)) {
    case GOOD:
        board->setScore(++score);
        break;

    case BAD:
        isGameOver = true;
        break;

    default:
        break;
    }
    
    pinwheel->act(dt);

}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    board->draw();
    pinwheel->draw();
    things->draw();

    if (isGameOver) {
        auto center = render->getCenter();
        render->DrawString("GAME OVER", center.x - 4*4*8, 3 * render->getHeight() / 4, {7, 25, 82, 0});
    }
       
}

// free game data in this function
void finalize()
{
    delete render;
    delete board ;
    delete pinwheel;
    delete things;
}



