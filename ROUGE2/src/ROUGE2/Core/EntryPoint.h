#pragma once

#ifdef R2_PLATFORM_WINDOWS

extern ROUGE2::Application* ROUGE2::CreateApplication();

int main(int argc, char** argv) {
	ROUGE2::Log::Init();

	OSVI_PROFILE_BEGIN_SESSION("INIT", "R2PROFILE-STARTUP.json");
	auto app = ROUGE2::CreateApplication();
	OSVI_PROFILE_END_SESSION();

	OSVI_PROFILE_BEGIN_SESSION("RUN", "R2PROFILE-RUNTIME.json");
	app->Run();
	OSVI_PROFILE_END_SESSION();

	OSVI_PROFILE_BEGIN_SESSION("SHUTDOWN", "R2PROFILE-SHUTDOWN.json");
	delete app; //del. f/ heap
	OSVI_PROFILE_END_SESSION();
}

#endif