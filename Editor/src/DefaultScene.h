#pragma once

#include <E3D.h>

class DefaultScene final : public E3D::Scene {
public:
    DefaultScene();
    ~DefaultScene() override;

    void OnUpdate(float ts) override;

    void OnImGuiRender() override;

    void OnEvent() override;

    void OnResize(int newWidth, int newHeight);

private:
    E3D::Program program;
    E3D::VertexArray vao;
    E3D::VertexBuffer vbo;
    E3D::ListenerHandle<E3D::EventType::WindowResize> handle;

    static constexpr float VERTICES[] = {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
    };
};

