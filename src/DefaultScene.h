#pragma once

#include "Scene.h"

namespace E3D {
    class DefaultScene final : public Scene {
    public:
        DefaultScene();
        ~DefaultScene() override;

        void OnUpdate(float ts) override;

        void OnImGuiRender() override;

        void OnEvent() override;
    };
}
