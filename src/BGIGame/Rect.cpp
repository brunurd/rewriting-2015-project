#include <BGIGame.h>

using namespace BGIGame;

void Rect::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
}

void Rect::setSize(int width, int height) {
    size.x = width;
    size.y = height;
}