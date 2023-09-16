#include <U8glib.h>
#include <Wire.h>

#define MENU_LENGTH 4

#include "menu/Menu.h"

#include "Games/Game.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

MenuItem* menuItems[MENU_LENGTH] = {
    new MenuItem("Snake", 0),
    new MenuItem("Rad 2", 0),
    new MenuItem("Rad 3", 0),
    new MenuItem("Rad 5", 0)
};

Menu menu(menuItems, &u8g);

void setup() {
    Serial.begin(9600);
    menu.init();
    
}

void loop() {
    menu.loop();
       
}