#pragma once

#include "E3D/Event/EventSystem.h"

namespace E3D {
    class Scene {
    public:
        Scene() = default;
        virtual ~Scene() = default;

        virtual void OnUpdate(float ts) {}
        virtual void OnImGuiRender() {}

    protected:
        ScopedEventListener events;
    };
}
