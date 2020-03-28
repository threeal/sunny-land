#include <stdio.h>
#include "Resource.h"

void ResourceH::ResourceCreate() {
    ImageSheet* imageSheet;

    imageSheet = AddImageSheet("Black");
    imageSheet->AddImage( AddImage ("Black", "./Sprite/Black.png") );

    imageSheet = AddImageSheet("Background");
    imageSheet->AddImage( AddImage ("Background", "./Sprite/Background.png") );

    imageSheet = AddImageSheet("Foreground");
    imageSheet->AddImage( AddImage ("Foreground", "./Sprite/Foreground.png") );

    imageSheet = AddImageSheet("Title");
    imageSheet->AddImage( AddImage ("Title", "./Sprite/Title.png") );

    imageSheet = AddImageSheet("PressEnter");
    imageSheet->SetSpeed(30);
    imageSheet->AddImage( AddImage ("PressEnter1", "./Sprite/PressEnter1.png") );
    imageSheet->AddImage( AddImage ("PressEnter2", "./Sprite/PressEnter2.png") );

    imageSheet = AddImageSheet("LandC");
    imageSheet->AddImage( AddImage ("LandC", "./Sprite/LandC.png") );
    imageSheet = AddImageSheet("LandN");
    imageSheet->AddImage( AddImage ("LandN", "./Sprite/LandN.png") );
    imageSheet = AddImageSheet("LandNE");
    imageSheet->AddImage( AddImage ("LandNE", "./Sprite/LandNE.png") );
    imageSheet = AddImageSheet("LandE");
    imageSheet->AddImage( AddImage ("LandE", "./Sprite/LandE.png") );
    imageSheet = AddImageSheet("LandSE");
    imageSheet->AddImage( AddImage ("LandSE", "./Sprite/LandSE.png") );
    imageSheet = AddImageSheet("LandS");
    imageSheet->AddImage( AddImage ("LandS", "./Sprite/LandS.png") );
    imageSheet = AddImageSheet("LandSW");
    imageSheet->AddImage( AddImage ("LandSW", "./Sprite/LandSW.png") );
    imageSheet = AddImageSheet("LandW");
    imageSheet->AddImage( AddImage ("LandW", "./Sprite/LandW.png") );
    imageSheet = AddImageSheet("LandNW");
    imageSheet->AddImage( AddImage ("LandNW", "./Sprite/LandNW.png") );

    imageSheet = AddImageSheet("StoneC");
    imageSheet->AddImage( AddImage ("StoneC", "./Sprite/StoneC.png") );
    imageSheet = AddImageSheet("StoneN");
    imageSheet->AddImage( AddImage ("StoneN", "./Sprite/StoneN.png") );
    imageSheet = AddImageSheet("StoneNE");
    imageSheet->AddImage( AddImage ("StoneNE", "./Sprite/StoneNE.png") );
    imageSheet = AddImageSheet("StoneE");
    imageSheet->AddImage( AddImage ("StoneE", "./Sprite/StoneE.png") );
    imageSheet = AddImageSheet("StoneSE");
    imageSheet->AddImage( AddImage ("StoneSE", "./Sprite/StoneSE.png") );
    imageSheet = AddImageSheet("StoneS");
    imageSheet->AddImage( AddImage ("StoneS", "./Sprite/StoneS.png") );
    imageSheet = AddImageSheet("StoneSW");
    imageSheet->AddImage( AddImage ("StoneSW", "./Sprite/StoneSW.png") );
    imageSheet = AddImageSheet("StoneW");
    imageSheet->AddImage( AddImage ("StoneW", "./Sprite/StoneW.png") );
    imageSheet = AddImageSheet("StoneNW");
    imageSheet->AddImage( AddImage ("StoneNW", "./Sprite/StoneNW.png") );

    imageSheet = AddImageSheet("FoxIdle");
    imageSheet->SetSpeed(15);
    imageSheet->AddImage( AddImage ("FoxIdle1", "./Sprite/FoxIdle1.png") );
    imageSheet->AddImage( AddImage ("FoxIdle2", "./Sprite/FoxIdle2.png") );

    imageSheet = AddImageSheet("FoxWalk");
    imageSheet->SetSpeed(6);
    imageSheet->AddImage( AddImage ("FoxWalk1", "./Sprite/FoxWalk1.png") );
    imageSheet->AddImage( AddImage ("FoxWalk2", "./Sprite/FoxWalk2.png") );
    imageSheet->AddImage( AddImage ("FoxWalk3", "./Sprite/FoxWalk3.png") );
    imageSheet->AddImage( AddImage ("FoxWalk4", "./Sprite/FoxWalk4.png") );
    imageSheet->AddImage( AddImage ("FoxWalk5", "./Sprite/FoxWalk5.png") );
    imageSheet->AddImage( AddImage ("FoxWalk6", "./Sprite/FoxWalk6.png") );
    imageSheet->AddImage( AddImage ("FoxWalk7", "./Sprite/FoxWalk7.png") );

    imageSheet = AddImageSheet("FoxDead");
    imageSheet->AddImage( AddImage ("FoxDead1", "./Sprite/FoxDead1.png") );

    imageSheet = AddImageSheet("FoxJump");
    imageSheet->AddImage( AddImage ("FoxJump", "./Sprite/FoxJump.png") );

    imageSheet = AddImageSheet("FoxLand");
    imageSheet->AddImage( AddImage ("FoxLand", "./Sprite/FoxLand.png") );

    imageSheet = AddImageSheet("RaccoonIdle");
    imageSheet->AddImage( AddImage ("RaccoonIdle1", "./Sprite/RaccoonWalk1.png") );

    imageSheet = AddImageSheet("RaccoonWalk");
    imageSheet->SetSpeed(6);
    imageSheet->AddImage( AddImage ("RaccoonWalk1", "./Sprite/RaccoonWalk1.png") );
    imageSheet->AddImage( AddImage ("RaccoonWalk2", "./Sprite/RaccoonWalk2.png") );
    imageSheet->AddImage( AddImage ("RaccoonWalk3", "./Sprite/RaccoonWalk3.png") );
    imageSheet->AddImage( AddImage ("RaccoonWalk4", "./Sprite/RaccoonWalk4.png") );
    imageSheet->AddImage( AddImage ("RaccoonWalk5", "./Sprite/RaccoonWalk5.png") );
    imageSheet->AddImage( AddImage ("RaccoonWalk6", "./Sprite/RaccoonWalk6.png") );

    imageSheet = AddImageSheet("FrogIdle");
    imageSheet->SetSpeed(6);
    imageSheet->AddImage( AddImage ("FrogIdle1", "./Sprite/FrogIdle1.png") );
    imageSheet->AddImage( AddImage ("FrogIdle2", "./Sprite/FrogIdle2.png") );
    imageSheet->AddImage( AddImage ("FrogIdle3", "./Sprite/FrogIdle3.png") );
    imageSheet->AddImage( AddImage ("FrogIdle4", "./Sprite/FrogIdle4.png") );
    imageSheet->AddImage( AddImage ("FrogIdle5", "./Sprite/FrogIdle5.png") );

    imageSheet = AddImageSheet("FrogWalk");
    imageSheet->AddImage( AddImage ("FrogWalk1", "./Sprite/FrogIdle1.png") );

    imageSheet = AddImageSheet("FrogJump");
    imageSheet->AddImage( AddImage ("FrogJump", "./Sprite/FrogJump.png") );

    imageSheet = AddImageSheet("FrogLand");
    imageSheet->AddImage( AddImage ("FrogLand", "./Sprite/FrogLand.png") );

    imageSheet = AddImageSheet("HawkIdle");
    imageSheet->AddImage( AddImage ("HawkIdle1", "./Sprite/HawkWalk1.png") );

    imageSheet = AddImageSheet("HawkWalk");
    imageSheet->SetSpeed(8);
    imageSheet->AddImage( AddImage ("HawkWalk1", "./Sprite/HawkWalk1.png") );
    imageSheet->AddImage( AddImage ("HawkWalk2", "./Sprite/HawkWalk2.png") );
    imageSheet->AddImage( AddImage ("HawkWalk3", "./Sprite/HawkWalk3.png") );
    imageSheet->AddImage( AddImage ("HawkWalk4", "./Sprite/HawkWalk4.png") );

    imageSheet = AddImageSheet("GrassA");
    imageSheet->AddImage( AddImage ("GrassA", "./Sprite/GrassA.png") );

    imageSheet = AddImageSheet("GrassB");
    imageSheet->AddImage( AddImage ("GrassB", "./Sprite/GrassB.png") );

    imageSheet = AddImageSheet("Diamond");
    imageSheet->SetSpeed(6);
    imageSheet->AddImage( AddImage ("Diamond1", "./Sprite/Diamond1.png") );
    imageSheet->AddImage( AddImage ("Diamond2", "./Sprite/Diamond2.png") );
    imageSheet->AddImage( AddImage ("Diamond3", "./Sprite/Diamond3.png") );
    imageSheet->AddImage( AddImage ("Diamond4", "./Sprite/Diamond4.png") );
    imageSheet->AddImage( AddImage ("Diamond5", "./Sprite/Diamond5.png") );

    imageSheet = AddImageSheet("Cherry");
    imageSheet->SetSpeed(6);
    imageSheet->AddImage( AddImage ("Cherry1", "./Sprite/Cherry1.png") );
    imageSheet->AddImage( AddImage ("Cherry2", "./Sprite/Cherry2.png") );
    imageSheet->AddImage( AddImage ("Cherry3", "./Sprite/Cherry3.png") );
    imageSheet->AddImage( AddImage ("Cherry4", "./Sprite/Cherry4.png") );
    imageSheet->AddImage( AddImage ("Cherry5", "./Sprite/Cherry5.png") );
    imageSheet->AddImage( AddImage ("Cherry6", "./Sprite/Cherry6.png") );

    imageSheet = AddImageSheet("Star");
    imageSheet->SetSpeed(6);
    imageSheet->AddImage( AddImage ("Star1", "./Sprite/Star1.png") );
    imageSheet->AddImage( AddImage ("Star2", "./Sprite/Star2.png") );
    imageSheet->AddImage( AddImage ("Star3", "./Sprite/Star3.png") );
    imageSheet->AddImage( AddImage ("Star4", "./Sprite/Star4.png") );
    imageSheet->AddImage( AddImage ("Star5", "./Sprite/Star5.png") );

    imageSheet = AddImageSheet("Cloud");
    imageSheet->SetSpeed(6);
    imageSheet->AddImage( AddImage ("Cloud1", "./Sprite/Cloud1.png") );
    imageSheet->AddImage( AddImage ("Cloud2", "./Sprite/Cloud2.png") );
    imageSheet->AddImage( AddImage ("Cloud3", "./Sprite/Cloud3.png") );
    imageSheet->AddImage( AddImage ("Cloud4", "./Sprite/Cloud4.png") );
    imageSheet->AddImage( AddImage ("Cloud5", "./Sprite/Cloud5.png") );
    imageSheet->AddImage( AddImage ("Cloud6", "./Sprite/Cloud6.png") );
    imageSheet->AddImage( AddImage ("Cloud7", "./Sprite/Cloud7.png") );

    AddFont("Medium", "./Font/lunchds.ttf", 22, 2);
}

void ResourceH::ResourceDestroy() {
    std::map<std::string, Image*>::iterator it;
    for (it = mapImages.begin(); it != mapImages.end(); ++it) {
        delete it->second;
    }

    mapImages.clear();
}

Image* ResourceH::GetImage(std::string name) {

    std::map<std::string, Image*>::iterator it;
    if ((it = mapImages.find(name)) != mapImages.end()) {
        return it->second;
    }

    return NULL;
}

Image* ResourceH::AddImage(std::string name, std::string fileName) {
    if (GetImage(name) != NULL) {
        return NULL;
    }

    Image* image = new Image (name, fileName);
    mapImages.insert(std::pair<std::string, Image*>(name, image));

    return image;
}

ImageSheet* ResourceH::GetImageSheet(std::string name) {

    std::map<std::string, ImageSheet*>::iterator it;
    if ((it = mapImageSheets.find(name)) != mapImageSheets.end()) {
        return it->second;
    }

    return NULL;
}

ImageSheet* ResourceH::AddImageSheet(std::string name) {
    if (GetImageSheet(name) != NULL) {
        return NULL;
    }

    ImageSheet* imageSheet = new ImageSheet (name);
    mapImageSheets.insert(std::pair<std::string, ImageSheet*>(name, imageSheet));

    return imageSheet;
}

Font* ResourceH::GetFont(std::string name) {

    std::map<std::string, Font*>::iterator it;
    if ((it = mapFonts.find(name)) != mapFonts.end()) {
        return it->second;
    }

    return NULL;
}

Font* ResourceH::AddFont(std::string name, std::string fileName, int fontSize, int outlineSize) {
    if (GetFont(name) != NULL) {
        return NULL;
    }

    Font* font = new Font (name, fileName, fontSize, outlineSize);
    mapFonts.insert(std::pair<std::string, Font*>(name, font));

    return font;
}
