#pragma once

#include <E3D.h>

class MeshLayer final : public E3D::Layer {
public:
    MeshLayer();
    ~MeshLayer() override;

    void OnUpdate(float ts) override;

    void OnImGuiRender() override;

private:
    E3D::Ref<E3D::VertexBuffer> cubeVBO;
    E3D::Ref<E3D::IndexBuffer> cubeIBO;
    E3D::Ref<E3D::VertexArray> cubeVAO;
    E3D::Ref<E3D::Program> cubeProgram;

    const std::filesystem::path cubeFsPath = ASSETS_DIR "/mesh.frag";
    const std::filesystem::path cubeVsPath = ASSETS_DIR "/mesh.vert";
    const std::filesystem::path meshPath = ASSETS_DIR "/suzanne.obj";

    // Camera
    E3D::CameraController controller;
};
