#include "pch.hpp"
#include "LayerStack.hpp"

namespace Core {
    LayerStack::~LayerStack() {
        for (Layer* layer : m_Layers) {
            layer->OnDetach();
            delete layer;
        }

        m_Layers.clear();
    }

    void LayerStack::PushLayer(Layer* layer) {
        m_Layers.emplace(m_Layers.begin() + m_CurrentIndex, layer);
        m_CurrentIndex++;
    }

    void LayerStack::PushOverlay(Layer* layer) {
        m_Layers.emplace_back(layer);
    }

    void LayerStack::PopLayer(Layer* layer) {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_CurrentIndex, layer);

        if (it != m_Layers.begin() + m_CurrentIndex) {
            layer->OnDetach();
            m_Layers.erase(it);
            m_CurrentIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* layer) {
        auto it = std::find(m_Layers.begin() + m_CurrentIndex, m_Layers.end(), layer);

        if (it != m_Layers.end()) {
            layer->OnDetach();
            m_Layers.erase(it);
        }
    }
}
