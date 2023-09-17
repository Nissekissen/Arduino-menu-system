#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Pong.h"
#include "3DCube.h"

#define SNAKE_ID 0

class GameHandler
{
private:
    int game = 0;
    Snake snake;
    Pong pong;
    Cube cube;
    U8GLIB_SSD1306_128X64 *u8g;

public:
    GameHandler(){};

    GameHandler(U8GLIB_SSD1306_128X64 *_u8g, int _game)
    {
        u8g = _u8g;
        game = _game;
        snake = Snake(u8g);
        pong = Pong(u8g);
        cube = Cube(u8g);
    }

    void init(void)
    {
        switch (game)
        {
        case 0:
            snake.init();
            break;
        case 1:
            pong.init();
            break;
        case 2:
            cube.init();
            break;
        }
    }

    void draw(void)
    {
        switch (game)
        {
        case 0:
            snake.draw();
            break;
        case 1:
            pong.draw();
            break;
        case 2:
            cube.draw();
            break;
        }
    }
    void update(void)
    {
        switch (game)
        {
        case 0:
            snake.update();
            break;
        case 1:
            pong.update();
            break;
        case 2:
            cube.update();
            break;
        }
    }
    void setGame(int _game)
    {
        game = _game;
    }
};

#endif