#pragma once

#include <memory>

#include "UI.h"
#include "Window.h"

namespace E3D {
    class Application {
    public:
        Application();
        ~Application();

        void Run() const;

    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<UI> ui;
        bool m_Running = true;
    };
}

