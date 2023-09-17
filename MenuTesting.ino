#include <U8glib.h>
#include <Wire.h>
#include <TMM_matrix.h>
#include <TMM_squarematrix.h>

#define MENU_LENGTH 4

#include "menu/Menu.h"

#include "Games/GameHandler.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

MenuItem* menuItems[MENU_LENGTH] = {
    new MenuItem("Snake", 0),
    new MenuItem("Pong", 1),
    new MenuItem("3D Cube", 2),
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