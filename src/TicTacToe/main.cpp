#include <BGIGame.h>
#include "scenes/IntroScene.hpp"

int main() {
    // Window setup.
    BGIGame::Application ticTacToe;

    ticTacToe.setTitle("Tic Tac Toe");

    ticTacToe.rect().setSize(600, 600);
    ticTacToe.rect().setPosition(340, 50);

    // Load initial scene.
    IntroScene introScene;
    ticTacToe.start(introScene);
}