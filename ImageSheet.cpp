#include <stdio.h>
#include "Game.h"
#include "Resource.h"

ImageSheet::ImageSheet(std::string name) {
    this->name = name;

    index = 0;
    length = 0;
    speed = 0;
}

ImageSheet::~ImageSheet() {
    for (Image* image : vectorImages) {
        delete image;
    }

    vectorImages.clear();
}

Image* ImageSheet::GetImage() {
    if (length <= 0) {
        return NULL;
    }

    if (speed > 0) {
        index = (Game.time.GetFrames() % (speed * length)) / speed;
    }

    return vectorImages.at(index);
}

void ImageSheet::AddImage(Image* image) {
    vectorImages.push_back(image);
    length = vectorImages.size();
}

void ImageSheet::SetSpeed(int speed) {
    this->speed = speed;
}

void ImageSheet::NextIndex() {
    index = (++index) % length;
}
