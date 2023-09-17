#include "../Games/GameHandler.h"


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

    char* getName() { return _displayName; }

    int getGame() { return game; }
};