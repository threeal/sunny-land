#include "stdio.h"
#include "Game.h"
#include "Manager.h"
#include "Menu.h"
#include "Intro.h"

void MenuH::MenuStart() {
    MenuCreate();
}

void MenuH::MenuLoop() {
    if (Game.input.GetKeyState(Input::Key::Enter) == Input::State::Released) {
        Game.scene = Game.Scene::SceneIntro;
        MenuEnd();

        Level.stage = 1;
        Level.score = 0;
        Level.diamond = 6;
        Level.life = 3;
        Intro.IntroStart();
    } else if (Game.input.GetKeyState(Input::Key::Escape) == Input::State::Released) {
        Game.isEnd = true;
    }
}

void MenuH::MenuEnd() {
    MenuDestroy();
    Manager.ManagerDestroy();
}

void MenuH::MenuCreate() {
    Level.rectCamera.x = 0;
    Level.rectCamera.y = 0;

    Sprite* newSprite = new Sprite (0, 0);
    newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Background"));
    newSprite->SetType(Sprite::Type::None);
    newSprite->isTiled = true;
    Background* newBackground = new Background(newSprite, 0, newSprite->rect.y, false);
    newBackground->parallaxX = 0.25;

    newSprite = new Sprite (Game.screenWidth/2, 100);
    newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Title"));
    newSprite->SetType(Sprite::Type::None);
    newSprite->SetRect(newSprite->rect.x, newSprite->rect.y, 2, 2);

    newSprite = new Sprite (Game.screenWidth/2, Game.screenHeight - 100);
    newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("PressEnter"));
    newSprite->SetType(Sprite::Type::None);
    newSprite->SetRect(newSprite->rect.x, newSprite->rect.y, 2, 2);
}

void MenuH::MenuDestroy() {
}
