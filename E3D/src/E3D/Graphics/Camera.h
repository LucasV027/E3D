#pragma once

#include "glm/glm.hpp"

namespace E3D {
    class Camera {
    public:
        explicit Camera(const glm::vec3& position = {0, 0, 0}, const glm::vec3& up = {0, 1, 0},
                        const glm::vec3& orientation = {0, 0, -1});

        void SetPerspective(float fovDeg, float aspect, float nearPlane = 0.01f, float farPlane = 100.0f);
        void UpdateViewMatrix();

        const glm::mat4& GetView() const;
        const glm::mat4& GetProjection() const;
        const glm::vec3& GetPosition() const;
        const glm::vec3& GetOrientation() const;

        void SetPosition(const glm::vec3& newPosition);
        void SetOrientation(const glm::vec3& newOrientation);

    private:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 orientation;

        glm::mat4 view;
        glm::mat4 proj;
    };
}
