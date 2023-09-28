/**
 * @file Pong.h
 * 
 * @brief A pong game for the menu system.
*/


/**
 * Paddle class for the pong game
 * 
 * @param u8g U8GLIB_SSD1306_128X64 object for drawing to the screen
 * @param x X position of the paddle
 * @param y Y position of the paddle
*/
class Paddle
{
private:
    int x, y = 0;
    int w = 4;
    int h = 16;

    int speed = 4;

    U8GLIB_SSD1306_128X64 *u8g;

public:
    int score = 0;

    Paddle(){};
    Paddle(U8GLIB_SSD1306_128X64 *_u8g, int _x, int _y)
    {
        u8g = _u8g;
        x = _x;
        y = _y;
    }

    /**
     * Draw the paddle to the screen
    */
    void draw()
    {
        u8g->drawBox(x, y, w, h);
    }

    /**
     * Check if the ball collided with the paddle
     * 
     * @param _x X position of the ball
     * @param _y Y position of the ball
     * @return true if the ball collided with the paddle
    */
    bool collided(int _x, int _y)
    {
        if (_x >= x - 4 && _x <= x + 6 && _y >= y && _y < y + h - 2)
        {
            return true;
        }
        return false;
    }

    /**
     * Move the paddle up or down
     * 
     * @param direction 1 for up, -1 for down
    */
    void move(int direction)
    {
        if (y + direction * speed <= 0) {
            y = 0;
            return;
        }
        if (y + direction * speed >= 48) {
            y = 48;
            return;
        }
        y += direction * speed;
    }
};

/**
 * Ball class for the pong game
 * 
 * @param u8g U8GLIB_SSD1306_128X64 object for drawing to the screen
 * @param p1 Paddle object for player 1
 * @param p2 Paddle object for player 2
*/
class Ball
{
private:
    float x = 64, y = 32;
    int speed = 5;
    double angle = PI / 6;

    U8GLIB_SSD1306_128X64 *u8g;

    Paddle *p1;
    Paddle *p2;

    bool gameOver = false;

public:
    Ball(){};
    Ball(U8GLIB_SSD1306_128X64 *_u8g, Paddle *_p1, Paddle *_p2)
    {
        u8g = _u8g;
        p1 = _p1;
        p2 = _p2;
        randomSeed(analogRead(A2));
    }

    /**
     * Draw the ball to the screen.
    */
    void draw()
    {
        u8g->drawBox(x - 2, y - 2, 4, 4);
    }

    /**
     * Update the ball's position. It uses the angle and speed to calculate the new position.
    */
    void update()
    {

        // Bounce on walls
        if (y >= 62 || y <= 2)
        {
            angle = -angle;
        }

        // Bounce on paddles
        if (p1->collided(x, y) || p2->collided(x, y))
        {
            angle += PI;
            angle = -angle;
            

            // Change angle by a small amount
            int dir = random(2) == 0 ? -1 : 1;
            int _a = random(8, 16);
            float angleOffset = PI / (dir * _a);
            angle += angleOffset;

            // Increase speed
            speed += (random(2) == 0 ? 1 : 1);
        }

        // If ball is out of bounds
        if (x > 128 || x < 0)
        {
            gameOver = true;
        }

        // Update position
        x += speed * cos(angle);
        y += speed * sin(angle);
    }

    /**
     * Check if the game is over.
     * 
     * @return bool True if the game is over.
    */
    bool isGameOver()
    {
        return gameOver;
    }

    /**
     * Reset the ball.
    */
    void reset(int side)
    {

        speed = 5;

        gameOver = false;
        x = 64;
        y = 32;
        int dir = random(2) == 0 ? -1 : 1;
        int _a = random(4, 11);
        
        angle = PI / (dir * _a) + (side == -1 ? PI : 0);
    }

    /**
     * Get the X position of the ball.
     * 
     * @return int X position of the ball.
    */
    int getX()
    {
        return (int)x;
    }
};

/**
 * Pong game for being used with the simple menu system.
 * 
 * @param u8g U8GLIB_SSD1306_128X64 object for drawing to the screen.
*/
class Pong
{
private:
    U8GLIB_SSD1306_128X64 *u8g;

    Paddle player1;
    Paddle player2;

    Ball ball;

public:
    Pong(){};
    Pong(U8GLIB_SSD1306_128X64 *_u8g)
    {
        u8g = _u8g;
    }

    /**
     * Initialize the game.
    */
    void init()
    {
        player1 = Paddle(u8g, 2, 0);
        player2 = Paddle(u8g, 122, 0);


        ball = Ball(u8g, &player1, &player2);
    };

    /**
     * Draw the game.
    */
    void draw()
    {

        u8g->drawLine(64, 0, 64, 64);

        char score[16];
        itoa(player1.score, score, 10);
        int d = (110 - u8g->getStrWidth(score)) / 2;
        u8g->drawStr(d, 2, score);

        itoa(player2.score, score, 10);
        d = (146 - u8g->getStrWidth(score)) / 2;
        u8g->drawStr(d, 2, score);

        player1.draw();
        player2.draw();
        ball.draw();
    }

    /**
     * Update the game.
    */
    void update()
    {
        if (digitalRead(2))
        {
            player1.move(-1);
        }
        else if (digitalRead(3))
        {
            player1.move(1);
        }

        if (digitalRead(4))
        {
            player2.move(-1);
        }
        else if (digitalRead(5))
        {
            player2.move(1);
        }

        if (ball.isGameOver())
        {
            if (ball.getX() > 128)
            {
                player1.score++;
            }
            else
            {
                player2.score++;
            }
            ball.reset(ball.getX() > 128 ? -1 : 1);
        }

        ball.update();
    }
};