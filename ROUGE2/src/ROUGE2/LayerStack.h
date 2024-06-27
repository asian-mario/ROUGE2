#pragma once

#include "ROUGE2/Core.h"
#include "Layer.h"

#include <vector>

namespace ROUGE2 {
	class ROUGE2_API LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);


		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }


	private:
		std::vector<Layer*> m_Layers; //stack
		unsigned int m_LayerInsertIndex = 0;
	};
}
