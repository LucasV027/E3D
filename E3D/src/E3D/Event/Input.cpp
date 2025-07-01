#include "Input.h"

#include "GLFW/glfw3.h"

namespace E3D {
    GLFWwindow* Input::window = nullptr;

    void Input::Init(GLFWwindow* windowHandle) {
        window = windowHandle;
    }

    bool Input::IsKeyPressed(const int key) {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(const int button) {
        return glfwGetMouseButton(window, button) == GLFW_PRESS;
    }

    glm::vec2 Input::GetMousePosition() {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return {static_cast<float>(xpos), static_cast<float>(ypos)};
    }

    float Input::GetMouseX() {
        return GetMousePosition().x;
    }

    float Input::GetMouseY() {
        return GetMousePosition().y;
    }
}
