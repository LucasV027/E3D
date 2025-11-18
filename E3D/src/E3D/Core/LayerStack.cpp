#include "LayerStack.h"

namespace E3D {
LayerStack::~LayerStack() {
    for (auto& [_, layer] : layers) {
        layer->OnDetach();
    }
}

void LayerStack::PopLayer(const std::string& tag) {
    if (!TagExists(tag)) {
        std::cerr << "[LayerStack] Warning: Trying to remove non-existent tag: " << tag << std::endl;
        return;
    }
    pendingDeletions.emplace_back(tag);
}

void LayerStack::ProcessPending() {
    for (const auto& tag : pendingDeletions) {
        for (int i = static_cast<int>(layers.size()) - 1; i >= 0; i--) {
            auto& [layerTag, layer] = layers[i];
            if (layerTag == tag) {
                if (layer) layer->OnDetach();
                layers.erase(layers.begin() + i);
            }
        }
    }

    for (const auto& tag : pendingAdditions) {
        for (int i = static_cast<int>(layers.size()) - 1; i >= 0; i--) {
            auto& [layerTag, layer] = layers[i];
            if (layerTag == tag) {
                layer->OnAttach();
                break;
            }
        }
    }

    pendingDeletions.clear();
    pendingAdditions.clear();
}

bool LayerStack::TagExists(const std::string& tag) const {
    for (const auto& [layerTag, layer] : layers)
        if (layerTag == tag)
            return true;

    for (const auto& pending : pendingAdditions)
        if (pending == tag)
            return true;

    return false;
}
}