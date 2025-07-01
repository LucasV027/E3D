#include "CameraController.h"

#include "E3D/Event/Input.h"
#include "E3D/Event/KeyCode.h"
#include "GLFW/glfw3.h"

namespace E3D {
    CameraController::CameraController(const float aspectRatio, const float fovDeg) :
        aspectRatio(aspectRatio),
        fov(fovDeg) {
        camera.SetPerspective(fov * zoom, aspectRatio);

        const auto direction = camera.GetOrientation();
        pitch = glm::degrees(std::asin(direction.y));
        yaw = glm::degrees(std::atan2(direction.z, direction.x));

        events.Subscribe<EventType::WindowResize>(BIND_EVENT_FN(OnResize));
        events.Subscribe<EventType::MouseScroll>(BIND_EVENT_FN(OnScroll));
        events.Subscribe<EventType::MouseMoved>(BIND_EVENT_FN(OnMouseMove));
        events.Subscribe<EventType::KeyboardInput>(BIND_EVENT_FN(OnKeyPress));
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

    void CameraController::OnMouseMove(const double xPos, const double yPos) {
        if (!cursorMode) return;

        if (firstClick) {
            lastX = xPos;
            lastY = yPos;
            firstClick = false;
        }

        float xOffset = xPos - lastX;
        float yOffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        xOffset *= sensitivity;
        yOffset *= sensitivity;

        yaw += xOffset;
        pitch += yOffset;

        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camera.SetOrientation(glm::normalize(direction));
    }

    void CameraController::OnKeyPress(const int keyCode, const Action action) {
        if (keyCode == Keyboard::C && action == Action::Press) {
            cursorMode = !cursorMode;
            firstClick = true;
            if (cursorMode) {
                Input::SetCursorMode(GLFW_CURSOR_DISABLED);
            } else {
                Input::SetCursorMode(GLFW_CURSOR_NORMAL);
            }
        }
    }
}
