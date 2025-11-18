#include "Window.h"

#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "Base.h"

namespace E3D {
    Window::Window(const Config& config) {
        if (windowCount == 0) {
            if (!glfwInit()) {
                std::cerr << "Failed to initialize GLFW" << std::endl;
                return;
            }

            glfwSetErrorCallback(GLFWErrorCallback);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            glfwWindowHint(GLFW_RESIZABLE, config.resizable ? GLFW_TRUE : GLFW_FALSE);
        }

        if (config.fullscreen) {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            // Use native resolution if fullscreen requested
            window = glfwCreateWindow(mode->width, mode->height, config.title.c_str(), monitor, nullptr);
        } else {
            window = glfwCreateWindow(static_cast<int>(config.width),
                                      static_cast<int>(config.height),
                                      config.title.c_str(), nullptr, nullptr);
        }

        if (!window) {
            std::cerr << "Failed to create GLFW window" << std::endl;
            return;
        }

        ++windowCount;
        glfwMakeContextCurrent(window);

        // V-Sync
        glfwSwapInterval(config.vsync ? 1 : 0);

        if (!gladLoadGL(glfwGetProcAddress)) {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return;
        }

        glfwSetFramebufferSizeCallback(window, [](GLFWwindow*, int w, int h) {
            glViewport(0, 0, w, h);
        });

        glfwSetWindowUserPointer(window, this);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            const auto& _this = *static_cast<Window*>(glfwGetWindowUserPointer(window));
            Event e{.type = Event::Resize, .resizeData = {.width = width, .height = height}};
            _this.eventCallback(e);
        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
            const auto& _this = *static_cast<Window*>(glfwGetWindowUserPointer(window));
            Event e{.type = Event::Close};
            _this.eventCallback(e);
        });

        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            const auto& _this = *static_cast<Window*>(glfwGetWindowUserPointer(window));
            Event e{.type = Event::Type::Keyboard, .keyData = {key, scancode, action, mods}};
            _this.eventCallback(e);
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
            const auto& _this = *static_cast<Window*>(glfwGetWindowUserPointer(window));
            Event e{.type = Event::Type::Mouse, .mouseData = {xPos, yPos}};
            _this.eventCallback(e);
        });
    }

    Window::~Window() {
        if (window) {
            glfwDestroyWindow(window);
            windowCount--;
            if (windowCount == 0) glfwTerminate();
        }
    }

    void Window::PollEvents() { glfwPollEvents(); }
    void Window::WaitEvents() { glfwWaitEvents(); }
    void Window::SwapBuffers() const { glfwSwapBuffers(window); }
    void Window::MakeCurrent() const { glfwMakeContextCurrent(window); }
    bool Window::ShouldClose() const { return glfwWindowShouldClose(window); }
    bool Window::IsKeyDown(const int key) const { return glfwGetKey(window, key) == GLFW_PRESS; }

    void Window::SetCursorMode(const CursorMode mode) {
        // clang-format off
        int m = 0;
        switch (mode) {
        case CursorMode::NORMAL: m = GLFW_CURSOR_NORMAL;     break;
        case CursorMode::DISABLED: m = GLFW_CURSOR_DISABLED; break;
        case CursorMode::HIDDEN: m = GLFW_CURSOR_HIDDEN;     break;
        default:
            panic("Invalid Cursor Mode");
        }
        // clang-format on

        glfwSetInputMode(window, GLFW_CURSOR, m);
        currentCursorMode = mode;
    }

    Window::CursorMode Window::GetCursorMode() const {
        return currentCursorMode;
    }

    void Window::SetVSync(const bool enable) const {
        glfwSwapInterval(enable ? 1 : 0);
    }

    void Window::SetEventCallback(const EventCallbackFn& callback) { eventCallback = callback; }

    void Window::GLFWErrorCallback(const int error, const char* description) {
        std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
    }
}
