#pragma once

#include "ROUGE2/Core/Core.h"
#include "ROUGE2/Events/Event.h"

#include "ROUGE2/Core/Timestep.h"

namespace ROUGE2 {
	class ROUGE2_API Layer { //subclass Layer class per layer
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName; //only for debug not part of release

	};
}