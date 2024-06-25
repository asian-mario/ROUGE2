#pragma once
#include "ROUGE2/Layer.h"

namespace ROUGE2 {
	class ROUGE2_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetatch();
		void OnUpdate();
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;
	};
}