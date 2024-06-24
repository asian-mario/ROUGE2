#pragma once

#include "ROUGE2/Core.h"
#include "ROUGE2/Events/Event.h"

namespace ROUGE2 {
	class ROUGE2_API Layer { //subclass Layer class per layer
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetatch() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }

	private:
		std::string m_DebugName; //only for debug not part of release

	};
}