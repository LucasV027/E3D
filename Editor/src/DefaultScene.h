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
    E3D::ListenerHandle<E3D::EventType::WindowResize> handle;
};

