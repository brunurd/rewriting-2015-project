#include <BGIGame.h>

using namespace BGIGame;

Scene *Application::m_currentScene = 0;
bool Application::m_initialized = false;
bool Application::m_quit = false;

Rect &Application::rect() {
    return m_rect;
}

Application::Application() {
    m_title = "BGI Game";
    rect().setSize(800, 600);
    rect().setPosition(0, 0);
}

Application::~Application() {
    quit();
}

void Application::setTitle(const char *title) {
    m_title = title;
}

void Application::init() {
    if (!m_initialized) {
        initwindow(m_rect.size.x, m_rect.size.y, m_title, m_rect.position.x, m_rect.position.y);
        m_initialized = true;
    }
}

void Application::start(GameObject &scene) {
    init();

    m_currentScene = &scene;

    while (!m_quit) {
        Timer timer;
        m_currentScene->render(Timer::tick);
        Input::update();
    }

    closegraph();
    delete m_currentScene;
    delete Input::getInstance();
}

void Application::quit() {
    m_quit = true;
}
