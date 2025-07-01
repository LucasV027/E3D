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
        void OnMouseMove(double xpos, double ypos);
        void OnKeyPress(int keyCode, Action action);

    private:
        Camera camera;

        float sensitivity = 0.1f;
        float baseSpeed = 10.0f;
        float boostSpeed = 40.0f;

        bool firstClick = true;
        double lastX = 0, lastY = 0;
        float yaw, pitch;
        bool cursorMode = false;

        float aspectRatio;
        float fov;
        float zoom = 1.0f;

        ListenerHandle<EventType::WindowResize> wrHandle;
        ListenerHandle<EventType::MouseScroll> sHandle;
        ListenerHandle<EventType::MouseMoved> mHandle;
        ListenerHandle<EventType::KeyboardInput> kHandle;
    };
}
