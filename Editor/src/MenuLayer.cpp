#include "MenuLayer.h"

#include "imgui.h"

MenuLayer::MenuLayer() : currentLayer(nullptr) {
}

void MenuLayer::OnUpdate(float ts) {
    E3D::RenderCommand::Clear(0.2f, 0.2f, 0.2f, 1.0f);
}

void MenuLayer::OnImGuiRender() {
    if (currentLayer) {
        if (ImGui::Button("<-")) {
            E3D::Application::Get().Pop(currentLayer);
            currentLayer = nullptr;
        }
    } else {
        for (const auto &[name, factory]: layerRegistry) {
            if (ImGui::Button(name.c_str())) {
                currentLayer = factory();
                E3D::Application::Get().Push(currentLayer);
            }
        }
    }
}
