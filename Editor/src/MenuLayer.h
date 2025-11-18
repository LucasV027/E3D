#pragma once

#include <E3D.h>

#include "BaseLayer.h"
#include "MeshLayer.h"

class MenuLayer final : public E3D::Layer {
public:
    MenuLayer();
    ~MenuLayer() override = default;

    void OnUpdate(double ts) override;
    void OnImGui() override;

private:
    const std::unordered_map<std::string, std::function<void(std::string&)>> layerRegistry = {
        {
            "Layer", [](std::string& name) {
                E3D::Application::Get().PushLayer<BaseLayer>("BaseLayer");
                name = "BaseLayer";
            }
        },
        {
            "MeshLayer", [](std::string& name) {
                E3D::Application::Get().PushLayer<MeshLayer>("MeshLayer");
                name = "MeshLayer";
            }
        },
    };

    std::string currentLayerTag;
};
