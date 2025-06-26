#pragma once

#include <memory>

#include "Scene.h"
#include "UI.h"
#include "Window.h"

int main(int argc, char** argv);

namespace E3D {
    class Application {
    public:
        Application(std::string title, int width, int height);
        ~Application();
        void SetScene(Scene* newScene);

    private:
        void Run() const;

    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<UI> ui;
        Scene* scene = nullptr;

    private:
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication(int argc, char** argv);
}

