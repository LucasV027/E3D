#pragma once

#include <memory>

#include "Base.h"
#include "E3D/Scene/Scene.h"
#include "Window.h"
#include "E3D/Event/EventSystem.h"

int main(int argc, char** argv);

namespace E3D {
    class Application {
    public:
        Application(std::string title, int width, int height);
        ~Application();
        void SetScene(Scene* newScene);

    private:
        void Run() const;
        void OnClose();
        void OnResize(int width, int height);

    private:
        Scope<Window> window;
        ScopedEventListener handler;
        Scene* scene = nullptr;
        bool running = true;

    private:
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication(int argc, char** argv);
}

