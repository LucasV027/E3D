#include "MeshLayer.h"

#include <format>

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "objload.h"

MeshLayer::MeshLayer() : controller(16.0f / 9.0f, 90.f) {
    controller.GetCamera().SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));

    obj::Model model;
    try {
        model = std::move(obj::loadModelFromFile(meshPath.string()));
    } catch (const std::exception &) {
        std::cerr << std::format("Failed to load model from {}\n", meshPath.string());
        return;
    }

    const auto &vertices = model.vertex;
    const auto &indices = model.faces.at("default");

    cubeVBO = E3D::VertexBuffer::Create(vertices, {{E3D::AttributeType::Float, 3}});
    cubeIBO = E3D::IndexBuffer::Create(indices);
    cubeVAO = E3D::VertexArray::Create(cubeVBO, cubeIBO);

    cubeProgram = E3D::Program::Create(cubeVsPath, cubeFsPath);
    if (!cubeProgram) throw std::runtime_error("Failed to create cubeProgram");

    E3D::RenderCommand::SetCullFace(true);
}

MeshLayer::~MeshLayer() = default;

void MeshLayer::OnUpdate(const float ts) {
    controller.OnUpdate(ts);

    const auto model = glm::mat4(1.0f);

    cubeProgram->Bind();
    cubeProgram->SetUniform("mvp", controller.GetCamera().GetProjection() * controller.GetCamera().GetView() * model);

    E3D::RenderCommand::SetDepthTest(true);
    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
    E3D::RenderCommand::Draw(*cubeVAO, *cubeIBO, *cubeProgram);
}

void MeshLayer::OnImGuiRender() {
    ImGui::NewLine();
    auto pos = controller.GetCamera().GetPosition();
    auto rot = controller.GetCamera().GetOrientation();
    ImGui::Text("Position (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
    ImGui::Text("Orientation (%.2f, %.2f, %.2f)", rot.x, rot.y, rot.z);
    ImGui::NewLine();
    static bool wireframe = false;
    if (ImGui::Checkbox("Wireframe", &wireframe)) {
        E3D::RenderCommand::SetWireframeMode(wireframe);
    }
}
