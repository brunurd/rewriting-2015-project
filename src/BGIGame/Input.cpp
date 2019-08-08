#include <graphics.h>
#include <BGIGame.h>

using namespace BGIGame;

Input *Input::m_instance = nullptr;

Input *Input::getInstance() {
    if (Input::m_instance == nullptr) {
        Input::m_instance = new Input();
    }

    return Input::m_instance;
}

bool Input::keyDown(int key) {
    return Input::getInstance()->m_key == key;
}

bool Input::keyUp(int key) {
    return Input::getInstance()->m_key != key;
}

void Input::update() {
    if (kbhit()) {
        Input::getInstance()->m_key = getch();
    }
}
