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
    cubeTexture = std::make_unique<E3D::Texture>(cubeTextureSpec);
    cubeTexture->LoadFromFile(ASSETS_DIR "/stone.png");


    ////////////////////// QUAD //////////////////////

    rboAttachment = E3D::RenderBuffer::Create(1280, 720, E3D::RenderBuffer::Type::DepthStencil);

    E3D::Texture::Specification texAttachmentSpec;
    texAttachmentSpec.width = 1280;
    texAttachmentSpec.height = 720;
    texAttachmentSpec.format = E3D::Texture::Format::RGBA8;
    texAttachmentSpec.magFilter = E3D::Texture::FilterMode::Linear;
    texAttachmentSpec.minFilter = E3D::Texture::FilterMode::Linear;
    texAttachment = CreateRef<E3D::Texture>(texAttachmentSpec);

    fbo = E3D::FrameBuffer::Builder()
          .WithSize(1280, 720)
          .WithTextureAttachment(E3D::FrameBuffer::Attachment::Color0, texAttachment)
          .WithRenderBufferAttachment(E3D::FrameBuffer::Attachment::DepthStencil, rboAttachment)
          .Build();


    quadVAO.Init();
    quadVBO.Load(QUAD, sizeof(QUAD));
    quadVAO.AddBuffer(quadVBO, {{E3D::AttributeType::Float, 2}, {E3D::AttributeType::Float, 2}});

    quadProgram = E3D::Program::Create(quadVsPath, quadFsPath);
    if (!quadProgram) throw std::runtime_error("Failed to create quadProgram");
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


    fbo->Unbind();
    E3D::RenderCommand::SetViewPort(0, 0, 1280, 720);

    // Second pass
    texAttachment->Bind();
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
