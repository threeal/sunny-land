#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>

#include "Game.h"
#include "Resource.h"
#include "Manager.h"
#include "Menu.h"
#include "Intro.h"
#include "Level.h"

GameH Game;
ResourceH Resource;
ManagerH Manager;
MenuH Menu;
IntroH Intro;
LevelH Level;

int main (int argc, char* argv[]) {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize\n");
        return 1;
    }

    if (!Game.WindowCreate()) {
        return 1;
    }

    if (!Game.RendererCreate()) {
        return 1;
    }

    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_Image could not Initialize\n");
        return false;
    }

    if( TTF_Init() == -1 )
    {
        printf( "SDL_ttf could not Initialize\n");
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf( "SDL_mixer could not Initialize\n");
        return false;
    }

    Game.GameStart();
    Game.GameLoop();
    Game.GameEnd();

    Game.RendererDestroy();
    Game.WindowDestroy();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
