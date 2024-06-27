#pragma once
#include "ROUGE2/Layer.h"
#include "ROUGE2/Events/KeyEvent.h"
#include "ROUGE2/Events/ApplicationEvent.h"
#include "ROUGE2/Events/MouseEvent.h"

namespace ROUGE2 {
	class ROUGE2_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}