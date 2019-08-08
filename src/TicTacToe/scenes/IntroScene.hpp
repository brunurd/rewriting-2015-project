#include <iostream>
#include <BGIGame.h>
#include "../elements/TestElement.hpp"

class IntroScene : public BGIGame::Scene {
public:
    void onLoad() {
        std::cout << "scene loaded" << std::endl;
    }

    void onUpdate(double tick) {
        std::cout << tick << std::endl;

        if (BGIGame::Input::keyDown(BGIGame::KeyCode::ENTER)) {
            // TODO: Load other scene.
        }

        if (BGIGame::Input::keyDown(BGIGame::KeyCode::ESC)) {
            BGIGame::Application::quit();
        }
    }
};