#pragma once

#include <functional>
#include <string>

class GLFWwindow;

namespace E3D {
    class Window {
    public:
        Window(std::string _title, int _width, int _height);
        ~Window();

        GLFWwindow* Handle() const;

        void PollEvents();
        void SwapBuffers() const;
        bool ShouldClose() const;
        void Bind() const;

        int Width() const;
        int Height() const;
        const std::string& Title() const;

    private:
        void Init();
        static void GLFWErrorCallback(int error, const char* description);

    private:
        GLFWwindow* window = nullptr;
        std::string title;
        int width, height;

        static int windowCount;
    };
}

