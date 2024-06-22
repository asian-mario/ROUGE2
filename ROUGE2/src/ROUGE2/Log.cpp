#include "r2pch.h"
#include "Log.h"

namespace ROUGE2 {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$"); //color + timestamp + log name + msg
		s_CoreLogger = spdlog::stdout_color_mt("ROUGE2"); //col - severity - yellow/medrisk
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);

 
	}
}