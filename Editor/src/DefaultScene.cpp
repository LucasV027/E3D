#include "DefaultScene.h"

#include "imgui.h"

DefaultScene::DefaultScene() = default;
DefaultScene::~DefaultScene() = default;

void DefaultScene::OnUpdate(float ts) {
    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
}

void DefaultScene::OnImGuiRender() {
    ImGui::ShowDemoWindow();
}

void DefaultScene::OnEvent() {}

