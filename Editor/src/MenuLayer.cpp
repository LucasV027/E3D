#include "MenuLayer.h"

#include "imgui.h"

MenuLayer::MenuLayer() {}

void MenuLayer::OnUpdate(double ts) {
    E3D::RenderCommand::Clear(0.2f, 0.2f, 0.2f, 1.0f);
}

void MenuLayer::OnImGui() {
    if (!currentLayerTag.empty()) {
        if (ImGui::Button("<-")) {
            E3D::Application::Get().PopLayer(currentLayerTag);
            currentLayerTag.clear();
        }
    } else {
        for (const auto& [name, factory] : layerRegistry) {
            if (ImGui::Button(name.c_str())) {
                factory(currentLayerTag);
            }
        }
    }
}
