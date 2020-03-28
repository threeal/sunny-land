#include <stdio.h>
#include "Game.h"
#include "Level.h"

GameObject::GameObject(int x, int y, Type type) {

    isActive = true;
    Level.vectorGameObjects.push_back(this);

    sprite = NULL;
    rigidBody = NULL;
    collider = NULL;
    item = NULL;
    player = NULL;
    behavior = NULL;

    SetRect(x, y);
    SetType(type);
}

GameObject::~GameObject() {
    if (sprite != NULL) {
        sprite->isActive = false;
    }
    if (rigidBody != NULL) {
        rigidBody->isActive = false;
    }
    if (collider != NULL) {
        collider->isActive = false;
    }
    if (item != NULL) {
        item->isActive = false;
    }
    if (player != NULL) {
        player->isActive = false;
    }
    if (behavior != NULL) {
        behavior->isActive = false;
    }
}

void GameObject::SetDefault() {
    type = Type::None;

    if (sprite != NULL) {
        sprite->isActive = false;
    }
    sprite = NULL;

    if (rigidBody != NULL) {
        rigidBody->isActive = false;
    }
    rigidBody = NULL;

    if (collider != NULL) {
        collider->isActive = false;
    }
    collider = NULL;

    if (item != NULL) {
        item->isActive = false;
    }
    item = NULL;

    if (player != NULL) {
        player->isActive = false;
    }
    player = NULL;

    if (behavior != NULL) {
        behavior->isActive = false;
    }
    behavior = NULL;

    SetRect(rect.x, rect.y);
}

void GameObject::SetType(Type type) {

    SetDefault();

    this->type = type;

    Sprite* newSprite = NULL;
    RigidBody* newRigidBody = NULL;
    Collider* newCollider = NULL;
    Item* newItem = NULL;
    Player* newPlayer = NULL;
    Behavior* newBehavior = NULL;

    switch (this->type) {

    case Type::None:
        isActive = false;
        break;

    case Type::LandC:
    case Type::LandN:
    case Type::LandNE:
    case Type::LandE:
    case Type::LandSE:
    case Type::LandS:
    case Type::LandSW:
    case Type::LandW:
    case Type::LandNW:
        newSprite = new Sprite (rect.x, rect.y);
        if (this->type == Type::LandC) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("LandC"));
        } else if (this->type == Type::LandN) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("LandN"));
        } else if (this->type == Type::LandNE) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("LandNE"));
        } else if (this->type == Type::LandE) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("LandE"));
        } else if (this->type == Type::LandSE) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("LandSE"));
        } else if (this->type == Type::LandS) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("LandS"));
        } else if (this->type == Type::LandSW) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("LandSW"));
        } else if (this->type == Type::LandW) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("LandW"));
        } else if (this->type == Type::LandNW) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("LandNW"));
        }

        newSprite->SetType(Sprite::Type::None);
        SetSprite(newSprite);

        newCollider = new Collider(this, rect.x, rect.y, 32, 32);
        newCollider->isTop = (this->type == Type::LandN || this->type == Type::LandNE || this->type == Type::LandNW);
        SetCollider(newCollider);
        break;

    case Type::StoneC:
    case Type::StoneN:
    case Type::StoneNE:
    case Type::StoneE:
    case Type::StoneSE:
    case Type::StoneS:
    case Type::StoneSW:
    case Type::StoneW:
    case Type::StoneNW:
        newSprite = new Sprite (rect.x, rect.y);
        if (this->type == Type::StoneC) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("StoneC"));
        } else if (this->type == Type::StoneN) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("StoneN"));
        } else if (this->type == Type::StoneNE) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("StoneNE"));
        } else if (this->type == Type::StoneE) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("StoneE"));
        } else if (this->type == Type::StoneSE) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("StoneSE"));
        } else if (this->type == Type::StoneS) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("StoneS"));
        } else if (this->type == Type::StoneSW) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("StoneSW"));
        } else if (this->type == Type::StoneW) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("StoneW"));
        } else if (this->type == Type::StoneNW) {
            newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("StoneNW"));
        }
        newSprite->SetType(Sprite::Type::None);
        SetSprite(newSprite);

        newCollider = new Collider(this, rect.x, rect.y, 32, 32);
        newCollider->isTop = (this->type == Type::StoneN || this->type == Type::StoneNE || this->type == Type::StoneNW);
        SetCollider(newCollider);
        break;

    case Type::Fox:
        newSprite = new Sprite (rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("FoxDead"));
        newSprite->AddImageSheet(Sprite::Type::Idle, Resource.GetImageSheet("FoxIdle"));
        newSprite->AddImageSheet(Sprite::Type::Walk, Resource.GetImageSheet("FoxWalk"));
        newSprite->AddImageSheet(Sprite::Type::Jump, Resource.GetImageSheet("FoxJump"));
        newSprite->AddImageSheet(Sprite::Type::Land, Resource.GetImageSheet("FoxLand"));
        newSprite->SetType(Sprite::Type::Idle);
        SetSprite(newSprite);

        newRigidBody = new RigidBody(this, (double)rect.x, (double)rect.y, 8, 15, 1);
        SetRigidBody(newRigidBody);

        newCollider = new Collider(this, rect.x, rect.y, 40, 48);
        SetCollider(newCollider);

        newPlayer = new Player (this);
        SetPlayer(newPlayer);
        break;

    case Type::Raccoon:
        newSprite = new Sprite (rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::Idle, Resource.GetImageSheet("RaccoonIdle"));
        newSprite->AddImageSheet(Sprite::Type::Walk, Resource.GetImageSheet("RaccoonWalk"));
        newSprite->AddImageSheet(Sprite::Type::Jump, Resource.GetImageSheet("RaccoonIdle"));
        newSprite->AddImageSheet(Sprite::Type::Land, Resource.GetImageSheet("RaccoonIdle"));
        newSprite->SetType(Sprite::Type::Walk);
        SetSprite(newSprite);

        newRigidBody = new RigidBody(this, (double)rect.x, (double)rect.y, 3, 12, 1);
        SetRigidBody(newRigidBody);

        newCollider = new Collider(this, rect.x, rect.y, 42, 44);
        SetCollider(newCollider);

        newBehavior = new Behavior(this, Behavior::Type::Raccoon);
        SetBehavior(newBehavior);
        break;

    case Type::Frog:
        newSprite = new Sprite (rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::Idle, Resource.GetImageSheet("FrogIdle"));
        newSprite->AddImageSheet(Sprite::Type::Walk, Resource.GetImageSheet("FrogIdle"));
        newSprite->AddImageSheet(Sprite::Type::Jump, Resource.GetImageSheet("FrogJump"));
        newSprite->AddImageSheet(Sprite::Type::Land, Resource.GetImageSheet("FrogLand"));
        newSprite->SetType(Sprite::Type::Walk);
        SetSprite(newSprite);

        newRigidBody = new RigidBody(this, (double)rect.x, (double)rect.y, 8, 12, 1);
        SetRigidBody(newRigidBody);

        newCollider = new Collider(this, rect.x, rect.y, 40, 64);
        SetCollider(newCollider);

        newBehavior = new Behavior(this, Behavior::Type::Frog);
        SetBehavior(newBehavior);
        break;

    case Type::Hawk:
        newSprite = new Sprite (rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::Idle, Resource.GetImageSheet("HawkIdle"));
        newSprite->AddImageSheet(Sprite::Type::Walk, Resource.GetImageSheet("HawkWalk"));
        newSprite->AddImageSheet(Sprite::Type::Jump, Resource.GetImageSheet("HawkIdle"));
        newSprite->AddImageSheet(Sprite::Type::Land, Resource.GetImageSheet("HawkIdle"));
        newSprite->SetType(Sprite::Type::Walk);
        SetSprite(newSprite);

        newRigidBody = new RigidBody(this, (double)rect.x, (double)rect.y, 8, 12, 1);
        SetRigidBody(newRigidBody);

        newCollider = new Collider(this, rect.x, rect.y, 40, 64);
        SetCollider(newCollider);

        newBehavior = new Behavior(this, Behavior::Type::Hawk);
        SetBehavior(newBehavior);
        break;

    case Type::Diamond:
        newSprite = new Sprite(rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Diamond"));
        newSprite->SetType(Sprite::Type::None);
        SetSprite(newSprite);

        newCollider = new Collider (this, rect.x, rect.y, 16, 16);
        newCollider->isTrigger = true;
        SetCollider(newCollider);

        newItem = new Item (this, Item::Type::Score, 100);
        SetItem(newItem);
        break;

    case Type::Cherry:
        newSprite = new Sprite(rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Cherry"));
        newSprite->SetType(Sprite::Type::None);
        SetSprite(newSprite);

        newCollider = new Collider (this, rect.x, rect.y, 16, 16);
        newCollider->isTrigger = true;
        SetCollider(newCollider);

        newItem = new Item (this, Item::Type::Score, 50);
        SetItem(newItem);
        break;

    case Type::GrassA:
        newSprite = new Sprite(rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("GrassA"));
        newSprite->SetType(Sprite::Type::None);
        SetSprite(newSprite);
        break;

    case Type::GrassB:
        newSprite = new Sprite(rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("GrassB"));
        newSprite->SetType(Sprite::Type::None);
        SetSprite(newSprite);
        break;

    case Type::Star:
        newSprite = new Sprite(rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Star"));
        newSprite->SetType(Sprite::Type::None);
        SetSprite(newSprite);

        newBehavior = new Behavior(this, Behavior::Type::Particle);
        SetBehavior(newBehavior);
        break;

    case Type::Cloud:
        newSprite = new Sprite(rect.x, rect.y);
        newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Cloud"));
        newSprite->SetType(Sprite::Type::None);
        SetSprite(newSprite);

        newBehavior = new Behavior(this, Behavior::Type::Particle);
        SetBehavior(newBehavior);
        break;

    }
}

void GameObject::SetSprite(Sprite* sprite) {
    this->sprite = sprite;

    rect.w = sprite->rect.w;
    rect.h = sprite->rect.h;

    SetRect(rect.x, rect.y, rect.w, rect.h);
}

void GameObject::SetRigidBody(RigidBody* rigidBody) {
    this->rigidBody = rigidBody;
}

void GameObject::SetCollider(Collider* collider) {
    this->collider = collider;
}

void GameObject::SetItem(Item* item) {
    this->item = item;
}

void GameObject::SetPlayer(Player* player) {
    this->player = player;
}

void GameObject::SetBehavior(Behavior* behavior) {
    this->behavior = behavior;
}

void GameObject::SetRect(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;

    if (player != NULL && !Level.isEditor) {
        SDL_Rect c = Level.rectCamera;

        if (rect.x < c.x + c.w) {
            c.x -= (c.x + c.w) - rect.x;
        } else if (rect.x > c.x + Game.screenWidth - c.w) {
            c.x += rect.x - (c.x + Game.screenWidth - c.w);
        }

        if (rect.y < c.y + c.h) {
            c.y -= (c.y + c.h) - rect.y;
        } else if (rect.y > c.y + Game.screenHeight - c.h) {
            c.y += rect.y - (c.y + Game.screenHeight - c.h);
        }

        Level.SetCamera(c.x, c.y);
    }

    if (sprite != NULL) {
        sprite->rect.x = rect.x - Level.rectCamera.x;
        sprite->rect.y = rect.y - Level.rectCamera.y;
    }

    if (collider != NULL) {
        collider->rect.x = rect.x;
        collider->rect.y = rect.y;
    }
}

void GameObject::SetRect(int x, int y) {
    SetRect(x, y, rect.w, rect.h);
}

void GameObject::MoveIdle() {
    if (rigidBody != NULL) {
        if (rigidBody->jumpCount > 0) {
            if (rigidBody->gravityY >= 0) {
                int w = sprite->rect.w;
                sprite->SetType(Sprite::Type::Land);
                sprite->SetRect(rect.x, rect.y, w, 2);
            }
            else {
                int w = sprite->rect.w;
                sprite->SetType(Sprite::Type::Jump);
                sprite->SetRect(rect.x, rect.y, w, 2);
            }
            return;
        }
        if (rigidBody->forceX != 0 || rigidBody->forceY != 0) {
            return;
        }
        if (rigidBody->gravityX != 0 || rigidBody->gravityY != 0) {
            if (rigidBody->jumpCount <= 0) {
                rigidBody->jumpCount = 1;
            }
            return;
        }
    }

    if (sprite != NULL) {
        int w = sprite->rect.w;
        sprite->SetType(Sprite::Type::Idle);
        sprite->SetRect(rect.x, rect.y, w, 2);
    }
}

void GameObject::MoveLeft() {
    if (rigidBody != NULL) {
        rigidBody->AddForce(-(rigidBody->moveSpeed), 0);

        if (sprite != NULL) {
            if (rigidBody->jumpCount <= 0) {
                sprite->SetType(Sprite::Type::Walk);
            }
            sprite->SetRect(rect.x, rect.y, -2, 2);
        }
    }
}

void GameObject::MoveRight() {
    if (rigidBody != NULL) {
        rigidBody->AddForce(rigidBody->moveSpeed, 0);

        if (sprite != NULL) {
            if (rigidBody->jumpCount <= 0) {
                sprite->SetType(Sprite::Type::Walk);
            }
            sprite->SetRect(rect.x, rect.y, 2, 2);
        }
    }
}

void GameObject::MoveJump() {
    if (rigidBody != NULL) {
        if (rigidBody->jumpCount <= 0) {
            rigidBody->AddGravity(0, -(rigidBody->jumpSpeed));
            rigidBody->jumpCount++;
            Mix_PlayChannel(-1, Game.soundJump, 0);
        }
    }
}
