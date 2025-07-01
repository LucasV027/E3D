#include "Timer.h"

#include "GLFW/glfw3.h"

namespace E3D {
    void Timer::Start() {
        currentFrame = glfwGetTime();
        lastFrame = currentFrame;
        deltaTime = 0.;
    }

    void Timer::Update() {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }

    double Timer::DeltaTime() const { return deltaTime; }
}
