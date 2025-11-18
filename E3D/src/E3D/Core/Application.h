#pragma once

#include "LayerStack.h"
#include "Window.h"

int main(int argc, char** argv);

namespace E3D {
    class Application {
    public:
        explicit Application(const Window::Config& config);
        ~Application() = default;

        static Application& Get();
        static Window& GetWindow();
        void Stop();

        static double Time();
        uint32_t Width() const;
        uint32_t Height() const;

        template <typename T>
        void PushLayer(const std::string& tag) {
            layerStack.PushLayer<T>(tag);
        }

        void PopLayer(const std::string& tag);

    private:
        void Run();
        void OnClose();
        void OnResize(int width, int height);
        void OnEvent(Event& event);

    private:
        Window window;
        LayerStack layerStack;
        bool running = true;
        bool minimized = false;
        int width, height;
        double dt = 0.0f;

    private:
        static Application* instance;
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication(int argc, char** argv);
}

