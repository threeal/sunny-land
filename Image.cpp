#include <stdio.h>
#include "Game.h"
#include "Resource.h"

Image::Image(std::string name, std::string fileName) {
    this->name = name;
    texture = NULL;

    LoadImage(fileName);
}

Image::~Image() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
}

void Image::LoadImage(std::string fileName) {
    SDL_Surface* surface = IMG_Load(fileName.c_str());
    if (surface == NULL) {
        printf("%s Unable to load image\n", fileName.c_str());
        return;
    }

    texture = SDL_CreateTextureFromSurface(Game.renderer, surface);
    width = surface->w;
    height = surface->h;
    SDL_FreeSurface(surface);

    if (texture == NULL) {
        printf("Unable to create texture\n");
        return;
    }
}
