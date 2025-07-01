#include "DefaultScene.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

DefaultScene::DefaultScene() : controller(16.0f / 9.0f, 90.f) {
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

DefaultScene::~DefaultScene() = default;

void DefaultScene::OnUpdate(const float ts) {
    controller.OnUpdate(ts);

    rotationMatrix = rotate(rotationMatrix, rotationSpeed * ts, normalize(rotationAxis));
    model = rotationMatrix;
    model = glm::scale(model, scale);

    program.Bind();
    program.SetUniform("mvp", controller.GetCamera().GetProjection() * controller.GetCamera().GetView() * model);

    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
    E3D::RenderCommand::Draw(vao, ibo, program);
}

void DefaultScene::OnImGuiRender() {
    ImGui::NewLine();
    ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0.0f, 100.f);
    ImGui::SliderFloat3("Rotation Axis", &rotationAxis.x, -1.0f, 1.0f);
    ImGui::SliderFloat3("Scale", &scale.x, 1.0f, 10.0f);
    ImGui::NewLine();
    auto pos = controller.GetCamera().GetPosition();
    auto rot = controller.GetCamera().GetOrientation();
    ImGui::Text("Position (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
    ImGui::Text("Orientation (%.2f, %.2f, %.2f)", rot.x, rot.y, rot.z);
}


