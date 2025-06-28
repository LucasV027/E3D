#include "DefaultScene.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

DefaultScene::DefaultScene() {
    vao.Init();
    vbo.Load(CUBE_COLOR, sizeof(CUBE_COLOR));
    vao.AddBuffer(vbo, {{E3D::AttributeType::Float, 3}, {E3D::AttributeType::Float, 3}});

    ibo.Load(CUBE_COLOR_INDICES, 36);

    program.Init();
    (void)program.Attach(E3D::ShaderType::Vertex, vsPath);
    (void)program.Attach(E3D::ShaderType::Fragment, fsPath);
    (void)program.Link();

    E3D::RenderCommand::SetCullFace(true);
}

DefaultScene::~DefaultScene() {}

void DefaultScene::OnUpdate(const float ts) {
    model = glm::mat4(1.0f);
    rotationMatrix = rotate(rotationMatrix, rotationSpeed * ts, normalize(rotationAxis));
    model = rotationMatrix;
    model = glm::scale(model, scale);

    // program.SetUniform("mvp", glm::identity<4>());

    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
    E3D::RenderCommand::Draw(vao, ibo, program);
}

void DefaultScene::OnImGuiRender() {
    ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0.0f, 10.0f);
    ImGui::SliderFloat3("Rotation Axis", &rotationAxis.x, -1.0f, 1.0f);
    ImGui::SliderFloat3("Scale", &scale.x, 1.0f, 10.0f);
}

void DefaultScene::OnEvent() {}


