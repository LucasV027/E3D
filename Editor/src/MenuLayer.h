#pragma once

#include <E3D.h>

#include "BaseLayer.h"

class MenuLayer final : public E3D::Layer {
public:
    MenuLayer();
    ~MenuLayer() override = default;

    void OnUpdate(float ts) override;
    void OnImGuiRender() override;

private:
    const std::unordered_map<std::string, std::function<Layer*()>> layerRegistry = {
        {"Base", [] { return new BaseLayer(); }},
    };

    Layer* currentLayer;
};
