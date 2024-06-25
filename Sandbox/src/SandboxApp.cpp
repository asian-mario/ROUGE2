#include <ROUGE2.h>


class ExLayer : public ROUGE2::Layer {
public:
	ExLayer() : Layer("Example") 
	{
	}

	void OnUpdate() override{
		R2_INFO("ExLayer::Update");
	}

	void OnEvent(ROUGE2::Event& event) override {
		R2_TRACE("{0}", event);
	}
};

class Sandbox : public ROUGE2::Application {
public:
	Sandbox() {
		PushLayer(new ExLayer());
		PushOverlay(new ROUGE2::ImGuiLayer());
	}

	~Sandbox() {
		
	}
};

ROUGE2::Application* ROUGE2::CreateApplication() {
	return new Sandbox(); //ret. application to entrypoint.h
}