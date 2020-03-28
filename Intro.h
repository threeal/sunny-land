#ifndef INTRO_H
#define INTRO_H

#include <SDL.h>
#include "Level.h"

class IntroH {
public:

    void IntroStart ();
    void IntroLoop ();
    void IntroEnd ();

    void IntroCreate ();
    void IntroDestroy ();
};

extern IntroH Intro;

#endif // INTRO_H
