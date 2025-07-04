#include "DefaultScene.h"

#include "imgui.h"
#include "glm/gtc/matrix_transform.hpp"

DefaultScene::DefaultScene() : controller(16.0f / 9.0f, 90.f) {
    ////////////////////// CUBE //////////////////////
    cubeVAO.Init();
    cubeVBO.Load(CUBE, sizeof(CUBE));
    cubeVAO.AddBuffer(cubeVBO, {
                          {E3D::AttributeType::Float, 3},
                          {E3D::AttributeType::Float, 3},
                          {E3D::AttributeType::Float, 2}
                      });

    cubeIBO.Load(CUBE_INDICES, 36);

    cubeProgram = E3D::Program::Create(cubeVsPath, cubeVsPath);
    cubeProgram->Bind();
    cubeProgram->SetUniform("texSampler", 0);

    E3D::Texture::Specification specification;
    specification.width = 64;
    specification.height = 64;
    specification.format = E3D::Texture::Format::RGB8;
    specification.wrapModeS = E3D::Texture::WrapMode::Repeat;
    specification.wrapModeT = E3D::Texture::WrapMode::Repeat;
    cubeTexture = std::make_unique<E3D::Texture>(specification);
    cubeTexture->LoadFromFile(ASSETS_DIR "/stone.png");


    ////////////////////// QUAD //////////////////////

    E3D::FrameBuffer::Specification framebufferSpecification;
    framebufferSpecification.width = 1280;
    framebufferSpecification.height = 720;
    fbo = std::make_unique<E3D::FrameBuffer>(framebufferSpecification);

    quadVAO.Init();
    quadVBO.Load(QUAD, sizeof(QUAD));
    quadVAO.AddBuffer(quadVBO, {{E3D::AttributeType::Float, 2}, {E3D::AttributeType::Float, 2}});

    quadProgram = E3D::Program::Create(quadVsPath, quadVsPath);
    quadProgram->Bind();
    quadProgram->SetUniform("screenTexture", 0);

    ////////////////////// Renderer //////////////////////
    E3D::RenderCommand::SetCullFace(true);
}

DefaultScene::~DefaultScene() = default;

void DefaultScene::OnUpdate(const float ts) {
    controller.OnUpdate(ts);

    rotationMatrix = rotate(rotationMatrix, rotationSpeed * ts, normalize(rotationAxis));
    model = rotationMatrix;
    model = glm::scale(model, scale);

    cubeProgram->Bind();
    cubeProgram->SetUniform("mvp", controller.GetCamera().GetProjection() * controller.GetCamera().GetView() * model);

    fbo->Bind();
    E3D::RenderCommand::SetViewPort(0, 0, 1280, 720);

    // First pass
    cubeTexture->Bind();
    E3D::RenderCommand::SetDepthTest(true);
    E3D::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
    E3D::RenderCommand::Draw(cubeVAO, cubeIBO, *cubeProgram);

    E3D::FrameBuffer::Default();
    E3D::RenderCommand::SetViewPort(0, 0, 1280, 720);

    // Second pass
    fbo->BindColorTexture();
    E3D::RenderCommand::SetDepthTest(false);
    E3D::RenderCommand::Draw(quadVAO, 0, 6, *quadProgram);
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
    ImGui::NewLine();
    static bool wireframe = false;
    if (ImGui::Checkbox("Wireframe", &wireframe)) {
        E3D::RenderCommand::SetWireframeMode(wireframe);
    }
}
