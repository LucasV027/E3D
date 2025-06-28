#pragma once

#include "Camera.h"
#include "E3D/Event/EventSystem.h"

namespace E3D {
    class CameraController {
    public:
        explicit CameraController(float aspectRatio, float fovDeg);
        ~CameraController();

        Camera& GetCamera();

    private:
        void OnResize(int width, int height);
        void OnScroll(double offset);

    private:
        Camera camera;

        float aspectRatio;
        float fov;
        float zoom = 1.0f;

        ListenerHandle<EventType::WindowResize> wrHandle;
        ListenerHandle<EventType::MouseScroll> sHandle;
    };
}
