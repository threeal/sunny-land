#include "Game.h"
#include "Level.h"

Behavior::Behavior(GameObject* gameObject, Type type) {
    isActive = true;
    Level.vectorBehaviors.push_back(this);

    bA = true;

    this->gameObject = gameObject;
    this->type = type;
}

void Behavior::Update() {

    switch (type) {
    case Type::Raccoon:     RaccoonUpdate(); EnemyUpdate(); break;
    case Type::Frog:        FrogUpdate(); EnemyUpdate(); break;
    case Type::Hawk:        HawkUpdate(); EnemyUpdate(); break;
    case Type::Particle:    ParticleUpdate(); break;
    }
}

void Behavior::EnemyUpdate() {
    for (Player* player : Level.vectorPlayers) {
        if (gameObject == NULL || player->gameObject == NULL)
            continue;

        Collider* colliderA = gameObject->collider;
        Collider* colliderB = player->gameObject->collider;
        if (colliderA == NULL || colliderB == NULL)
            continue;

        RigidBody* rigidBody = gameObject->rigidBody;
        if (rigidBody != NULL) {
            colliderA->rect.x += rigidBody->forceX;
            colliderA->rect.y += rigidBody->forceY;
        }

        if (colliderA->Collision(colliderB)) {
            if (colliderA->Collision(colliderA->rect.x, colliderB->rect.y, colliderA->rect.w, colliderA->rect.h)) {
                player->PlayerHit(gameObject);
            } else {
                Mix_PlayChannel(-1, Game.soundStomp, 0);
                player->AddForce(0, -9);
                EnemyDead();
            }
        }

        if (rigidBody != NULL) {
            colliderA->rect.x -= rigidBody->forceX;
            colliderA->rect.y -= rigidBody->forceY;
        }
    }
}

void Behavior::EnemyDead() {
    isActive = false;
    gameObject->SetType(GameObject::Type::Cloud);
}

void Behavior::RaccoonUpdate() {
    bool isLeft = bA;

    if (gameObject == NULL) {
        return;
    }

    bool land = false;

    int posX = gameObject->rect.x;
    int posY = gameObject->rect.y;

    if (isLeft) {
        posX -= 32;
    } else {
        posX += 32;
    }

    for (Collider* collider : Level.vectorColliders) {
        if (collider == gameObject->collider)
            continue;

        GameObject* go;
        if ((go = collider->gameObject) != NULL) {
            if (go->player != NULL) {
                continue;
            }
        }

        if (collider->Collision(posX, posY)) {
            isLeft = !isLeft;
            break;
        }
        if (!land) {
            if (collider->Collision(posX, posY + 64)) {
                land = true;
            }
        }
    }

    if (!land) {
        isLeft = !isLeft;
    }

    if (isLeft) {
        gameObject->MoveLeft();
    } else {
        gameObject->MoveRight();
    }

    bA = isLeft;
}

void Behavior::FrogUpdate() {
}

void Behavior::HawkUpdate() {
}

void Behavior::ParticleUpdate() {
    Sprite* sprite;
    if ((sprite = gameObject->sprite) == NULL) {
        isActive = false;
        return;
    }

    ImageSheet* imageSheet;
    if ((imageSheet = sprite->GetImageSheet()) == NULL) {
        isActive = false;
        return;
    }

    if (imageSheet->index >= imageSheet->length - 1) {
        isActive = false;
        if (gameObject != NULL) {
            gameObject->isActive = false;
        }
    }
}

void Behavior::End() {

    switch (type) {

    case Type::Raccoon:
        if (this->gameObject != NULL) {
            Level.AddScore(50);
        }
        break;

    case Type::Frog:
        if (this->gameObject != NULL) {
            Level.AddScore(50);
        }
        break;

    case Type::Hawk:
        if (this->gameObject != NULL) {
            Level.AddScore(50);
        }
        break;

    case Type::Particle:
        break;
    }
}
