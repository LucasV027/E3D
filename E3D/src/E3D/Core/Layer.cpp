#include "Layer.h"

namespace E3D {
    LayerStack::~LayerStack() {
        for (const auto& layer : layers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer) {
        if (layer)
            layers.emplace_back(layer);
    }

    void LayerStack::PopLayer(Layer* layer) {
        auto it = std::ranges::find(layers, layer);
        if (it != layers.end()) {
            layers.erase(it);
        }
    }
}
