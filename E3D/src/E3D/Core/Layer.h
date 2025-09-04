#pragma once

#include <vector>

#include "E3D/Event/EventSystem.h"

namespace E3D {
    class Layer {
    public:
        Layer() = default;
        virtual ~Layer() = default;

        virtual void OnUpdate(float ts) {}
        virtual void OnImGuiRender() {}

    protected:
        ScopedEventListener events;
    };

    class LayerStack {
    public:
        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PopLayer(Layer* layer);

        std::vector<Layer*>::iterator begin() { return layers.begin(); }
        std::vector<Layer*>::iterator end() { return layers.end(); }
        std::vector<Layer*>::const_iterator begin() const { return layers.begin(); }
        std::vector<Layer*>::const_iterator end() const { return layers.end(); }

    private:
        std::vector<Layer*> layers;
    };
}
