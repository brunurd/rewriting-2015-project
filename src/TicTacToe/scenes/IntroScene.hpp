#include <iostream>
#include <BGIGame.h>

class IntroScene : public BGIGame::Scene {
public:
    void load() {}

    void update(double tick) {
        if (BGIGame::Input::keyDown(BGIGame::KeyCode::ESC)) {
            BGIGame::Application::quit();
        }
    }
};