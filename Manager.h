#ifndef MANAGER_H
#define MANAGER_H

#include <SDL.h>
#include <vector>
#include <map>
#include "Resource.h"

class Sprite {
public:

    enum Type {
        None, Idle, Walk, Jump, Land
    };

    bool isActive;

    std::map<Type, ImageSheet*> mapImageSheets;
    int index;
    SDL_Rect rect;
    Type type;
    bool isTiled;

    Sprite (int x, int y);

    ImageSheet* GetImageSheet ();
    void AddImageSheet (Type type, ImageSheet* ImageSheet);

    void SetRect (int x, int y, int w, int h);
    void SetRect (int x, int y);
    void SetType (Type type);
};

class Background {

public:

    bool isActive;

    Sprite* sprite;
    SDL_Rect rect;
    SDL_Rect offset;

    bool isForeground;
    bool isParallax;
    double parallaxX;
    double parallaxY;

    Background (Sprite* sprite, int x, int y, bool isForeground);
    ~Background ();

    void SetOffset (int x, int y, int w, int h);
    void SetOffset (int x, int y);
    void SetRect ();

};

class Text {

public:

    bool isActive;
    bool isCenter;

    Font* font;
    std::string text;

    SDL_Texture* texture;
    SDL_Color color;
    SDL_Color outlineColor;
    SDL_Rect rect;

    int width;
    int height;

    Text (Font* font, int x, int y, std::string text, bool isCenter);

    void SetText (std::string text);
    void SetRect (int x, int y, int w, int h);
    void SetRect (int x, int y);
    void SetColor (int r, int g, int b);
    void SetOutlineColor (int r, int g, int b);
};

class ManagerH {
public:

    std::vector<Sprite*> vectorSprites;
    std::vector<Background*> vectorBackgrounds;
    std::vector<Background*> vectorForegrounds;
    std::vector<Text*> vectorTexts;

    void ManagerDestroy ();

    void ManageSprite ();
    void ClearSprite ();

    void ManageBackground ();
    void ManageForeground ();
    void ClearBackground ();

    void ManageText ();
    void ClearText ();
};

extern ManagerH Manager;

#endif // MANAGER_H
