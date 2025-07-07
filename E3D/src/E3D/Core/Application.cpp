#include "Application.h"

#include <format>

#include "imgui.h"
#include "Timer.h"
#include "UI.h"

#include "E3D/Event/EventSystem.h"
#include "E3D/Event/Input.h"
#include "E3D/Graphics/RenderCommand.h"

namespace E3D {
    Application* Application::instance = nullptr;

    Application::Application(std::string title, int width, int height) {
        if (instance) panic("Application already exists");
        instance = this;

        window = CreateScope<Window>(std::move(title), width, height);
        Input::Init(window->Handle());
        EventSystem::Init(window->Handle());
        handler.Subscribe<EventType::WindowClose>(BIND_EVENT_FN(OnClose));
        handler.Subscribe<EventType::WindowResize>(BIND_EVENT_FN(OnResize));

        // Important: Initialize ImGui *after* the EventSystem.
        // ImGui's setup appends its own GLFW callbacks to any existing ones,
        // but the EventSystem initialization *overwrites* the GLFW callbacks.
        UI::Init(window->Handle());
    }

    Application::~Application() {
        UI::Shutdown();
    }

    Application& Application::Get() { return *instance; }

    void Application::Push(Layer* layer) {
        layers.PushLayer(layer);
    }

    void Application::Pop(Layer* layer) {
        layers.PopLayer(layer);
    }

    void Application::Run() const {
        Timer deltaClock;
        deltaClock.Start();

        while (running) {
            deltaClock.Update();
            window->PollEvents();

            for (auto* layer : layers) layer->OnUpdate(deltaClock.DeltaTime());

            UI::BeginFrame();
            ImGui::Begin("[INFO]");
            ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
            for (auto* layer : layers) layer->OnImGuiRender();
            ImGui::End();
            UI::EndFrame();

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
