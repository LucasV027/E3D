#pragma once

#include <E3D.h>

class MeshScene final : public E3D::Scene {
public:
    MeshScene();
    ~MeshScene() override;

    void OnUpdate(float ts) override;
    void OnImGuiRender() override;

private:
    E3D::Ref<E3D::Mesh> mesh;
    E3D::Program program;
    E3D::CameraController controller;

    const std::vector<float> CUBE = {
        // Position (3) |  Color (3)
        0.5f, -0.5f, -0.5f, 1.f, 0.f, 0.f,
        0.5f, -0.5f, 0.5f, 0.f, 1.f, 0.f,
        -0.5f, -0.5f, 0.5f, 0.f, 0.f, 1.f,
        -0.5f, -0.5f, -0.5f, 1.f, 1.f, 0.f,
        0.5f, 0.5f, -0.5f, 1.f, 0.f, 1.f,
        0.5f, 0.5f, 0.5f, 0.f, 1.f, 1.f,
        -0.5f, 0.5f, 0.5f, 1.f, 0.64f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.f, 0.75f, 0.79f
    };

    const std::vector<unsigned int> CUBE_INDICES = {
        1, 2, 3,
        4, 7, 6,
        4, 5, 1,
        1, 5, 6,
        6, 7, 3,
        4, 0, 3,
        0, 1, 3,
        5, 4, 6,
        0, 4, 1,
        2, 1, 6,
        2, 6, 3,
        7, 4, 3
    };

    const std::filesystem::path cubeFsPath = ASSETS_DIR "/mesh.frag";
    const std::filesystem::path cubeVsPath = ASSETS_DIR "/mesh.vert";
};
