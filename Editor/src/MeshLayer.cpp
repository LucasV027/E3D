#include "MeshLayer.h"

#include <format>

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"
#include "objload.h"
#include "glm/gtc/type_ptr.inl"

MeshLayer::MeshLayer() : controller(16.0f / 9.0f, 90.f) {
    previewValue = shadingTypes[shadingIndex];
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

    program->Bind();
    program->SetUniform(
        "mvp", controller.GetCamera().GetProjection() * controller.GetCamera().GetView() * transform.transform);
    program->SetUniform("color", color);
    program->SetUniform("lightDirection", lightDirection);
    program->SetUniform("shadingType", shadingIndex);

    E3D::RenderCommand::SetDepthTest(true);
    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
    E3D::RenderCommand::Draw(*vao, *ibo, *program);
}

void MeshLayer::OnImGuiRender() {
    static bool wireframe = false;
    if (ImGui::Checkbox("Wireframe", &wireframe)) {
        E3D::RenderCommand::SetWireframeMode(wireframe);
    }

    ImGui::SeparatorText("Camera");
    ImGui::Indent();
    const auto pos = controller.GetCamera().GetPosition();
    const auto rot = controller.GetCamera().GetOrientation();
    ImGui::Text("Position (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
    ImGui::Text("Orientation (%.2f, %.2f, %.2f)", rot.x, rot.y, rot.z);
    ImGui::Unindent();

    transform.OnImGuiRender();

    ImGui::SeparatorText("Scene");
    ImGui::Indent();

    if (ImGui::BeginCombo("Shading mode", previewValue.c_str())) {
        for (size_t i = 0; i < shadingTypes.size(); ++i) {
            const bool isSelected = (shadingIndex == static_cast<int>(i));
            if (ImGui::Selectable(shadingTypes[i].c_str(), isSelected)) {
                shadingIndex = i;
                previewValue = shadingTypes[shadingIndex];
            }

            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }

    ImGui::ColorEdit3("Color", glm::value_ptr(color));
    ImGui::SliderFloat3("Light direction", glm::value_ptr(lightDirection), -10.0f, 10.0f, "%.2f");
    ImGui::Unindent();
}


void Transform::OnImGuiRender() {
    ImGui::SeparatorText("Transform");
    ImGui::Indent();

    bool update = false;

    ImGui::SeparatorText("Translation");
    ImGui::Indent();
    update |= ImGui::SliderFloat3("Offset", glm::value_ptr(translation), -100.f, 100.f, "%.2f");
    ImGui::Unindent();

    ImGui::SeparatorText("Rotation");
    ImGui::Indent();
    update |= ImGui::DragFloat3("Axis", glm::value_ptr(rotationAxis), 0.1f, -1.0f, 1.0f, "%.2f");
    update |= ImGui::DragFloat("Angle", &rotationAngle, 1.f, 0.0f, 180.0f, "%.2f");
    ImGui::Unindent();

    ImGui::SeparatorText("Scale");
    ImGui::Indent();
    update |= ImGui::SliderFloat("Factor", &scaleFactor, 0.01f, 10.0f, "%.2f");
    ImGui::Unindent();

    ImGui::Unindent();

    if (update) ReCompute();
}

void Transform::ReCompute() {
    const glm::mat4 T = glm::translate(glm::mat4(1.0f), translation);
    auto R = glm::mat4(1.0f);
    if (glm::length(rotationAxis) > 0.0001f) {
        R = glm::rotate(glm::mat4(1.0f), glm::radians(rotationAngle), rotationAxis);
    }

    const glm::mat4 S = glm::scale(glm::mat4(1.0f), glm::vec3(scaleFactor));
    transform = T * R * S;
}
