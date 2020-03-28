#include <stdio.h>
#include "Game.h"
#include "Resource.h"
#include "Menu.h"
#include "Intro.h"
#include "Level.h"

GameH::GameH() {

    isEnd = false;
    scene = Scene::SceneMenu;

    screenWidth = 640;
    screenHeight = 480;
}

void GameH::GameStart() {
    Resource.ResourceCreate();

    music = Mix_LoadMUS("./Sound/Music.wav");
    Mix_PlayMusic(music, -1);

    soundWin = Mix_LoadWAV("./Sound/Win.wav");
    soundLose = Mix_LoadWAV("./Sound/Lose.wav");
    soundJump = Mix_LoadWAV("./Sound/Jump.wav");
    soundHit = Mix_LoadWAV("./Sound/Hit.wav");
    soundPoint = Mix_LoadWAV("./Sound/Point.wav");
    soundStomp = Mix_LoadWAV("./Sound/Stomp.wav");


    switch (scene) {
    case Scene::SceneMenu:  Menu.MenuStart(); break;
    case Scene::SceneIntro: Intro.IntroStart(); break;
    case Scene::SceneLevel: Level.LevelStart(); break;
    }
}

void GameH::GameLoop() {
    while(!End()) {
        InputHandle();

        switch (scene) {
        case Scene::SceneMenu:  Menu.MenuLoop(); break;
        case Scene::SceneIntro: Intro.IntroLoop(); break;
        case Scene::SceneLevel: Level.LevelLoop(); break;
        }

        Manager.ManageBackground();
        Manager.ManageSprite();
        Manager.ManageText();
        Manager.ManageForeground();

        ScreenUpdate();
    }
}

void GameH::GameEnd() {

    switch (scene) {
    case Scene::SceneMenu:  Menu.MenuEnd(); break;
    case Scene::SceneIntro: Intro.IntroEnd(); break;
    case Scene::SceneLevel: Level.LevelEnd(); break;
    }

    Mix_FreeMusic(music);

    Resource.ResourceDestroy();
}

bool GameH::End() {
    return isEnd;
}

bool GameH::WindowCreate() {
    window = SDL_CreateWindow(
        "Sunnyland",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screenWidth,
        screenHeight,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("Window could not be created\n");
        return false;
    }

    return true;
}

bool GameH::RendererCreate() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created\n");
        return false;
    }

    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );

    return true;
}

bool GameH::WindowDestroy() {
    SDL_DestroyWindow(window);
    window = NULL;

    return true;
}

bool GameH::RendererDestroy() {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;

    return true;
}

void GameH::ScreenClear() {
    SDL_RenderClear(renderer);
}

void GameH::ScreenPut(Sprite* sprite) {
    ImageSheet* imageSheet;
    if ((imageSheet = sprite->GetImageSheet()) == NULL) {
        return;
    }

    Image* image;
    if ((image = imageSheet->GetImage()) == NULL) {
        return;
    }

    SDL_Rect rect = sprite->rect;
    SDL_Point point;
    SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;

    point.x = rect.x;
    point.y = rect.y;

    if (rect.w < 0) {
        if (rect.h < 0) { flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);}
        else { flip = SDL_FLIP_HORIZONTAL;}
    }
    else if (rect.h < 0) { flip = SDL_FLIP_VERTICAL;}

    rect.w = SDL_abs(rect.w) * image->width;
    rect.h = SDL_abs(rect.h) * image->height;
    rect.x = rect.x - (rect.w / 2);
    rect.y = rect.y - (rect.h / 2);

    if (sprite->isTiled) {
        while (rect.x > 0) {
            rect.x -= rect.w;
        }

        while (rect.y > 0) {
            rect.y -= rect.h;
        }

        while (rect.x < screenWidth) {
            int tempY = rect.y;
            while (rect.y < screenHeight) {
                SDL_RenderCopyEx(renderer, image->texture, NULL, &rect, 0, &point, flip);
                rect.y += rect.h;
            }
            rect.x += rect.w;
            rect.y = tempY;
        }
    }
    else {
        SDL_RenderCopyEx(renderer, image->texture, NULL, &rect, 0, &point, flip);
    }
}

void GameH::ScreenPut(Text* text) {

    SDL_Texture* texture;
    if ((texture = text->texture) == NULL) {
        return;
    }

    SDL_Rect rect = text->rect;
    SDL_Point point;
    SDL_RendererFlip flip = SDL_RendererFlip::SDL_FLIP_NONE;

    point.x = rect.x;
    point.y = rect.y;

    if (rect.w < 0) {
        if (rect.h < 0) { flip = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);}
    else { flip = SDL_FLIP_HORIZONTAL;}
    }
    else if (rect.h < 0) { flip = SDL_FLIP_VERTICAL;}

    rect.w = SDL_abs(rect.w) * text->width;
    rect.h = SDL_abs(rect.h) * text->height;

    if (text->isCenter) {
        rect.x = rect.x - (rect.w / 2);
        rect.y = rect.y - (rect.h / 2);
    } else {
        rect.x = rect.x;
        rect.y = rect.y;
    }

    SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, &point, flip);
}

void GameH::ScreenUpdate() {
    SDL_RenderPresent(renderer);

    TimeHandle();
    ScreenClear();
}

void GameH::InputHandle() {

    for (int i = 0; i < input.keySize; i++) {
        if (input.keyState[i] == Input::State::Pressed) {
            input.keyState[i] = Input::State::Async;
        } else if (input.keyState[i] == Input::State::Released) {
            input.keyState[i] = Input::State::None;
        }
    }

    if (input.mouseState == Input::State::Pressed) {
        input.mouseState = Input::State::Async;
    } else if (input.mouseState == Input::State::Released) {
        input.mouseState = Input::State::None;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isEnd = true;
        }
        else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            for (int i = 0; i < input.keySize; i++) {
                if (event.key.keysym.sym == input.keyCode[i]) {
                    if (event.key.state == SDL_PRESSED) {
                        if (input.keyState[i] != Input::State::Async) {
                            input.keyState[i] = Input::State::Pressed;
                        }
                    } else {
                        input.keyState[i] = Input::State::Released;
                    }
                }
            }
        }
        else if (event.type == SDL_MOUSEMOTION) {
            input.mouseX = event.motion.x;
            input.mouseY = event.motion.y;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                if (event.button.state == SDL_PRESSED) {
                    if (input.mouseState != Input::State::Async) {
                        input.mouseState = Input::State::Pressed;
                    }
                } else {
                    input.mouseState = Input::State::Released;
                }
            }
        }
    }
}

void GameH::TimeHandle() {
    while (SDL_GetTicks() - time.ticks <= 30) {}

    time.ticks += 30;
    time.frames++;
}

void GameH::TimeDelay(int delay) {
    int tick = SDL_GetTicks();
    while (SDL_GetTicks() - tick <= delay) {}

    time.ticks = SDL_GetTicks();
}
