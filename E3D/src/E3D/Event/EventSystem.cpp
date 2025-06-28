#include "EventSystem.h"

#include "GLFW/glfw3.h"
#include "imgui.h"

namespace E3D {
    void EventSystem::Init(GLFWwindow* window) {
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int width, int height) {
            Dispatch<EventType::WindowResize>(width, height);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow*) {
            Dispatch<EventType::WindowClose>();
        });

        glfwSetKeyCallback(window, [](GLFWwindow*, int key, int, int action, int) {
            Dispatch<EventType::KeyboardInput>(key, static_cast<Action>(action));
        });

        glfwSetCharCallback(window, [](GLFWwindow*, unsigned int codepoint) {
            Dispatch<EventType::KeyboardChar>(codepoint);
        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow*, int button, int action, int) {
            if (!ImGui::GetIO().WantCaptureMouse) {
                Dispatch<EventType::MouseButton>(button, static_cast<Action>(action));
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow*, double /*xoffset*/, double yoffset) {
            Dispatch<EventType::MouseScroll>(yoffset);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow*, double xpos, double ypos) {
            Dispatch<EventType::MouseMoved>(xpos, ypos);
        });
    }
}
