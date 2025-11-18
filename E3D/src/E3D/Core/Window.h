#pragma once

#include <cstdint>
#include <string>
#include <functional>

#include "Event.h"

class GLFWwindow;

namespace E3D {
    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        struct Config {
            std::string title = "OpenGL Window";
            uint32_t width = 800;
            uint32_t height = 600;
            bool fullscreen = false;
            bool resizable = true;
            bool vsync = true;
        };

        explicit Window(const Config& config);
        ~Window();

        GLFWwindow* Handle() const { return window; }

        static void PollEvents();
        static void WaitEvents();
        void SwapBuffers() const;
        void MakeCurrent() const;
        bool ShouldClose() const;

        bool IsKeyDown(int key) const;

        enum class CursorMode { NORMAL, DISABLED, HIDDEN };
        void SetCursorMode(CursorMode mode);
        CursorMode GetCursorMode() const;
        void SetVSync(bool enable) const;

        void SetEventCallback(const EventCallbackFn& callback);

    private:
        static void GLFWErrorCallback(int error, const char* description);

    private:
        GLFWwindow* window = nullptr;
        EventCallbackFn eventCallback;
        CursorMode currentCursorMode = CursorMode::NORMAL;

        inline static int windowCount = 0;
    };
}

