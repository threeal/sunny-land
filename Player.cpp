#include <stdio.h>
#include "Game.h"
#include "Intro.h"
#include "Level.h"

Player::Player(GameObject* gameObject) {
    isActive = true;
    Level.vectorPlayers.push_back(this);

    isDead = false;

    this->gameObject = gameObject;
}

void Player::PlayerControl() {
    if (gameObject == NULL) {
        return;
    }


    if (!isDead) {
        if (gameObject->rect.y - 64 > Level.levelHeight) {
            Mix_PlayChannel(-1, Game.soundHit, 0);
            isDead = true;
            Level.timer = 60;
            AddForce(0, -18);
        }
    }

    if (isDead) {
        if (gameObject->sprite != NULL) {
            gameObject->sprite->SetType(Sprite::Type::None);
        }

        if (Level.timer <= 0) {
            Mix_PlayChannel(-1, Game.soundLose, 0);
            Game.TimeDelay(1000);
            Game.ScreenUpdate();
            Game.scene = Game.Scene::SceneIntro;
            Level.LevelEnd();
            Intro.IntroStart();
        } else {
            Level.timer--;
        }

        return;
    } else if (Level.diamond <= 0) {

        if (Level.timer <= 0) {
            Mix_PlayChannel(-1, Game.soundWin, 0);
            Game.TimeDelay(1000);
            Game.ScreenUpdate();
            Game.scene = Game.Scene::SceneIntro;
            Level.LevelEnd();
            Intro.IntroStart();
            return;
        } else {
            Level.timer--;
        }
    }

    gameObject->MoveIdle();

    if (Game.input.GetKeyState(Input::Key::Left) == Input::State::Async) {
        gameObject->MoveLeft();
    } else if (Game.input.GetKeyState(Input::Key::Right) == Input::State::Async) {
        gameObject->MoveRight();
    }

    if (Game.input.GetKeyState(Input::Key::Jump) == Input::State::Async) {
        gameObject->MoveJump();
    }
}

void Player::PlayerHit(GameObject* gameObject) {
    if (isDead)
        return;

    Mix_PlayChannel(-1, Game.soundHit, 0);
    isDead = true;
    Level.timer = 30;

    if (this->gameObject == NULL || gameObject == NULL)
        return;

    double fx, fy;
    if (this->gameObject->rect.x >= gameObject->rect.x) {
        AddForce(6, -6);
    } else {
        AddForce(-6, -6);
    }
}

void Player::AddForce(double forceX, double forceY) {
    if (gameObject == NULL)
        return;

    RigidBody* rigidBody;
    if ((rigidBody = this->gameObject->rigidBody) == NULL)
        return;

    if (forceY < 0) {
        rigidBody->jumpCount++;
    }

    rigidBody->SetGravity(forceX, forceY);
}
