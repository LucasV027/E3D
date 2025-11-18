#pragma once

#include "Layer.h"

namespace E3D {
    class ImGuiLayer final : public Layer {
    public:
        void OnAttach() override;
        void OnDetach() override;

        void OnEvent(Event&) override;

        static void Begin();
        static void End();
    };
}
