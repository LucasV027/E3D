#pragma once

#include "Camera.h"
#include "E3D/Event/EventSystem.h"

namespace E3D {
    class CameraController {
    public:
        explicit CameraController(float aspectRatio, float fovDeg);
        ~CameraController();

        Camera& GetCamera();

        void OnUpdate(float dt);

    private:
        void OnResize(int width, int height);
        void OnScroll(double offset);

    private:
        Camera camera;

        float sensitivity = 100.0f;
        float baseSpeed = 10.0f;
        float boostSpeed = 40.0f;
        bool firstClick = true;

        float aspectRatio;
        float fov;
        float zoom = 1.0f;

        ListenerHandle<EventType::WindowResize> wrHandle;
        ListenerHandle<EventType::MouseScroll> sHandle;
    };
}
