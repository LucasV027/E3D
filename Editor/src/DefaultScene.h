#pragma once

#include <E3D.h>

class DefaultScene final : public E3D::Scene {
public:
    DefaultScene();
    ~DefaultScene() override;

    void OnUpdate(float ts) override;

    void OnImGuiRender() override;

private:
    // Cube
    E3D::VertexBuffer cubeVBO;
    E3D::IndexBuffer cubeIBO;
    E3D::VertexArray cubeVAO;
    E3D::Ref<E3D::Program> cubeProgram;
    std::unique_ptr<E3D::Texture> cubeTexture;
    const std::filesystem::path cubeFsPath = ASSETS_DIR "/cube.frag";
    const std::filesystem::path cubeVsPath = ASSETS_DIR "/cube.vert";

    // Post
    E3D::VertexBuffer quadVBO;
    E3D::VertexArray quadVAO;
    E3D::Ref<E3D::Program> quadProgram;
    const std::filesystem::path quadFsPath = ASSETS_DIR "/post.frag";
    const std::filesystem::path quadVsPath = ASSETS_DIR "/post.vert";

    std::unique_ptr<E3D::FrameBuffer> fbo;

    // Camera
    E3D::CameraController controller;

    // Transforms
    glm::mat4 model = glm::mat4(1.0f);
    float rotationSpeed = 0.0f;
    glm::vec3 rotationAxis = glm::vec3(1.0f);
    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    glm::vec3 scale = glm::vec3(1.0f);

    // Geometry
    static constexpr float CUBE[] = {
        // Position (3) | Color (3) | UV (2)
        -0.5f, -0.5f, 0.5f, 1.f, 0.f, 0.f, 0.f, 0.f,
        0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f, 1.f, 0.f,
        0.5f, 0.5f, 0.5f, 0.f, 0.f, 1.f, 1.f, 1.f,
        -0.5f, 0.5f, 0.5f, 1.f, 1.f, 0.f, 0.f, 1.f,
        0.5f, -0.5f, -0.5f, 1.f, 0.f, 1.f, 0.f, 0.f,
        -0.5f, -0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 0.f,
        -0.5f, 0.5f, -0.5f, 1.f, 0.6f, 0.f, 1.f, 1.f,
        0.5f, 0.5f, -0.5f, 1.f, 0.7f, 0.8f, 0.f, 1.f,
        -0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f, 0.f, 0.f,
        -0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f, 1.f, 0.f,
        -0.5f, 0.5f, 0.5f, 0.f, 0.f, 1.f, 1.f, 1.f,
        -0.5f, 0.5f, -0.5f, 1.f, 1.f, 0.f, 0.f, 1.f,
        0.5f, -0.5f, 0.5f, 1.f, 0.f, 1.f, 0.f, 0.f,
        0.5f, -0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 0.f,
        0.5f, 0.5f, -0.5f, 1.f, 0.6f, 0.f, 1.f, 1.f,
        0.5f, 0.5f, 0.5f, 1.f, 0.7f, 0.8f, 0.f, 1.f,
        -0.5f, 0.5f, 0.5f, 1.f, 0.f, 0.f, 0.f, 0.f,
        0.5f, 0.5f, 0.5f, 0.f, 1.f, 0.f, 1.f, 0.f,
        0.5f, 0.5f, -0.5f, 0.f, 0.f, 1.f, 1.f, 1.f,
        -0.5f, 0.5f, -0.5f, 1.f, 1.f, 0.f, 0.f, 1.f,
        -0.5f, -0.5f, -0.5f, 1.f, 0.f, 1.f, 0.f, 0.f,
        0.5f, -0.5f, -0.5f, 0.f, 1.f, 1.f, 1.f, 0.f,
        0.5f, -0.5f, 0.5f, 1.f, 0.6f, 0.f, 1.f, 1.f,
        -0.5f, -0.5f, 0.5f, 1.f, 0.7f, 0.8f, 0.f, 1.f,
    };

    static constexpr unsigned int CUBE_INDICES[] = {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    static constexpr float QUAD[] = {
        // Position (2) | UV (2)
        -1.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
};
