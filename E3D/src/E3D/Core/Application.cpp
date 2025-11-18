#include "Application.h"

#include <format>

#include <imgui.h>

#include "ImGuiLayer.h"
#include "E3D/Graphics/RenderCommand.h"

namespace E3D {
    Application* Application::instance = nullptr;

    Application::Application(const Window::Config& config) : window(config) {
        if (instance)
            panic("Application already exists");
        instance = this;

        window.SetEventCallback([this](Event& event) { return this->OnEvent(event); });

        PushLayer<ImGuiLayer>("ImGuiLayer#");
    }

    Application& Application::Get() { return *instance; }
    Window& Application::GetWindow() { return instance->window; }
    void Application::Stop() { running = false; }

    uint32_t Application::Width() const { return width; }
    uint32_t Application::Height() const { return height; }
    double Application::Time() { return Window::Time(); }

    void Application::PopLayer(const std::string& tag) {
        layerStack.PopLayer(tag);
    }

    void Application::Run() {
        double lastFrame = Time();

        while (running) {
            // Sleep when minimized
            if (minimized) {
                Window::WaitEvents();
                continue;
            }

            layerStack.ProcessPending();

            const double time = Time();
            dt = time - lastFrame;
            lastFrame = time;

            // --- Update ---
            {
                for (auto& [_, layer] : layerStack.Layers())
                    layer->OnUpdate(dt);
            }

            // --- Render ---
            {
                for (auto& [_, layer] : layerStack.Layers())
                    layer->OnRender();
            }


            // --- ImGui ---
            {
                ImGuiLayer::Begin();
                ImGui::Begin("[INFO]");
                for (auto& [tag, layer] : layerStack.Layers()) {
                    if (tag.back() != '#')
                        ImGui::SeparatorText(tag.c_str());
                    layer->OnImGui();
                }
                ImGui::End();
                ImGuiLayer::End();
            }

            window.SwapBuffers();
            Window::PollEvents();
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
            for (auto& [_, layer] : layerStack.Layers()) {
                if (event.handled) return;
                layer->OnEvent(event);
            }
        }
    }
}
