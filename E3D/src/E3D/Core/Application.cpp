#include "Application.h"

#include <format>

#include "imgui.h"
#include "UI.h"

#include "E3D/Event/EventSystem.h"
#include "E3D/Event/Input.h"
#include "E3D/Graphics/RenderCommand.h"

namespace E3D {
    Application::Application(std::string title, int width, int height) {
        window = std::make_unique<Window>(std::move(title), width, height);
        Input::Init(window->Handle());
        EventSystem::Init(window->Handle());
        EventSystem::Register<EventType::WindowClose>(BIND_EVENT_FN(OnClose));
        EventSystem::Register<EventType::WindowResize>(BIND_EVENT_FN(OnResize));

        // Important: Initialize ImGui *after* the EventSystem.
        // ImGui's setup appends its own GLFW callbacks to any existing ones,
        // but the EventSystem initialization *overwrites* the GLFW callbacks.
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
        while (running) {
            window->PollEvents();

            if (scene) {
                scene->OnUpdate(0.001f);

                UI::BeginFrame();
                ImGui::Begin("[INFO]");
                ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
                scene->OnImGuiRender();
                ImGui::End();
                UI::EndFrame();
            }

            window->SwapBuffers();
        }
    }

    void Application::OnClose() {
        running = false;
    }

    void Application::OnResize(const int width, const int height) {
        RenderCommand::SetViewPort(0, 0, width, height);
    }
}
