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

    // Model data
    const auto &vertices = model.vertex;
    const auto &normals = model.normal;
    const auto &texCoords = model.texCoord;
    const auto &indices = model.faces.at("default");

    std::vector<float> verticesData;
    verticesData.reserve(vertices.size() + normals.size() + texCoords.size());

    for (size_t i = 0; i < vertices.size() / 3; i++) {
        // One time per vertex

        // Positions
        verticesData.push_back(vertices[i * 3 + 0]);
        verticesData.push_back(vertices[i * 3 + 1]);
        verticesData.push_back(vertices[i * 3 + 2]);

        // Normals
        verticesData.push_back(normals[i * 3 + 0]);
        verticesData.push_back(normals[i * 3 + 1]);
        verticesData.push_back(normals[i * 3 + 2]);

        // TexCoords
        verticesData.push_back(texCoords[i * 2 + 0]);
        verticesData.push_back(texCoords[i * 2 + 1]);
    }


    vbo = E3D::VertexBuffer::Create(verticesData, {
                                            {E3D::AttributeType::Float, 3},
                                            {E3D::AttributeType::Float, 3},
                                            {E3D::AttributeType::Float, 2},
                                        });

    ibo = E3D::IndexBuffer::Create(indices);
    vao = E3D::VertexArray::Create(vbo, ibo);

    program = E3D::Program::Create(cubeVsPath, cubeFsPath);
    if (!program) throw std::runtime_error("MeshLayer: Failed to create program");

    E3D::RenderCommand::SetCullFace(true);
}

MeshLayer::~MeshLayer() = default;

void MeshLayer::OnUpdate(const float ts) {
    controller.OnUpdate(ts);

    const auto model = glm::mat4(1.0f);

    program->Bind();
    program->SetUniform("mvp", controller.GetCamera().GetProjection() * controller.GetCamera().GetView() * model);

    E3D::RenderCommand::SetDepthTest(true);
    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
    E3D::RenderCommand::Draw(*vao, *ibo, *program);
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
