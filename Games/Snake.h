

int SQUARE_SIZE = 4;
int GRID_X = 128 / SQUARE_SIZE;
int GRID_Y = 64 / SQUARE_SIZE;

class Food
{
private:
    int x, y;
    U8GLIB_SSD1306_128X64 *u8g;

public:
    Food(){};
    Food(U8GLIB_SSD1306_128X64 *_u8g)
    {
        randomSeed(analogRead(A5));
        x = random(GRID_X);
        y = random(GRID_Y);
        u8g = _u8g;
    }

    void regenerate()
    {
        int oldX = x, oldY = y;
        do {
        randomSeed(analogRead(A5));
        x = random(GRID_X);
        y = random(GRID_Y);
        } while (oldX == x && oldY == y);
    }

    int getX() { return x; }
    int getY() { return y; }

    void draw()
    {
        u8g->drawBox(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
    }
};

class SnakePart
{
private:
    U8GLIB_SSD1306_128X64 *u8g;

public:
    int x, y;

    SnakePart() {}

    SnakePart(int _x, int _y, U8GLIB_SSD1306_128X64 *_u8g)
    {
        x = _x;
        y = _y;
        u8g = _u8g;
    }

    void draw()
    {
        u8g->drawBox(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE);
    }

    void setPosition(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
};

void shift(SnakePart values[], int size)
{
    Serial.println(values[0].x);

    SnakePart temp = values[size - 1], temp1;
    for (int i = 0; i < size; i++)
    {
        temp1 = values[i];
        values[i] = temp;
        temp = temp1;
    }

    Serial.println(values[0].x);
}

class Snake
{
private:
    U8GLIB_SSD1306_128X64 *u8g;
    SnakePart tail[32];
    Food food;

    int xVel = 1;
    int yVel = 0;

    int snakeSize = 4;

public:
    Snake(U8GLIB_SSD1306_128X64 *_u8g)
    {
        u8g = _u8g;
        food = Food(u8g);
    };

    void init()
    {
        Serial.println("Init snake");
        tail[0] = SnakePart(3, 0, u8g);
        tail[1] = SnakePart(2, 0, u8g);
        tail[2] = SnakePart(1, 0, u8g);
        tail[3] = SnakePart(0, 0, u8g);
    }

    void draw()
    {
        food.draw();

        for (int i = 0; i < snakeSize; i++)
        {

            tail[i].draw();
        }

    }

    void update(void)
    {
        if (tail[0].x == food.getX() && tail[0].y == food.getY()) {
            tail[snakeSize] = SnakePart(tail[snakeSize - 1].x, tail[snakeSize - 1].y, u8g);
            snakeSize++;
            food.regenerate();
        }

        if (digitalRead(2) && xVel != 1)
        {
            xVel = -1;
            yVel = 0;
        }
        else if (digitalRead(3) && xVel != -1)
        {
            xVel = 1;
            yVel = 0;
        }
        else if (digitalRead(4) && yVel != 1)
        {
            xVel = 0;
            yVel = -1;
        }
        else if (digitalRead(5) && yVel != -1)
        {
            xVel = 0;
            yVel = 1;
        }

        if (tail[0].x > GRID_X)
        {
            tail[0].x = 0;
        }
        if (tail[0].x < 0)
        {
            tail[0].x = GRID_X - 1;
        }
        if (tail[0].y > GRID_Y)
        {
            tail[0].y = 0;
        }
        if (tail[0].y <= 0)
        {
            tail[0].y = GRID_Y - 1;
        }

        shift(tail, snakeSize);

        tail[0].x = tail[1].x + xVel;
        tail[0].y = tail[1].y + yVel;
    }
};