#pragma once

#include <memory>
#include <vector>
#include <iostream>

#include "Layer.h"

namespace E3D {
    class LayerStack {
        struct LayerWithTag {
            std::string tag;
            std::unique_ptr<Layer> layer;
        };

    public:
        LayerStack() = default;
        ~LayerStack();

        template <typename T>
        void PushLayer(const std::string& tag) {
            if (TagExists(tag)) {
                std::cerr << "[LayerStack] Error: Tag already exists: " << tag << std::endl;
                return;
            }

            layers.emplace_back(tag, std::make_unique<T>());
            pendingAdditions.emplace_back(tag);
        }

        void PopLayer(const std::string& tag);

        const std::vector<LayerWithTag>& Layers() const { return layers; }
        void ProcessPending();
        bool TagExists(const std::string& tag) const;

    private:
        std::vector<LayerWithTag> layers;

        std::vector<std::string> pendingAdditions;
        std::vector<std::string> pendingDeletions;
    };
}
