#include <stdio.h>
#include "Game.h"
#include "Manager.h"

void ManagerH::ManagerDestroy() {
    ClearText();
    ClearBackground();
    ClearSprite();
}

void ManagerH::ManageSprite() {
    std::vector<Sprite*>::iterator it = vectorSprites.begin();

    while (it != vectorSprites.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorSprites.erase(it);
            continue;
        }

        ++it;
    }

    for (Sprite* sprite : vectorSprites) {
        Game.ScreenPut(sprite);
    }
}

void ManagerH::ClearSprite() {
    for (Sprite* sprite : vectorSprites) {
        delete sprite;
    }

    vectorSprites.clear();
}

void ManagerH::ManageBackground() {
    std::vector<Background*>::iterator it = vectorBackgrounds.begin();

    while (it != vectorBackgrounds.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorBackgrounds.erase(it);
            continue;
        }

        ++it;
    }

    for (Background* background: vectorBackgrounds) {
        background->SetRect();
    }
}

void ManagerH::ManageForeground() {
    std::vector<Background*>::iterator it = vectorForegrounds.begin();

    while (it != vectorForegrounds.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorForegrounds.erase(it);
            continue;
        }

        ++it;
    }

    for (Background* background: vectorForegrounds) {
        background->SetRect();
    }
}

void ManagerH::ClearBackground() {
    for (Background* background : vectorBackgrounds) {
        delete background;
    }

    for (Background* background : vectorForegrounds) {
        delete background;
    }

    vectorBackgrounds.clear();
    vectorForegrounds.clear();
}

void ManagerH::ManageText() {
    std::vector<Text*>::iterator it = vectorTexts.begin();

    while (it != vectorTexts.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorTexts.erase(it);
            continue;
        }

        ++it;
    }

    for (Text* text : vectorTexts) {
        Game.ScreenPut(text);
    }
}

void ManagerH::ClearText() {
    for (Text* text : vectorTexts) {
        delete text;
    }

    vectorTexts.clear();
}
