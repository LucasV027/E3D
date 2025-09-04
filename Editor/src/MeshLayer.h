#pragma once

#include <E3D.h>

struct Transform {
    float scaleFactor = 1.0f;
    glm::vec3 translation = glm::vec3(0.0f);
    float rotationAngle = 0.0f;
    glm::vec3 rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 transform = glm::mat4(1.0f);

    void OnImGuiRender();

    void ReCompute();
};

class MeshLayer final : public E3D::Layer {
public:
    MeshLayer();

    ~MeshLayer() override;

    void OnUpdate(float ts) override;

    void OnImGuiRender() override;

private:
    // OpenGL
    E3D::Ref<E3D::VertexBuffer> vbo;
    E3D::Ref<E3D::IndexBuffer> ibo;
    E3D::Ref<E3D::VertexArray> vao;
    E3D::Ref<E3D::Program> program;

    // Model
    Transform transform;

    // UI
    std::string previewValue;
    std::vector<std::string> shadingTypes = {"Basic", "Toon"};

    // Uniforms
    uint32_t shadingIndex = 0;
    glm::vec3 color = glm::vec3(0.2f, 0.6f, 0.4f);
    glm::vec3 lightDirection = glm::vec3(0.0f, 10.0f, 0.0f);

    // Paths
    const std::filesystem::path cubeFsPath = ASSETS_DIR "/mesh.frag";
    const std::filesystem::path cubeVsPath = ASSETS_DIR "/mesh.vert";
    const std::filesystem::path meshPath = ASSETS_DIR "/suzanne.obj";

    // Camera
    E3D::CameraController controller;
};
