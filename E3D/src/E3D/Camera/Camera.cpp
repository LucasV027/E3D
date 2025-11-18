#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace E3D {
    Camera::Camera(const glm::vec3& position, const glm::vec3& up, const glm::vec3& orientation) :
        position(position),
        up(up),
        orientation(orientation) {
        UpdateViewMatrix();
    }

    void Camera::SetPerspective(const float fovDeg, const uint32_t width, const uint32_t height, const float nearPlane,
                                const float farPlane) {
        SetPerspective(fovDeg, static_cast<float>(width) / static_cast<float>(height), nearPlane, farPlane);
    }

    void Camera::SetPerspective(const float fovDeg, const float aspect, const float nearPlane, const float farPlane) {
        proj = glm::perspective(glm::radians(fovDeg), aspect, nearPlane, farPlane);
    }

    void Camera::UpdateViewMatrix() { view = lookAt(position, position + orientation, up); }

    void Camera::SetPosition(const glm::vec3& newPosition) {
        position = newPosition;
        UpdateViewMatrix();
    }

    void Camera::SetOrientation(const glm::vec3& newOrientation) {
        orientation = newOrientation;
        UpdateViewMatrix();
    }
}
