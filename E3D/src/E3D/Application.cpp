#include "Application.h"

#include "UI.h"

namespace E3D {
    Application::Application(std::string title, int width, int height) {
        window = std::make_unique<Window>(std::move(title), width, height);
        UI::Init(window->Handle());
    }

    Application::~Application() {
        UI::Shutdown();
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

                UI::BeginFrame();
                scene->OnImGuiRender();
                UI::EndFrame();
            }

            window->SwapBuffers();
        }
    }
}
