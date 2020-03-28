#include <stdio.h>
#include <math.h>
#include "Game.h"
#include "Level.h"

void LevelH::LevelStart() {
    Manager.ManagerDestroy();
    LevelCreate();
}

void LevelH::LevelLoop() {
    if (!isGameOver) {
        if (isEditor) {
            LevelEditor();
        }
        else {
            ManagePlayer();
            ManageBehavior();
            ManageRigidBody();
            ManageCollider();
            ManageItem();
        }

        ManageGameObject();
    }
}

void LevelH::LevelEnd() {
    LevelDestroy();
    Manager.ManagerDestroy();
}

void LevelH::LevelCreate() {

    isEditor = false;
    isGameOver = false;

    levelWidth = 1600;
    levelHeight = 800;

    Sprite* newSprite = new Sprite (0, 0);
    newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Background"));
    newSprite->SetType(Sprite::Type::None);
    newSprite->isTiled = true;
    Background* newBackground = new Background(newSprite, 0, newSprite->rect.y, false);
    newBackground->parallaxX = 0.25;

    newSprite = new Sprite (0, 96);
    newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Foreground"));
    newSprite->SetType(Sprite::Type::None);
    newSprite->isTiled = true;
    newBackground = new Background(newSprite, 0, newSprite->rect.y, false);
    newBackground->parallaxX = 0.75;

    switch (stage) {
        case 1: LevelLoad("./Level/Level1.dat"); break;
        case 2: LevelLoad("./Level/Level2.dat"); break;
    }

    newSprite = new Sprite (0, 0);
    newSprite->AddImageSheet(Sprite::Type::None, Resource.GetImageSheet("Diamond"));
    newSprite->SetType(Sprite::Type::None);
    newBackground = new Background(newSprite, Game.screenWidth - 20, 22, true);
    newBackground->parallaxX = 0;
    newBackground->parallaxY = 0;

    Collider* newCollider = new Collider(NULL, -16, levelHeight/2, 32, levelHeight);
    newCollider->SetLayer(1000);

    newCollider = new Collider(NULL, levelWidth + 16, levelHeight/2, 32, levelHeight);
    newCollider->SetLayer(1000);

    SetCamera(0, 0, 320, 128);

    textScore = new Text(Resource.GetFont("Medium"), 8, 8, "", false);
    textScore->SetColor(255, 255, 255);
    textScore->SetOutlineColor(32, 32, 32);

    textDiamond = new Text(Resource.GetFont("Medium"), Game.screenWidth - 50, 8, "", false);
    textDiamond->SetColor(255, 255, 255);
    textDiamond->SetOutlineColor(32, 32, 32);

    SetScore(score);
    SetDiamond(6);
    timer = 0;
}

void LevelH::LevelDestroy() {
    ClearBehavior();
    ClearPlayer();
    ClearGameObject();
    ClearRigidBody();
    ClearCollider();
    ClearItem();
}

void LevelH::ManageGameObject() {
    std::vector<GameObject*>::iterator it = vectorGameObjects.begin();

    while (it != vectorGameObjects.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorGameObjects.erase(it);
            continue;
        }

        ++it;
    }

    for (GameObject* gameObject : vectorGameObjects) {
        gameObject->SetRect(gameObject->rect.x, gameObject->rect.y);
    }
}

void LevelH::ClearGameObject() {
    for (GameObject* gameObject : vectorGameObjects) {
        delete gameObject;
    }

    vectorGameObjects.clear();
}

void LevelH::ManageRigidBody() {
    std::vector<RigidBody*>::iterator it = vectorRigidBodies.begin();

    while (it != vectorRigidBodies.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorRigidBodies.erase(it);
            continue;
        }

        ++it;
    }

    for (RigidBody* rigidBody : vectorRigidBodies) {
        rigidBody->AddGravity(gravityX, gravityY);
    }

    for (RigidBody* rigidBody : vectorRigidBodies) {
        rigidBody->Move();
    }
}

void LevelH::ClearRigidBody() {
    for (RigidBody* rigidBody : vectorRigidBodies) {
        delete rigidBody;
    }

    vectorRigidBodies.clear();
}

void LevelH::ManageCollider() {
    std::vector<Collider*>::iterator it = vectorColliders.begin();

    while (it != vectorColliders.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorColliders.erase(it);
            continue;
        }

        ++it;
    }
}

void LevelH::ClearCollider() {
    for (Collider* collider : vectorColliders) {
        delete collider;
    }

    vectorColliders.clear();
}

void LevelH::ManageItem() {
    std::vector<Item*>::iterator it = vectorItems.begin();

    while (it != vectorItems.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorItems.erase(it);
            continue;
        }

        ++it;
    }

    for (Player* player : vectorPlayers) {
        GameObject* playerObject;
        if ((playerObject = player->gameObject) == NULL) {
            continue;
        }

        if (playerObject->collider == NULL) {
            continue;
        }

        for (Item* item : vectorItems) {
            GameObject* itemObject;
            if ((itemObject = item->gameObject) == NULL) {
                continue;
            }

            if (itemObject->collider == NULL) {
                continue;
            }

            if (playerObject->collider->Collision(itemObject->collider)) {
                item->Effect(playerObject);
            }
        }
    }
}

void LevelH::ClearItem() {
    for (Item* item : vectorItems) {
        delete item;
    }

    vectorItems.clear();
}

void LevelH::ManagePlayer() {
    std::vector<Player*>::iterator it = vectorPlayers.begin();

    while (it != vectorPlayers.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorPlayers.erase(it);
            continue;
        }

        ++it;
    }

    for (Player* player : vectorPlayers) {
        player->PlayerControl();
    }
}

void LevelH::ClearPlayer() {
    for (Player* player : vectorPlayers) {
        delete player;
    }

    vectorPlayers.clear();
}

void LevelH::ManageBehavior() {
    std::vector<Behavior*>::iterator it = vectorBehaviors.begin();

    while (it != vectorBehaviors.end()) {
        if (!((*it)->isActive)) {
            delete (*it);
            it = vectorBehaviors.erase(it);
            continue;
        }

        ++it;
    }

    for (Behavior* behavior : vectorBehaviors) {
        behavior->Update();
    }

    for (Behavior* behavior : vectorBehaviors) {
        if (!behavior->isActive) {
            behavior->End();
        }
    }
}

void LevelH::ClearBehavior() {
    for (Behavior* behavior : vectorBehaviors) {
        delete behavior;
    }

    vectorBehaviors.clear();
}

void LevelH::LevelLoad(std::string fileName) {

    LevelDestroy();

    FILE* file = fopen(fileName.c_str(), "r");

    int n, type, x, y, layer;
    GameObject* gameObject;
    fscanf(file, "%d\n", &n);

    for (int i = 0; i < n; i++) {
        fscanf(file, "%d %d %d %d\n", &type, &x, &y, &layer);
        printf("%d %d %d %d\n", type, x, y, layer);
        gameObject = new GameObject (x, y, (GameObject::Type)type);

        if (gameObject->collider != NULL) {
            gameObject->collider->SetLayer(layer);
        }
    }

    fclose(file);
}

void LevelH::LevelSave(std::string fileName) {
    FILE* file = fopen(fileName.c_str(), "w");

    fprintf(file, "%d\n", vectorGameObjects.size());
    for (GameObject* gameObject : vectorGameObjects) {
        int layer = 0;
        if (gameObject->collider != NULL) {
            layer = gameObject->collider->layer;
        }
        fprintf(file, "%d %d %d %d\n", gameObject->type, gameObject->rect.x, gameObject->rect.y, layer);
    }

    fclose(file);
}

void LevelH::LevelEditor() {
    if (Game.input.GetMouseState() == Input::State::Pressed) {

        int x = ((rectCamera.x + Game.input.mouseX) / 32) * 32;
        int y = ((rectCamera.y + Game.input.mouseY) / 32) * 32;

        for (GameObject* gameObject : vectorGameObjects) {
            if (gameObject->collider != NULL) {
                if (gameObject->collider->Collision(x + 32, y + 32)) {
                    gameObject->isActive = false;
                }
            }
        }

        GameObject* gameObject = new GameObject (x+16, y+16, editorType);

        Collider* collider;
        if ((collider = gameObject->collider) != NULL) {
            collider->SetLayer(editorLayer);
        }
        printf("created at %d %d\n", x, y);
    }

    if (Game.input.GetKeyState(Input::Key::Next1) == Input::State::Pressed) {
        editorType = (GameObject::Type)((editorSize + editorType - 1) % editorSize);
        printf("type %d\n", editorType);
    }

    if (Game.input.GetKeyState(Input::Key::Prev1) == Input::State::Pressed) {
        editorType = (GameObject::Type)((editorSize + editorType + 1) % editorSize);
        printf("type %d\n", editorType);
    }

    if (Game.input.GetKeyState(Input::Key::Next2) == Input::State::Pressed) {
        editorLayer++;
        printf("layer %d\n", editorLayer);
    }

    if (Game.input.GetKeyState(Input::Key::Prev2) == Input::State::Pressed) {
        editorLayer--;
        printf("layer %d\n", editorLayer);
    }

    if (Game.input.GetKeyState(Input::Key::Save) == Input::State::Pressed) {
        printf("Saved\n");
        LevelSave("Level//Level0.dat");
    }

    if (Game.input.GetKeyState(Input::Key::Load) == Input::State::Pressed) {
        printf("Loaded\n");
        LevelLoad("Level//Level0.dat");
    }

    if (Game.input.GetKeyState(Input::Key::Right) == Input::State::Async) {
        SetCamera(rectCamera.x + 6, rectCamera.y, rectCamera.w, rectCamera.h);
    }

    if (Game.input.GetKeyState(Input::Key::Left) == Input::State::Async) {
        SetCamera(rectCamera.x - 6, rectCamera.y, rectCamera.w, rectCamera.h);
    }

    if (Game.input.GetKeyState(Input::Key::Down) == Input::State::Async) {
        SetCamera(rectCamera.x, rectCamera.y + 6, rectCamera.w, rectCamera.h);
    }

    if (Game.input.GetKeyState(Input::Key::Up) == Input::State::Async) {
        SetCamera(rectCamera.x, rectCamera.y - 6, rectCamera.w, rectCamera.h);
    }

}

void LevelH::SetCamera(int x, int y, int offsetX, int offsetY) {
    rectCamera.x = x;
    rectCamera.y = y;
    rectCamera.w = offsetX;
    rectCamera.h = offsetY;

    if (rectCamera.x < 0) {
        rectCamera.x = 0;
    }
    if (rectCamera.y < 0) {
        rectCamera.y = 0;
    }
    if (rectCamera.x + Game.screenWidth > levelWidth) {
        rectCamera.x = levelWidth - Game.screenWidth;
    }
    if (rectCamera.y + Game.screenHeight > levelHeight) {
        rectCamera.y = levelHeight - Game.screenHeight;
    }

}

void LevelH::SetCamera(int x, int y) {
    SetCamera(x, y, rectCamera.w, rectCamera.h);
}

void LevelH::SetScore(int val) {
    score = val;
    char buffer[32];

    sprintf(buffer, "Score: %d", score);
    textScore->SetText(buffer);
}

void LevelH::AddScore(int val) {
    SetScore(score + val);
}

void LevelH::SetDiamond(int val) {
    diamond = val;
    char buffer[32];

    sprintf(buffer, "%d", diamond);
    textDiamond->SetText(buffer);
}

void LevelH::AddDiamond(int val) {
    SetDiamond(diamond + val);
}
