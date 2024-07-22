#pragma once

#ifdef R2_PLATFORM_WINDOWS

extern ROUGE2::Application* ROUGE2::CreateApplication();

int main(int argc, char** argv) {
	ROUGE2::Log::Init();

	R2_PROFILE_BEGIN_SESSION("INIT", "R2PROFILE-STARTUP.json");
	auto app = ROUGE2::CreateApplication();
	R2_PROFILE_END_SESSION();

	R2_PROFILE_BEGIN_SESSION("RUN", "R2PROFILE-RUNTIME.json");
	app->Run();
	R2_PROFILE_END_SESSION();

	R2_PROFILE_BEGIN_SESSION("SHUTDOWN", "R2PROFILE-SHUTDOWN.json");
	delete app; //del. f/ heap
	R2_PROFILE_END_SESSION();
}

#endif