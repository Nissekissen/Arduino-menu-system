#include <U8glib.h>
#include <Wire.h>

#define MENU_LENGTH 4

#include "menu/Menu.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

MenuItem* menuItems[MENU_LENGTH] = {
    new MenuItem("Rad 1"),
    new MenuItem("Rad 2"),
    new MenuItem("Rad 3"),
    new MenuItem("Rad 4")
};

Menu menu(menuItems, &u8g);

void setup() {
    menu.init();
}

void loop() {
    menu.loop();
       
}