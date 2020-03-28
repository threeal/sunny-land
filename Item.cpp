#include "Game.h"
#include "Level.h"

Item::Item(GameObject* gameObject, Type type, int value) {

    isActive = true;
    Level.vectorItems.push_back(this);

    this->gameObject = gameObject;
    this->type = type;
    this->value = value;
}

void Item::Effect(GameObject* gameObject) {

    switch (type) {

    case Type::Score:
        if (this->gameObject != NULL) {
            Mix_PlayChannel(-1, Game.soundPoint, 0);
            Level.AddScore(25);
            if (this->gameObject->type == GameObject::Type::Diamond) {
                Level.AddDiamond(-1);
                if (Level.diamond <= 0) {
                    Level.timer = 60;
                }
            }

            this->gameObject->SetType(GameObject::Type::Star);
        }
        break;
    }

}
