#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace E3D {
    Camera::Camera(const glm::vec3& position, const glm::vec3& up, const glm::vec3& orientation) :
        position(position), up(up), orientation(orientation) {
        UpdateViewMatrix();
    }

    void Camera::SetPerspective(const float fovDeg, const float aspect, const float nearPlane, const float farPlane) {
        proj = glm::perspective(glm::radians(fovDeg), aspect, nearPlane, farPlane);
    }

    void Camera::UpdateViewMatrix() { view = glm::lookAt(position, position + orientation, up); }

    const glm::mat4& Camera::GetView() const { return view; }
    const glm::mat4& Camera::GetProjection() const { return proj; }
    const glm::vec3& Camera::GetPosition() const { return position; }
    const glm::vec3& Camera::GetOrientation() const { return orientation; }

    void Camera::SetPosition(const glm::vec3& newPosition) {
        this->position = newPosition;
        UpdateViewMatrix();
    }

    void Camera::SetOrientation(const glm::vec3& newOrientation) {
        this->orientation = newOrientation;
        UpdateViewMatrix();
    }
}
