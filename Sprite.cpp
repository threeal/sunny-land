#include <stdio.h>
#include "Manager.h"

Sprite::Sprite(int x, int y) {
    isActive = true;
    Manager.vectorSprites.push_back(this);

    isTiled = false;

    rect.w = -2;
    rect.h = 2;
    SetRect(x, y);
}

ImageSheet* Sprite::GetImageSheet() {
    std::map<Type, ImageSheet*>::iterator it;
    if ((it = mapImageSheets.find(type)) != mapImageSheets.end()) {
        return it->second;
    }

    return NULL;
}

void Sprite::AddImageSheet(Type type, ImageSheet* imageSheet) {
    std::map<Type, ImageSheet*>::iterator it;
    if ((it = mapImageSheets.find(type)) != mapImageSheets.end()) {
        mapImageSheets.erase(it);
    }

    mapImageSheets.insert(std::pair<Type, ImageSheet*>(type, imageSheet));
}

void Sprite::SetRect(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Sprite::SetRect(int x, int y) {
    SetRect(x, y, rect.w, rect.h);
}

void Sprite::SetType(Type type) {
    this->type = type;
}
