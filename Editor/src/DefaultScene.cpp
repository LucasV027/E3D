#include "DefaultScene.h"

#include <format>
#include <iostream>

#include "imgui.h"

DefaultScene::DefaultScene() {
    handle = E3D::EventSystem::Register<E3D::EventType::WindowResize>(BIND_EVENT_FN(OnResize));

    program.Init();
    (void)program.Attach(E3D::ShaderType::Fragment, ASSETS_DIR "main.frag");
    (void)program.Attach(E3D::ShaderType::Vertex, ASSETS_DIR "main.vert");
    (void)program.Link();

    vao.Init();
    vbo.Load(VERTICES, sizeof(VERTICES));
    vao.AddBuffer(vbo, {{E3D::AttributeType::Float, 3}, {E3D::AttributeType::Float, 3}});
}

DefaultScene::~DefaultScene() {
    E3D::EventSystem::Unregister<E3D::EventType::WindowResize>(handle);
}

void DefaultScene::OnUpdate(float ts) {
    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
    E3D::RenderCommand::Draw(vao, 0, 3, program);
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
