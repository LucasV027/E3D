#include "CameraController.h"

#include "E3D/Event/Input.h"
#include "E3D/Event/KeyCode.h"

namespace E3D {
    CameraController::CameraController(const float aspectRatio, const float fovDeg) :
        aspectRatio(aspectRatio),
        fov(fovDeg) {
        wrHandle = EventSystem::Register<EventType::WindowResize>(BIND_EVENT_FN(OnResize));
        sHandle = EventSystem::Register<EventType::MouseScroll>(BIND_EVENT_FN(OnScroll));
        camera.SetPerspective(fov * zoom, aspectRatio);
    }

    CameraController::~CameraController() {
        EventSystem::Unregister<EventType::WindowResize>(wrHandle);
        EventSystem::Unregister<EventType::MouseScroll>(sHandle);
    }

    Camera& CameraController::GetCamera() { return camera; }

    void CameraController::OnUpdate(const float dt) {
        glm::vec3 pos = camera.GetPosition();
        const glm::vec3 orientation = camera.GetOrientation();
        constexpr glm::vec3 up = {0.f, 1.f, 0.f};

        const float speed = Input::IsKeyPressed(Keyboard::LEFT_SHIFT) ? boostSpeed : baseSpeed;

        if (Input::IsKeyPressed(Keyboard::W))
            pos += dt * speed * orientation;
        if (Input::IsKeyPressed(Keyboard::S))
            pos -= dt * speed * orientation;
        if (Input::IsKeyPressed(Keyboard::D))
            pos += dt * speed * glm::normalize(glm::cross(orientation, up));
        if (Input::IsKeyPressed(Keyboard::A))
            pos -= dt * speed * glm::normalize(glm::cross(orientation, up));
        if (Input::IsKeyPressed(Keyboard::SPACE))
            pos += dt * speed * up;
        if (Input::IsKeyPressed(Keyboard::LEFT_CONTROL))
            pos -= dt * speed * up;

        camera.SetPosition(pos);
    }

    void CameraController::OnResize(const int width, const int height) {
        aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        camera.SetPerspective(fov * zoom, aspectRatio);
    }

    void CameraController::OnScroll(const double offset) {
        if (offset < 0.0f && zoom < 1.5f) {
            zoom += 0.1f;
        } else if (offset > 0.0f && zoom > 0.5f) {
            zoom -= 0.1f;
        } else {
            return;
        }
        camera.SetPerspective(fov * zoom, aspectRatio);
    }
}
