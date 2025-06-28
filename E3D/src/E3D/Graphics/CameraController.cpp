#include "CameraController.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "E3D/Event/EventSystem.h"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

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
