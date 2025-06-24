#pragma once

#include "Window.h"

namespace E3D {
    class UI {
    public:
        void Init(GLFWwindow* window);
        void Shutdown();

        void BeginFrame();
        void EndFrame();
    };
}
