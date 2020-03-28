#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Resource.h"
#include "Manager.h"

class Input {

public:

    enum Key {
        Up, Down, Left, Right, Jump, Save, Load, Prev1, Next1, Prev2, Next2, Enter, Escape
    };

    enum State {
        None, Pressed, Async, Released
    };

    int keySize = 13;
    SDL_Keycode keyCode[13] = {
        SDLK_UP,
        SDLK_DOWN,
        SDLK_LEFT,
        SDLK_RIGHT,
        SDLK_SPACE,
        SDLK_F5,
        SDLK_F9,
        SDLK_q,
        SDLK_w,
        SDLK_a,
        SDLK_s,
        SDLK_RETURN,
        SDLK_ESCAPE
    };

    State keyState[13] = {
        State::None,
        State::None,
        State::None,
        State::None,
        State::None,
        State::None,
        State::None,
        State::None,
        State::None,
        State::None,
        State::None,
        State::None,
        State::None
    };

    int mouseX = 0;
    int mouseY = 0;
    State mouseState = State::None;

    State GetKeyState (Key key);
    State GetMouseState ();
};

class Time {

public:

    Uint32 ticks = 0;
    int frames = 0;

    int GetFrames ();

};

class GameH {

public:

    bool isEnd;

    SDL_Window* window;

    SDL_Renderer* renderer;

    SDL_Surface* screenSurface;
    int screenWidth;
    int screenHeight;

    Mix_Music* music;
    Mix_Chunk* soundWin;
    Mix_Chunk* soundLose;
    Mix_Chunk* soundJump;
    Mix_Chunk* soundHit;
    Mix_Chunk* soundPoint;
    Mix_Chunk* soundStomp;

    Input input;
    Time time;

    enum Scene {
        SceneMenu, SceneIntro, SceneLevel
    };

    Scene scene;

    GameH ();
    bool End ();

    void GameStart ();
    void GameLoop ();
    void GameEnd ();

    bool WindowCreate ();
    bool WindowDestroy ();

    bool RendererCreate ();
    bool RendererDestroy();

    void ScreenClear ();
    void ScreenPut (Sprite* sprite);
    void ScreenPut(Text* text);
    void ScreenUpdate ();

    void InputHandle ();
    void TimeHandle ();
    void TimeDelay (int delay);
};

extern GameH Game;

#endif // GAME_H
