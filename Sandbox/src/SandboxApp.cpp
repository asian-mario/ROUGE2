#include <ROUGE2.h>

class ExLayer : public ROUGE2::Layer {
public:
	ExLayer() : Layer("Example") 
	{
	}

	void OnUpdate() override{

		if (ROUGE2::Input::IsKeyPressed(R2_KEY_SPACE)) {
			R2_INFO("SPACE KEY PRESSED");
		}
	}

	void OnEvent(ROUGE2::Event& event) override {
		//R2_TRACE("{0}", event);
		/*
			technically you can convert char -> ascii to use as events b/ limits function keys
		*/
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