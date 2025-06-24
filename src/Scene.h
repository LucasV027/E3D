#pragma once

namespace E3D {
    class Scene {
    public:
        Scene() = default;
        virtual ~Scene() = default;

        virtual void OnUpdate(float ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(/* TODO: Event object? */) {}
    };
}
