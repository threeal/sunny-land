#include <stdio.h>
#include "Game.h"
#include "Level.h"

Collider::Collider(GameObject* gameObject, int x, int y, int w, int h) {

    isActive = true;
    Level.vectorColliders.push_back(this);

    this->gameObject = gameObject;

    isTop = false;
    isTrigger = false;
    SetRect(x, y, w, h);

}

void Collider::SetRect(int x, int y, int w, int h) {
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Collider::SetRect(int x, int y) {
    SetRect(x, y, rect.w, rect.h);
}

void Collider::SetLayer(int layer) {
    this->layer = layer;
}

bool Collider::Collision(int x, int y, int w, int h) {
    return (x + w >= rect.x && x <= rect.x + rect.w && y + h >= rect.y && y <= rect.y + rect.h);
}

bool Collider::Collision(int x, int y) {
    return Collision(x, y, 0, 0);
}

bool Collider::Collision(Collider* collider) {
    return Collision(collider->rect.x, collider->rect.y, collider->rect.w, collider->rect.h);
}

void Collider::ClampForce(RigidBody* rigidBody) {
    if (rigidBody == NULL) {
        return;
    }

    double ax, ay, aw, ah, bx, by, bw, bh, fx, fy;

    ax = rigidBody->positionX;
    ay = rigidBody->positionY;
    aw = ((double)rect.w) / 2;
    ah = ((double)rect.h) / 2;

    int z = 0;
    for (Collider* collider : Level.vectorColliders) {
        z++;
        if (collider == this) {
            continue;
        }

        if (collider->isTrigger) {
            continue;
        }

        if (this->layer > collider->layer && !collider->isTop) {
            continue;
        }

        bx = collider->rect.x;
        by = collider->rect.y;
        bw = ((double)collider->rect.w) / 2;
        bh = ((double)collider->rect.h) / 2;

        if (this->layer <= collider->layer) {

            fx = rigidBody->forceX;
            fy = rigidBody->forceY;

            if ((ay + ah) > (by - bh) && (ay - ah) < (by + bh)) {
                if (SDL_abs(fx) + (aw + bw) > SDL_abs(bx - ax)) {
                    if (bx > ax && fx >= 0) {
                        rigidBody->SetForce((bx - bw) - (ax + aw), rigidBody->forceY);
                        continue;
                    } else if (bx < ax && fx <= 0) {
                        rigidBody->SetForce((bx + bw) - (ax - aw), rigidBody->forceY);
                        continue;
                    }
                }
            }
        }

        if (this->layer <= collider->layer || collider->isTop) {

            fx = rigidBody->forceX;
            fy = rigidBody->forceY;

            if ((ax + aw) > (bx - bw) && (ax - aw) < (bx + bw)) {
                if (SDL_abs(fy) + (ah + bh) > SDL_abs(by - ay)) {
                    if (by > ay && fy >= 0) {
                        rigidBody->SetForce(rigidBody->forceX, (by - bh) - (ay + ah));
                        rigidBody->gravityY = 0;
                        rigidBody->gravityX = 0;
                        rigidBody->jumpCount = 0;

                        if (collider->isTop) {
                            this->SetLayer(collider->layer);
                        }
                        continue;

                    } else if (by < ay && fy <= 0) {
                        if (this->layer <= collider->layer) {
                            rigidBody->SetForce(rigidBody->forceX, (by + bh) - (ay - ah));
                            rigidBody->gravityY = 0;
                            rigidBody->gravityX = 0;
                            continue;
                        }
                    }
                }
            }
        }
    }
}
