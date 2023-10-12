#pragma once
#include <vector>

#include "Layer.hpp"
#include "Engine/Core/Debug/Logger.hpp"

namespace Core {
    class LayerStack {
    public:

        LayerStack() = default;
        ~LayerStack();

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        void PopLayer(Layer* layer);
        void PopOverlay(Layer* layer);

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }

        std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
        std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

        std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
        std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }

        std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
        std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

        size_t size() const { return m_Layers.size(); }

        Layer* operator[](size_t index) {
            ASSERT(index < m_Layers.size(), "Wrong layer index!")

            return m_Layers[index];
        }

        const Layer* operator[](size_t index) const {
            ASSERT(index < m_Layers.size(), "Wrong layer index!")

            return m_Layers[index];
        }

    private:
        std::vector<Layer*> m_Layers;

        uint32_t m_CurrentIndex = 0;
    };
}
