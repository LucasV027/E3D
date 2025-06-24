#include "Application.h"

#include "DefaultScene.h"

namespace E3D {
    Application::Application() {
        window = std::make_unique<Window>("E3D", 1280, 720);
        ui = std::make_unique<UI>();
        ui->Init(window->Handle());
        scene = std::make_unique<DefaultScene>();
    }

    Application::~Application() {
        ui->Shutdown();
    }

    void Application::Run() const {
        while (!window->ShouldClose()) {
            window->PollEvents();

            scene->OnUpdate(1.0f);

            ui->BeginFrame();
            scene->OnImGuiRender();
            ui->EndFrame();

            window->SwapBuffers();
        }
    }
}
