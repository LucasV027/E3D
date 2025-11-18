#pragma once

#include <vector>

#include "Event.h"

namespace E3D {
    class Layer {
    public:
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(double dt) {}
        virtual void OnImGui() {}
        virtual void OnEvent(Event& event) {}
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
