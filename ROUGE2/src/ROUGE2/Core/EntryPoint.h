#pragma once

#ifdef R2_PLATFORM_WINDOWS

extern ROUGE2::Application* ROUGE2::CreateApplication();

int main(int argc, char** argv) {
	ROUGE2::Log::Init();
	R2_CORE_LOG_WARN("Initialized Logging");
	int a = 2422;
	R2_INFO("Logging Started Var={0}", a);




	auto app = ROUGE2::CreateApplication();
	app->Run();
	delete app; //del. f/ heap
}

#endif