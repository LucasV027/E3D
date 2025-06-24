#include "Window.h"

#include <iostream>

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Base.h"

namespace E3D {
    int Window::windowCount = 0;

    Window::Window(std::string _title, const int _width, const int _height) : title(std::move(_title)),
                                                                              width(_width),
                                                                              height(_height) {
        Init();
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        windowCount--;
        if (windowCount == 0) glfwTerminate();
    }

    GLFWwindow* Window::Handle() const { return window; }

    void Window::PollEvents() { glfwPollEvents(); }
    void Window::SwapBuffers() const { glfwSwapBuffers(window); }
    bool Window::ShouldClose() const { return glfwWindowShouldClose(window); }
    void Window::Bind() const { glfwMakeContextCurrent(window); }
    int Window::Width() const { return width; }
    int Window::Height() const { return height; }
    const std::string& Window::Title() const { return title; }

    void Window::Init() {
        if (windowCount == 0) {
            const int success = glfwInit();
            if (!success) panic("Failed to initialize GLFW");

            glfwSetErrorCallback(GLFWErrorCallback);
        }

        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        ++windowCount;

        glfwMakeContextCurrent(window);
        const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!status) panic("Failed to initialize GLAD");
    }

    void Window::GLFWErrorCallback(int error, const char* description) {
        std::cerr << "GLFW Error (" << error << "): " << description << std::endl;
    }
}

