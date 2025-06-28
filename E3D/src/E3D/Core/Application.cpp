#include "Application.h"

#include <format>
#include <iostream>

#include "UI.h"

#include "E3D/Event/EventSystem.h"

namespace E3D {
    Application::Application(std::string title, int width, int height) {
        window = std::make_unique<Window>(std::move(title), width, height);
        EventSystem::Init(window->Handle());
        EventSystem::Register<EventType::WindowClose>(BIND_EVENT_FN(OnClose));

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
                scene->OnUpdate(1.0f);

                UI::BeginFrame();
                scene->OnImGuiRender();
                UI::EndFrame();
            }

            window->SwapBuffers();
        }
    }

    void Application::OnClose() {
        running = false;
    }
}
