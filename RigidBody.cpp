#include "stdio.h"
#include "Level.h"

RigidBody::RigidBody(GameObject* gameObject, double positionX, double positionY, double moveSpeed, double jumpSpeed, double weight) {

    isActive = true;
    Level.vectorRigidBodies.push_back(this);

    this->gameObject = gameObject;

    this->positionX = positionX;
    this->positionY = positionY;

    this->moveSpeed = moveSpeed;
    this->jumpSpeed = jumpSpeed;
    this->weight = weight;

    this->jumpCount = 0;

    SetForce(0, 0);
    SetGravity(0, 0);
}

void RigidBody::SetForce(double forceX, double forceY) {
    this->forceX = forceX;
    this->forceY = forceY;
}

void RigidBody::AddForce(double forceX, double forceY) {
    this->forceX += forceX;
    this->forceY += forceY;
}

void RigidBody::SetGravity(double gravityX, double gravityY) {
    this->gravityX = gravityX;
    this->gravityY = gravityY;

    AddForce(this->gravityX, this->gravityY);
}

void RigidBody::AddGravity(double gravityX, double gravityY) {
    this->gravityX += gravityX * weight;
    this->gravityY += gravityY * weight;

    AddForce(this->gravityX, this->gravityY);
}

void RigidBody::Move() {

    if (gameObject != NULL) {
        gameObject->collider->ClampForce(this);
    }

    positionX += forceX;
    positionY += forceY;

    SetForce(0, 0);

    if (gameObject != NULL) {
        gameObject->SetRect(positionX, positionY);
    }
}
