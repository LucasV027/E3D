#pragma once

#include <E3D.h>

class MeshLayer final : public E3D::Layer {
public:
    MeshLayer();
    ~MeshLayer() override;

    void OnUpdate(float ts) override;

    void OnImGuiRender() override;

private:
    E3D::Ref<E3D::VertexBuffer> vbo;
    E3D::Ref<E3D::IndexBuffer> ibo;
    E3D::Ref<E3D::VertexArray> vao;
    E3D::Ref<E3D::Program> program;

    const std::filesystem::path cubeFsPath = ASSETS_DIR "/mesh.frag";
    const std::filesystem::path cubeVsPath = ASSETS_DIR "/mesh.vert";
    const std::filesystem::path meshPath = ASSETS_DIR "/suzanne.obj";

    // Camera
    E3D::CameraController controller;
};
