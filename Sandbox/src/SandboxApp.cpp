#include <ROUGE2.h>
	
class Sandbox : public ROUGE2::Application {
public:
	Sandbox() {

	}

	~Sandbox() {
		
	}
};

ROUGE2::Application* ROUGE2::CreateApplication() {
	return new Sandbox(); //ret. application to entrypoint.h
}