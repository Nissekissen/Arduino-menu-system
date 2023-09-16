#ifndef GAME_H
#define GAME_H

#include "Snake.h"

#define SNAKE_ID 0

class GameHandler
{
private:
    int game;
    Snake *snake;
    U8GLIB_SSD1306_128X64 *u8g;

public:
    GameHandler(){};

    GameHandler(U8GLIB_SSD1306_128X64 *_u8g, int _game)
    {
        u8g = _u8g;
        game = _game;
        snake = new Snake(u8g);
    }

    void init(void)
    {
        switch (game)
        {
        case 0:
            snake->init();
            break;
        }
    }

    void draw(void)
    {
        switch (game)
        {
        case 0:
            snake->draw();
            break;
        }
    }
    void update(void)
    {
        switch (game)
        {
        case 0:
            snake->update();
            break;
        }
    }
    void setGame(int _game)
    {
        game = _game;
    }
};

#endif