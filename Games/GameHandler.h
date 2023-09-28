/**
 * @file GameHandler.h
 * 
 * @brief Game handler for handling the games
*/

#ifndef GAME_H
#define GAME_H

#include "Snake.h"
#include "Pong.h"
#include "3DCube.h"

#define SNAKE_ID 0

/**
 * Game handler for handling the games
 * 
 * @param U8GLIB_SSD1306_128X64 The display
 * @param game The id of the selected game
*/
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

    /**
     * Initialize the game
    */
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

    /**
     * Draw the game
    */
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

    /**
     * Update the game
    */
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

    /**
     * Set the game
     * 
     * @param _game The id of the selected game
    */
    void setGame(int _game)
    {
        game = _game;
    }
};

#endif