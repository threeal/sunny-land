#include <stdio.h>
#include "Resource.h"

Font::Font (std::string name, std::string fileName, int fontSize, int outlineSize) {

    font = NULL;
    outline = NULL;

    this->name = name;
    this->fontSize = fontSize;
    this->outlineSize = outlineSize;

    font = TTF_OpenFont(fileName.c_str(), fontSize);
    if (font == NULL) {
        printf("%s Unable to load font\n", fileName.c_str());
        return;
    }

    if  (this->outlineSize <= 0) {
        return;
    }

    outline = TTF_OpenFont(fileName.c_str(), fontSize);
    if (outline == NULL) {
        printf("%s Unable to load outline\n", fileName.c_str());
        return;
    }
    TTF_SetFontOutline(outline, outlineSize);
}

Font::~Font() {
    if (font != NULL) {
        TTF_CloseFont(font);
        font = NULL;
    }
}
