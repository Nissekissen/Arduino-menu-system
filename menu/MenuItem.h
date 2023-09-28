/**
 * @file MenuItem.h
 * 
 * @brief Menu item for storing the name and game id
*/

#include "../Games/GameHandler.h"

/**
 * Menu item for storing the name and game id
 * 
 * @param displayName The name of the game
 * @param game The id of the game
*/
class MenuItem
{
private:
    char* _displayName;
    int game;

public:
    MenuItem(char* displayName, int _game)
    {
        _displayName = displayName;
        game = _game;
    }

    /**
     * Get the name of the game
     * 
     * @return The name of the game
    */
    char* getName() { return _displayName; }

    /**
     * Get the id of the game
     * 
     * @return The id of the game
    */
    int getGame() { return game; }
};