#include <vector>
#include <BGIGame.h>

using namespace BGIGame;

void GameObject::render(double tick) {
    if (!m_loaded) {
        load();
        m_loaded = true;
        renderChildren();
        return;
    }

    update(tick);
    renderChildren(tick);
}

void GameObject::renderChildren(double tick) {
    if (m_children.empty())
    {
        return;
    }

    for (int i = 0; m_children.size(); i++) {
        m_children[i]->render(tick);
    }
}

void GameObject::load() {}
void GameObject::update(double tick) {}