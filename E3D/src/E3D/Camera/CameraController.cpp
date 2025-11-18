#include "CameraController.h"

#include <GLFW/glfw3.h>

#include "E3D/Core/Application.h"

namespace E3D {
    CameraController::CameraController(Camera& camera) : camera(camera) {
        const auto direction = camera.Orientation();
        pitch = glm::degrees(std::asin(direction.y));
        yaw = glm::degrees(std::atan2(direction.z, direction.x));
    }

    void CameraController::SetSpeed(const float speed) { this->speed = speed; }
    float CameraController::GetSpeed() const { return speed; }

    void CameraController::OnEvent(const Event& event) {
        switch (event.type) {
        case Event::Type::Keyboard:
            OnKeyPress(event.keyData.key, event.keyData.scancode, event.keyData.action, event.keyData.mods);
            break;
        case Event::Type::Mouse:
            OnMouseMove(event.mouseData.x, event.mouseData.y);
            break;
        default: break;
        }
    }

    void CameraController::OnUpdate(const float dt) const {
        glm::vec3 pos = camera.Position();
        const glm::vec3 orientation = camera.Orientation();
        constexpr glm::vec3 up = {0.f, 1.f, 0.f};
        const glm::vec3 forward = glm::normalize(glm::vec3{orientation.x, 0.0f, orientation.z});
        const glm::vec3 right = glm::normalize(cross(forward, up));

        auto& window = E3D::Application::GetWindow();
        if (window.IsKeyDown(GLFW_KEY_W)) pos += dt * forward * speed;
        if (window.IsKeyDown(GLFW_KEY_S)) pos -= dt * forward * speed;
        if (window.IsKeyDown(GLFW_KEY_D)) pos += dt * right * speed;
        if (window.IsKeyDown(GLFW_KEY_A)) pos -= dt * right * speed;
        if (window.IsKeyDown(GLFW_KEY_SPACE)) pos += dt * up * speed;
        if (window.IsKeyDown(GLFW_KEY_LEFT_CONTROL)) pos -= dt * up * speed;

        camera.SetPosition(pos);
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

    void CameraController::OnKeyPress(const int key, const int scancode, const int action, const int mods) {
        if (key == GLFW_KEY_C && action == GLFW_PRESS) {
            cursorMode = !cursorMode;
            firstClick = true;
            E3D::Application::GetWindow().SetCursorMode(cursorMode
                                                            ? E3D::Window::CursorMode::DISABLED
                                                            : E3D::Window::CursorMode::NORMAL);
        }
    }
}
