#include <iostream>
#include <BGIGame.h>

class TestElement : public BGIGame::GameObject {
public:
    void onLoad() {
        std::cout << "element loaded" << std::endl;
    }
};