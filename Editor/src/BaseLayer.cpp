#include "BaseLayer.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

BaseLayer::BaseLayer() {
    const uint32_t width = E3D::Application::Get().Width();
    const uint32_t height = E3D::Application::Get().Height();

    camera.SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    camera.SetOrientation(glm::vec3(0.0f, 0.0f, -1.f));
    camera.SetPerspective(90.0f, static_cast<float>(width) / static_cast<float>(height));

    controller = E3D::CreateScope<E3D::CameraController>(camera);
    controller->SetSpeed(20.0f);

    cubeVBO = E3D::VertexBuffer::Create(CUBE, {
                                            {E3D::AttributeType::Float, 3},
                                            {E3D::AttributeType::Float, 3},
                                            {E3D::AttributeType::Float, 2}
                                        });

    cubeIBO = E3D::IndexBuffer::Create(CUBE_INDICES);

    cubeVAO = E3D::VertexArray::Create(cubeVBO, cubeIBO);

    cubeProgram = E3D::Program::Create(cubeVsPath, cubeFsPath);
    if (!cubeProgram) throw std::runtime_error("Failed to create cubeProgram");
    cubeProgram->Bind();
    cubeProgram->SetUniform("texSampler", 0);

    E3D::Texture::Specification cubeTextureSpec;
    cubeTextureSpec.width = 64;
    cubeTextureSpec.height = 64;
    cubeTextureSpec.format = E3D::Texture::Format::RGB8;
    cubeTextureSpec.wrapModeS = E3D::Texture::WrapMode::Repeat;
    cubeTextureSpec.wrapModeT = E3D::Texture::WrapMode::Repeat;
    cubeTexture = E3D::CreateScope<E3D::Texture>(cubeTextureSpec);
    cubeTexture->LoadFromFile(ASSETS_DIR "/stone.png");

    E3D::RenderCommand::SetCullFace(true);
}

BaseLayer::~BaseLayer() = default;

void BaseLayer::OnUpdate(const double ts) {
    controller->OnUpdate(ts);

    rotationMatrix = rotate(rotationMatrix, rotationSpeed * (float)ts, normalize(rotationAxis));
    model = rotationMatrix;
    model = glm::scale(model, scale);

    cubeProgram->Bind();
    cubeProgram->SetUniform("mvp", camera.Proj() * camera.View() * model);

    cubeTexture->Bind();
    E3D::RenderCommand::SetDepthTest(true);
    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
    E3D::RenderCommand::Draw(*cubeVAO, *cubeIBO, *cubeProgram);
}

void BaseLayer::OnImGui() {
    ImGui::NewLine();
    ImGui::SliderFloat("Rotation Speed", &rotationSpeed, 0.0f, 100.f);
    ImGui::SliderFloat3("Rotation Axis", &rotationAxis.x, -1.0f, 1.0f);
    ImGui::SliderFloat3("Scale", &scale.x, 1.0f, 10.0f);
    ImGui::NewLine();
    const auto& pos = camera.Position();
    const auto& rot = camera.Orientation();
    ImGui::Text("Position (%.2f, %.2f, %.2f)", pos.x, pos.y, pos.z);
    ImGui::Text("Orientation (%.2f, %.2f, %.2f)", rot.x, rot.y, rot.z);
    ImGui::NewLine();
    static bool wireframe = false;
    if (ImGui::Checkbox("Wireframe", &wireframe)) {
        E3D::RenderCommand::SetWireframeMode(wireframe);
    }
}

void BaseLayer::OnEvent(Event& event) {
    controller->OnEvent(event);
}
