#include "Application.h"

#include <format>

#include "imgui.h"
#include "Timer.h"
#include "UI.h"

#include "E3D/Graphics/RenderCommand.h"

namespace E3D {
    Application* Application::instance = nullptr;

    Application::Application(const Window::Config& config) : window(config) {
        if (instance)
            panic("Application already exists");
        instance = this;

        window.SetEventCallback([this](Event& event) { return this->OnEvent(event); });

        // Important: Initialize ImGui *after* the EventSystem.
        // ImGui's setup appends its own GLFW callbacks to any existing ones,
        // but the EventSystem initialization *overwrites* the GLFW callbacks.
        UI::Init(window.Handle());
    }

    Application::~Application() {
        UI::Shutdown();
    }

    Application& Application::Get() { return *instance; }
    Window& Application::GetWindow() { return instance->window; }
    uint32_t Application::Width() const { return width; }
    uint32_t Application::Height() const { return height; }

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
            window.PollEvents();

            for (auto* layer : layers) layer->OnUpdate(deltaClock.DeltaTime());

            UI::BeginFrame();
            ImGui::Begin("[INFO]");
            ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
            for (auto* layer : layers) layer->OnImGui();
            ImGui::End();
            UI::EndFrame();

            window.SwapBuffers();
        }
    }

    void Application::OnClose() {
        running = false;
    }

    void Application::OnResize(const int width, const int height) {
        if (width == 0 || height == 0) {
            minimized = true;
            return;
        }

        minimized = false;
        this->width = width;
        this->height = height;
    }

    void Application::OnEvent(Event& event) {
        switch (event.type) {
        case Event::Type::Close:
            OnClose();
            break;
        case Event::Type::Resize:
            OnResize(event.resizeData.width, event.resizeData.height);
        default:
            break;
        }

        if (!minimized) {
            for (const auto layer : layers) {
                if (event.handled) return;
                layer->OnEvent(event);
            }
        }
    }
}
