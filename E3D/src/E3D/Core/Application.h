#pragma once

#include "Layer.h"
#include "Window.h"

int main(int argc, char** argv);

namespace E3D {
    class Application {
    public:
        explicit Application(const Window::Config& config);
        ~Application();

        static Application& Get();
        static Window& GetWindow();
        uint32_t Width() const;
        uint32_t Height() const;

        void Push(Layer* layer);
        void Pop(Layer* layer);

    private:
        void Run() const;
        void OnClose();
        void OnResize(int width, int height);
        void OnEvent(Event& event);

    private:
        Window window;
        LayerStack layers;
        bool running = true;
        bool minimized = false;
        int width, height;

    private:
        static Application* instance;
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication(int argc, char** argv);
}

