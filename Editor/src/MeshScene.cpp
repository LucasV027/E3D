#include "MeshScene.h"

#include "glm/gtc/matrix_transform.hpp"
#include "imgui.h"

MeshScene::MeshScene(): controller(16.0f / 9.0f, 90.f) {
    E3D::RenderCommand::SetCullFace(true);

    mesh = E3D::Mesh::Create(
        CUBE,
        {
            {E3D::AttributeType::Float, 3},
            {E3D::AttributeType::Float, 3},
        },
        CUBE_INDICES
    );

    program.Init();
    program.Attach(E3D::ShaderType::Vertex, cubeVsPath);
    program.Attach(E3D::ShaderType::Fragment, cubeFsPath);
    program.Link();
}

MeshScene::~MeshScene() = default;

void MeshScene::OnUpdate(const float ts) {
    controller.OnUpdate(ts);

    program.Bind();
    program.SetUniform("mvp", controller.GetCamera().GetProjection() * controller.GetCamera().GetView());

    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
    E3D::RenderCommand::Draw(*mesh, program);
}

void MeshScene::OnImGuiRender() {
    const auto pos = controller.GetCamera().GetPosition();
    const auto rot = controller.GetCamera().GetOrientation();
    ImGui::Text("Position (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
    ImGui::Text("Orientation (%.2f, %.2f, %.2f)", rot.x, rot.y, rot.z);
    ImGui::NewLine();
}
