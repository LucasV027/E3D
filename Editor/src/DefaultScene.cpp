#include "DefaultScene.h"

// TODO Abstract these includes
#include "imgui.h"
#include "glad/glad.h"

DefaultScene::DefaultScene() = default;
DefaultScene::~DefaultScene() = default;

void DefaultScene::OnUpdate(float ts) {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DefaultScene::OnImGuiRender() {
    ImGui::ShowDemoWindow();
}

void DefaultScene::OnEvent() {}

