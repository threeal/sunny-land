#include "stdio.h"
#include "Game.h"
#include "Manager.h"
#include "Menu.h"
#include "Intro.h"

void IntroH::IntroStart() {
    IntroCreate();
}

void IntroH::IntroLoop() {
    printf("level life %d", Level.life);
    IntroEnd();

    Mix_HaltMusic();
    if (Level.life < 0 || Level.stage > 2) {
        Game.TimeDelay(3500);
        Game.scene = Game.Scene::SceneMenu;
        Menu.MenuStart();
    } else {
        Game.TimeDelay(2000);
        Game.scene = Game.Scene::SceneLevel;
        Level.LevelStart();
    }
    Mix_PlayMusic(Game.music, -1);
}

void IntroH::IntroEnd() {
    IntroDestroy();
    Manager.ManagerDestroy();
}

void IntroH::IntroCreate() {

    Level.rectCamera.x = 0;
    Level.rectCamera.y = 0;

    char buffer[8];
    Sprite* newSprite;
    Background* newBackground;
    Text* newText;

    newSprite = new Sprite (0, 0);
    newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Black"));
    newSprite->SetType(Sprite::Type::None);
    newSprite->isTiled = true;
    newBackground = new Background(newSprite, 0, 0, false);

    if (Level.diamond <= 0) {
        Level.stage += 1;
    } else {
        Level.life -= 1;
    }

    if (Level.life < 0 || Level.stage > 2) {
        newText = new Text (
            Resource.GetFont("Medium"),
            Game.screenWidth / 2,
            Game.screenHeight / 2,
            "",
            true
        );
        newText->SetColor(255, 255, 255);
        newText->SetOutlineColor(32, 32, 32);
        newText->SetText("GAME OVER");
    } else {
        newSprite = new Sprite ((Game.screenWidth/2), (Game.screenHeight/2));
        newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("FoxIdle"));
        newSprite->SetType(Sprite::Type::None);
        newBackground = new Background(newSprite, -16, 32, true);

        newText = new Text (
            Resource.GetFont("Medium"),
            (Game.screenWidth / 2),
            (Game.screenHeight / 2) - 16,
            "",
            true
        );
        newText->SetColor(255, 255, 255);
        newText->SetOutlineColor(32, 32, 32);

        sprintf(buffer, "Stage - %d", Level.stage);
        newText->SetText(buffer);

        newText = new Text (
            Resource.GetFont("Medium"),
            (Game.screenWidth / 2) + 16,
            (Game.screenHeight / 2) + 24,
            "",
            false
        );
        newText->SetColor(255, 255, 255);
        newText->SetOutlineColor(32, 32, 32);

        sprintf(buffer, "x%d", Level.life);
        newText->SetText(buffer);
    }
}

void IntroH::IntroDestroy() {
}

