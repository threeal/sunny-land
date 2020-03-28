#include "Game.h"
#include "Level.h"
#include "Manager.h"

Background::Background(Sprite* sprite, int x, int y, bool isForeground) {
    isActive = true;

    this->isForeground = isForeground;
    if (this->isForeground) {
        Manager.vectorForegrounds.push_back(this);
    } else {
        Manager.vectorBackgrounds.push_back(this);
    }

    isParallax = true;
    parallaxX = 1;
    parallaxY = 1;

    this->sprite = sprite;
    rect.w = 1;
    rect.h = 1;
    SetOffset(x, y);
}

Background::~Background() {
    if (sprite != NULL) {
        sprite->isActive = false;
    }
}

void Background::SetOffset(int x, int y, int w, int h) {

    offset.x = x;
    offset.y = y;
    offset.w = w;
    offset.h = h;

    SetRect();
}

void Background::SetOffset(int x, int y) {
    SetOffset(x, y, offset.w, offset.h);
}

void Background::SetRect() {
    rect.x = offset.x;
    rect.y = offset.y;
    if (isParallax) {
        rect.x += ((Game.screenWidth / 2) - Level.rectCamera.x) * parallaxX;
        rect.y += ((Game.screenHeight / 2) - Level.rectCamera.y) * parallaxY;
    }

    if (sprite != NULL) {
        sprite->rect.x = rect.x;
        sprite->rect.y = rect.y;
    }
}
