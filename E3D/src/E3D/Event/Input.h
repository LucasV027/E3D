#pragma once

#include "glm/glm.hpp"

#include "E3D/Core/Window.h"

namespace E3D {
    class Input {
    public:
        static void Init(GLFWwindow* windowHandle);

        static bool IsKeyPressed(int key);
        static bool IsMouseButtonPressed(int button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();

        // TODO: Put this somewhere else?
        static void SetCursorMode(int mode);

    private:
        static GLFWwindow* window;
    };
}
