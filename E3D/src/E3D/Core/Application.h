#pragma once

#include <memory>

#include "Base.h"
#include "Layer.h"
#include "Window.h"
#include "E3D/Event/EventSystem.h"

int main(int argc, char** argv);

namespace E3D {
    class Application {
    public:
        Application(std::string title, int width, int height);
        ~Application();
        static Application& Get();

        void Push(Layer* layer);
        void Pop(Layer* layer);

    private:
        void Run() const;
        void OnClose();
        void OnResize(int width, int height);

    private:
        Scope<Window> window;
        ScopedEventListener handler;
        LayerStack layers;
        bool running = true;

    private:
        static Application* instance;
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication(int argc, char** argv);
}

