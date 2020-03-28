#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include "Level.h"

class MenuH {

public:

    void MenuStart ();
    void MenuLoop ();
    void MenuEnd ();

    void MenuCreate ();
    void MenuDestroy ();
};

extern MenuH Menu;

#endif // MENU_H
