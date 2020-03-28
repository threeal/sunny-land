#include "Game.h"

Input::State Input::GetKeyState(Key key) {
    int i = ((int)key)%keySize;
    return keyState[i];
}

Input::State Input::GetMouseState() {
    return mouseState;
}
