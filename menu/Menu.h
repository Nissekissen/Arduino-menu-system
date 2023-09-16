#include "MenuItem.h"

class Menu
{
private:
    MenuItem *menuItems[MENU_LENGTH];
    U8GLIB_SSD1306_128X64 *u8g;

    GameHandler gameHandler;

    int currentMenu;

    bool isPlaying;

    void drawMenu(void)
    {
        uint8_t i, h;
        u8g_uint_t w, d;

        u8g->setFont(u8g_font_6x13);
        u8g->setFontRefHeightText();
        u8g->setFontPosTop();

        h = u8g->getFontAscent() - u8g->getFontDescent();
        w = u8g->getWidth();

        for (i = 0; i < MENU_LENGTH; i++)
        {
            MenuItem *item = menuItems[i];
            d = (w - u8g->getStrWidth(item->getName())) / 2;
            u8g->setDefaultForegroundColor();
            if (i == currentMenu)
            {
                u8g->drawBox(0, i * h + 1, w, h);
                u8g->setDefaultBackgroundColor();
            }
            u8g->drawStr(d, i * h, item->getName());
        }
    }

    void updateMenu(void)
    {

        if (isPlaying) {
            if (digitalRead(6)) {
                isPlaying = false;
            }
            return;
        }

        if (digitalRead(3))
        {
            currentMenu++;
            if (currentMenu >= MENU_LENGTH)
            {
                currentMenu = 0;
            }
        }
        else if (digitalRead(2))
        {
            if (currentMenu == 0)
            {
                currentMenu = MENU_LENGTH;
            }
            currentMenu--;
        }
        else if (digitalRead(5))
        {
            isPlaying = true;
            gameHandler.setGame(menuItems[currentMenu]->getGame());
            gameHandler.init();
        }
    }

public:
    Menu(MenuItem *items[10], U8GLIB_SSD1306_128X64 *oled)
    {
        for (int i = 0; i < 10; i++)
        {
            menuItems[i] = items[i];
        }
        u8g = oled;

        currentMenu = 0;

        isPlaying = false;

        gameHandler = GameHandler(u8g, 0);
    }

    void init()
    {
        Wire.begin();
        pinMode(2, INPUT);
        pinMode(3, INPUT);
        pinMode(4, INPUT);
        pinMode(5, INPUT);
        pinMode(6, INPUT);
    }

    void loop()
    {
        u8g->firstPage();

        do
        {

            if (isPlaying)
            {
                gameHandler.draw();
            }
            else
            {
                drawMenu();
            }

        } while (u8g->nextPage());

        if (isPlaying)
        {
            gameHandler.update();
        }

        updateMenu();
    }
};