#include "Application.h"

#define GLFW_INCLUDE_NONE
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "imgui.h"

namespace E3D {
    Application::Application() {
        window = std::make_unique<Window>("E3D", 1280, 720);
        ui = std::make_unique<UI>();
        ui->Init(window->Handle());
    }

    Application::~Application() {
        ui->Shutdown();
    }

    void Application::Run() const {
        while (!window->ShouldClose()) {
            window->PollEvents();

            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            ui->BeginFrame();
            ImGui::ShowDemoWindow();
            ui->EndFrame();

            window->SwapBuffers();
        }
    }
}
