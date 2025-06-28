#include "DefaultScene.h"

#include <format>
#include <iostream>

#include "imgui.h"

DefaultScene::DefaultScene() {
    handle = E3D::EventSystem::Register<E3D::EventType::WindowResize>(BIND_EVENT_FN(OnResize));
}

DefaultScene::~DefaultScene() {
    E3D::EventSystem::Unregister<E3D::EventType::WindowResize>(handle);
}

void DefaultScene::OnUpdate(float ts) {
    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
}

void DefaultScene::OnImGuiRender() {
    ImGui::Begin("[INFO]");
    ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
    ImGui::End();
}

void DefaultScene::OnEvent() {}

void DefaultScene::OnResize(int newWidth, int newHeight) {
    std::cout << std::format("DefaultScene::OnResize ({} {})", newWidth, newHeight) << std::endl;
}
