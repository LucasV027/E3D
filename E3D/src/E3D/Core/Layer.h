#pragma once

#include "Event.h"

namespace E3D {
    class Layer {
    public:
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(double dt) {}
        virtual void OnRender() {}
        virtual void OnImGui() {}
        virtual void OnEvent(Event&) {}
    };
}
