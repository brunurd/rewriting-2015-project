#include <BGIGame.h>

using namespace BGIGame;

GameObject::GameObject() {
    m_loaded = false;
    setEnabled(true);
}

void GameObject::render(double tick) {
    if (!m_enabled) {
        return;
    }

    if (!m_loaded) {
        onLoad();
        m_loaded = true;
        renderChildren();
        return;
    }

    onUpdate(tick);
    renderChildren(tick);
}

void GameObject::renderChildren(double tick) {
    if (m_children.empty()) {
        return;
    }

    for (int i = 0; i < m_children.size(); i++) {
        m_children[i]->render(tick);
    }
}

void GameObject::setEnabled(bool enabled) {
    m_enabled = enabled;
}

void GameObject::onLoad() {}

void GameObject::onUpdate(double tick) {}
