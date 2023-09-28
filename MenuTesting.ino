/**
 * MenuTesting.ino
 * Purpose: A program with a simple menu system where you can select between a few games to play.
 * Date: 2023-09-23
 * Created by: Nils Lindblad
*/

#include <U8glib.h>
#include <Wire.h>
#include <TMM_matrix.h>
#include <TMM_squarematrix.h>

#define MENU_LENGTH 3

#include "menu/Menu.h"

#include "Games/GameHandler.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK);

MenuItem* menuItems[MENU_LENGTH] = {
    new MenuItem("Snake", 0),
    new MenuItem("Pong", 1),
    new MenuItem("3D Cube", 2)
};

Menu menu(menuItems, &u8g);

void setup() {
    Serial.begin(9600);
    menu.init();
    
}

void loop() {
    menu.loop();
       
}