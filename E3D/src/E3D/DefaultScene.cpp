#include "DefaultScene.h"

#include "imgui.h"
#include "glad/glad.h"

namespace E3D {
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
}
