#include "Application.h"

#include "../../../Editor/src/DefaultScene.h"

namespace E3D {
    Application::Application(std::string title, int width, int height) {
        window = std::make_unique<Window>(std::move(title), width, height);
        ui = std::make_unique<UI>();
        ui->Init(window->Handle());
    }

    Application::~Application() {
        ui->Shutdown();
        delete scene;
    }

    void Application::SetScene(Scene* newScene) {
        delete scene;
        scene = newScene;
    }

    void Application::Run() const {
        while (!window->ShouldClose()) {
            window->PollEvents();

            if (scene) {
                scene->OnUpdate(1.0f);

                ui->BeginFrame();
                scene->OnImGuiRender();
                ui->EndFrame();
            }

            window->SwapBuffers();
        }
    }
}
