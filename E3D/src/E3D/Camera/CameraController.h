#pragma once

#include "Camera.h"
#include "E3D/Core/Event.h"

namespace E3D {
    class CameraController {
    public:
        explicit CameraController(Camera& camera);
        ~CameraController() = default;

        void SetSpeed(float speed);
        float GetSpeed() const;

        void OnUpdate(float dt) const;
        void OnEvent(const Event& event);

    private:
        void OnMouseMove(double xPos, double yPos);
        void OnKeyPress(int key, int scancode, int action, int mods);

    private:
        Camera& camera;

        float sensitivity = 0.1f;
        float speed = 0.5;

        bool firstClick = true;
        double lastX = 0., lastY = 0.;
        float yaw = 0.f, pitch = 0.f;
        bool cursorMode = false;
    };
}
