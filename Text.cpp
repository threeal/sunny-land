#include <stdio.h>
#include "Manager.h"
#include "Game.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

Text::Text(Font* font, int x, int y, std::string text, bool isCenter) {
    isActive = true;
    Manager.vectorTexts.push_back(this);

    this->font = font;
    this->text = "";
    this->isCenter = isCenter;

    texture = NULL;
    rect.w = 1;
    rect.h = 1;

    width = 0;
    height = 0;

    SetRect(x, y);
    SetColor(255, 255, 255);
    SetOutlineColor(0, 0, 0);
    SetText(text);
}

void Text::SetText(std::string text) {
    if (this->text == text) {
        return;
    }
    this->text = text;

    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }

    SDL_Surface* fgSurface = TTF_RenderText_Solid(font->font, this->text.c_str(), color);
    if (fgSurface == NULL) {
        printf("Unable to create text\n");
        return;
    }

    if (font->outlineSize > 0) {
        SDL_Surface* bgSurface = TTF_RenderText_Solid(font->outline, this->text.c_str(), outlineColor);
        if (bgSurface == NULL) {
            printf("Unable to create text\n");
            return;
        }

        SDL_Rect rect = {font->outlineSize, font->outlineSize, fgSurface->w, fgSurface->h};
        SDL_BlitSurface(fgSurface, NULL, bgSurface, &rect);
        SDL_FreeSurface(fgSurface);
        fgSurface = bgSurface;
    }

    texture = SDL_CreateTextureFromSurface(Game.renderer, fgSurface);
    width = fgSurface->w;
    height = fgSurface->h;
    SDL_FreeSurface(fgSurface);

    if (texture == NULL) {
        printf("Unable to create texture\n");
        return;
    }
}

void Text::SetRect(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Text::SetRect(int x, int y) {
    SetRect(x, y, rect.w, rect.h);
}

void Text::SetColor(int r, int g, int b) {
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;
}

void Text::SetOutlineColor(int r, int g, int b) {
    outlineColor.r = r;
    outlineColor.g = g;
    outlineColor.b = b;
    outlineColor.a = 255;
}
