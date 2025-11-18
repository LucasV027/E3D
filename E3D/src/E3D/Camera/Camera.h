#pragma once

#include <glm/glm.hpp>

namespace E3D {
    class Camera {
    public:
        explicit Camera(const glm::vec3& position = {0.f, 0.f, 0.f},
                        const glm::vec3& up = {0.f, 1.f, 0.f},
                        const glm::vec3& orientation = {0.f, 0.f, -1.f});

        void SetPerspective(float fovDeg, uint32_t width, uint32_t height, float nearPlane = 0.1f, float farPlane = 1000.0f);
        void SetPerspective(float fovDeg, float aspect, float nearPlane = 0.1f, float farPlane = 1000.0f);

        void UpdateViewMatrix();

        void SetPosition(const glm::vec3& newPosition);
        void SetOrientation(const glm::vec3& newOrientation);

        const glm::mat4& View() const { return view; }
        const glm::mat4& Proj() const { return proj; }

        const glm::vec3& Position() const { return position; }
        const glm::vec3& Orientation() const { return orientation; }

    private:
        glm::vec3 position;
        glm::vec3 up;
        glm::vec3 orientation;

        glm::mat4 view = glm::mat4(1.f);
        glm::mat4 proj = glm::mat4(1.f);
    };
}
