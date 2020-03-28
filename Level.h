#ifndef LEVEL_H
#define LEVEL_H

#include <SDL.h>
#include <string>
#include <vector>
#include "Resource.h"
#include "Manager.h"

class GameObject;
class RigidBody;
class Collider;
class Item;
class Player;
class Behavior;
class LevelH;

class GameObject {

public:

    enum Type {
        None,
        LandC, LandN, LandNE, LandE, LandSE, LandS, LandSW, LandW, LandNW,
        StoneC, StoneN, StoneNE, StoneE, StoneSE, StoneS, StoneSW, StoneW, StoneNW,
        Fox, Raccoon, Frog, Hawk,
        Diamond, Cherry,
        GrassA, GrassB, Star, Cloud
    };

    bool isActive;

    Type type;
    SDL_Rect rect;

    Sprite* sprite;
    RigidBody* rigidBody;
    Collider* collider;
    Item* item;
    Player* player;
    Behavior* behavior;

    GameObject(int x, int y, Type type);
    ~GameObject();

    void SetDefault ();
    void SetType (Type type);

    void SetSprite (Sprite* sprite);
    void SetRigidBody (RigidBody* rigidBody);
    void SetCollider (Collider* collider);
    void SetItem (Item* item);
    void SetPlayer (Player* player);
    void SetBehavior (Behavior* behavior);

    void SetRect (int x, int y, int w, int h);
    void SetRect (int x, int y);

    void MoveIdle ();
    void MoveLeft ();
    void MoveRight ();
    void MoveJump ();

};

class RigidBody {

public:

    bool isActive;
    GameObject* gameObject;

    int layer;

    double positionX;
    double positionY;
    double forceX;
    double forceY;

    double moveSpeed;
    double jumpSpeed;

    int jumpCount;

    double weight;
    double gravityX;
    double gravityY;

    RigidBody (GameObject* gameObject, double positionX, double positionY, double moveSpeed, double jumpSpeed, double weight);

    void SetForce (double forceX, double forceY);
    void AddForce (double forceX, double forceY);
    void SetGravity (double gravityX, double gravityY);
    void AddGravity (double gravityX, double gravityY);
    void Move ();

};

class Collider {

public:

    bool isActive;
    GameObject* gameObject;

    SDL_Rect rect;

    bool isTrigger;
    bool isTop;
    int layer;

    Collider (GameObject* gameObject, int x, int y, int w, int h);

    void SetRect (int x, int y, int w, int h);
    void SetRect (int x, int y);
    void SetLayer (int layer);

    bool Collision (int x, int y, int w, int h);
    bool Collision (int x, int y);
    bool Collision (Collider* Collider);
    void ClampForce (RigidBody* rigidBody);

};

class Item {

public:

    bool isActive;
    GameObject* gameObject;

    enum Type {
        Score
    };

    Type type;
    int value;

    Item (GameObject* gameObject, Type type, int value);
    void Effect (GameObject* gameObject);
};

class Player {

public:

    bool isActive;
    GameObject* gameObject;

    bool isDead;

    Player (GameObject* gameObject);

    void PlayerControl ();
    void PlayerHealth ();

    void PlayerHit (GameObject* gameObject);
    void AddForce (double forceX, double forceY);
};

class Behavior {

private:
    void EnemyUpdate ();
    void EnemyDead ();

    void RaccoonUpdate ();
    void FrogUpdate ();
    void HawkUpdate ();
    void ParticleUpdate ();

public:

    bool isActive;
    GameObject* gameObject;

    enum Type {
        Raccoon, Frog, Hawk, Particle
    };

    Type type;

    bool bA;

    Behavior (GameObject* gameObject, Type type);

    void Update ();
    void End ();
};

class LevelH {

private:

    const double gravityX = 0;
    const double gravityY = 1;

    GameObject::Type editorType = GameObject::Type::None;
    int editorSize = 29;
    int editorLayer = 0;

    Text* textScore;
    Text* textDiamond;

public:

    bool isEditor;
    bool isGameOver;

    SDL_Rect rectCamera;
    int score = 0;
    int diamond = 0;

    int stage = 0;
    int life = 0;

    int timer = 0;

    int levelWidth;
    int levelHeight;

    std::vector<GameObject*> vectorGameObjects;
    std::vector<RigidBody*> vectorRigidBodies;
    std::vector<Collider*> vectorColliders;
    std::vector<Item*> vectorItems;
    std::vector<Player*> vectorPlayers;
    std::vector<Behavior*> vectorBehaviors;

    void LevelStart ();
    void LevelLoop ();
    void LevelEnd ();

    void LevelCreate ();
    void LevelDestroy ();

    void ManageGameObject ();
    void ClearGameObject ();

    void ManageRigidBody ();
    void ClearRigidBody ();

    void ManageCollider ();
    void ClearCollider ();

    void ManageItem ();
    void ClearItem ();

    void ManagePlayer ();
    void ClearPlayer ();

    void ManageBehavior ();
    void ClearBehavior ();

    void LevelLoad (std::string fileName);
    void LevelSave (std::string fileName);
    void LevelEditor ();

    void SetCamera (int x, int y, int offsetX, int offsetY);
    void SetCamera (int x, int y);

    void SetScore (int val);
    void AddScore (int val);

    void SetDiamond (int val);
    void AddDiamond (int val);
};

extern LevelH Level;

#endif // LEVEL_H
