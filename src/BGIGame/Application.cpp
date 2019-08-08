#include <graphics.h>
#include <BGIGame.h>

using namespace BGIGame;

Scene *Application::m_currentScene = 0;
bool Application::m_initialized = false;
bool Application::m_quit = false;

Application::Application() {
    m_title = "BGI Game";
    setSize(800, 600);
    setPosition(0, 0);
}

Application::~Application() {
    quit();
}

void Application::setTitle(const char *title) {
    m_title = title;
}

void Application::setSize(int width, int height) {
    m_rect.size.x = width;
    m_rect.size.y = height;
}

void Application::setPosition(int x, int y) {
    m_rect.position.x = x;
    m_rect.position.y = y;
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
        m_currentScene->render(0);
        Input::update();
    }

    closegraph();
}

void Application::loadScene(GameObject &scene) {
    delete m_currentScene;
    m_currentScene = &scene;
}

void Application::quit() {
    m_quit = true;
    delete m_currentScene;
    delete Input::getInstance();
}
