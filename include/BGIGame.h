#ifndef BGI_GAME
#define BGI_GAME

#include <vector>
#include <string>
#include <graphics.h>
#include <windows.h>

#ifndef nullptr
#define nullptr 0
#endif //nullptr

namespace BGIGame {
    struct Point {
        int x;
        int y;
    };

    struct Rect {
        Point position;
        Point size;
    };

    struct KeyCode {
        static int const ENTER = 13;
        static int const ESC = 27;
    };

    class Timer {
    private:
        LARGE_INTEGER m_startingTime;
        LARGE_INTEGER m_endingTime;
        LARGE_INTEGER m_frequency;

        void stop();

    public:
        static double tick;

        Timer();

        ~Timer();
    };

    class Component {
    };

    class GameObject {
    private:
        std::vector<Component> m_components;
        std::vector<GameObject *> m_children;
        bool m_loaded;
        bool m_enabled;
        std::string m_name;

    public:
        GameObject();

        void render(double tick = 0);

        void renderChildren(double tick = 0);

        void setEnabled(bool enabled);

        virtual void onLoad();

        virtual void onUpdate(double tick);
    };

    typedef GameObject Scene;

    class Application {
    private:
        static Scene *m_currentScene;
        const char *m_title;
        Rect m_rect;
        static bool m_initialized;
        static bool m_quit;

        void init();

    public:
        Application();

        ~Application();

        void setTitle(const char *title);

        void setSize(int width, int height);

        void setPosition(int x, int y);

        void start(Scene &scene);

        static void quit();
    };

    class Input {
    private:
        static Input *m_instance;

    public:
        int m_key;

        static Input *getInstance();

        static bool keyDown(int key);

        static bool keyUp(int key);

        static void update();
    };
}

#endif //BGI_GAME
