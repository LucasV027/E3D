#pragma once

#include "Window.h"

namespace E3D {
    class UI {
    public:
        static void Init(GLFWwindow* window);
        static void Shutdown();

        static void BeginFrame();
        static void EndFrame();
    };
}
