
class MenuItem
{
private:
    char* _displayName;

public:
    MenuItem(char* displayName)
    {
        _displayName = displayName;
    }

    char* getName() { return _displayName; }
};