#ifndef RESOURCE_H
#define RESOURCE_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <map>
#include <vector>

class Image;
class ImageSheet;
class Resource;

class Image {
private:
    void LoadImage (std::string fileName);

public:

    std::string name;
    SDL_Texture* texture;
    int width;
    int height;

    Image (std::string name, std::string fileName);
    ~Image ();
};

class ImageSheet {

public:

    std::string name;
    std::vector<Image*> vectorImages;

    int index;
    int length;
    int speed;

    ImageSheet (std::string name);
    ~ImageSheet ();

    Image* GetImage ();
    void AddImage (Image* image);
    void SetSpeed (int speed);

    void NextIndex ();
};

class Font {
private:
    void LoadFont (std::string fileName);

public:

    std::string name;
    TTF_Font* font;
    int fontSize;

    TTF_Font* outline;
    int outlineSize;

    Font (std::string name, std::string fileName, int fontSize, int outlineSize);
    ~Font ();
};

class ResourceH {
public:

    std::map<std::string, Image*> mapImages;
    std::map<std::string, ImageSheet*> mapImageSheets;
    std::map<std::string, Font*> mapFonts;

    void ResourceCreate ();
    void ResourceDestroy ();

    Image* GetImage (std::string name);
    Image* AddImage (std::string name, std::string fileName);

    ImageSheet* GetImageSheet (std::string name);
    ImageSheet* AddImageSheet (std::string name);

    Font* GetFont (std::string name);
    Font* AddFont (std::string name, std::string fileName, int fontSize, int outlineSize);
};

extern ResourceH Resource;

#endif // RESOURCE_H
