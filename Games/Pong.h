

class Paddle
{
private:
    int x, y = 0;
    int w = 4;
    int h = 24;

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

    void draw()
    {
        u8g->drawBox(x, y, w, h);
    }

    bool collided(int _x, int _y)
    {
        if (_x >= x - 4 && _x <= x + 6 && _y >= y && _y < y + h - 2)
        {
            return true;
        }
        return false;
    }

    void move(int direction)
    {
        y += direction * speed;
    }
};

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

    void draw()
    {
        u8g->drawBox(x - 2, y - 2, 4, 4);
    }

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

    bool isGameOver()
    {
        return gameOver;
    }

    void reset(int side)
    {
        gameOver = false;
        x = 64;
        y = 32;
        int dir = random(2) == 0 ? -1 : 1;

        int _a = random(4, 11);
        Serial.println(_a * dir);
        angle = PI / (dir * _a) + (side == -1 ? PI : 0);
    }

    int getX()
    {
        return (int)x;
    }
};

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

    void init()
    {
        player1 = Paddle(u8g, 2, 0);
        player2 = Paddle(u8g, 122, 0);

        ball = Ball(u8g, &player1, &player2);
    };

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