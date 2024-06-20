#pragma once

#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

#include "Core.h"

namespace ROUGE2 {
	class ROUGE2_API Log
	{
	public:
		static void Init();

		//inline d/ to frequent exec.
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; } 
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

//log macros - core
#define R2_CORE_LOG_FATAL(...)	::ROUGE2::Log::GetCoreLogger()->fatal(__VA_ARGS__)
#define R2_CORE_LOG_ERROR(...)	::ROUGE2::Log::GetCoreLogger()->error(__VA_ARGS__)
#define R2_CORE_LOG_WARN(...)	::ROUGE2::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define R2_CORE_LOG_INFO(...)	::ROUGE2::Log::GetCoreLogger()->info(__VA_ARGS__)
#define R2_CORE_LOG_TRACE(...)	::ROUGE2::Log::GetCoreLogger()->trace(__VA_ARGS__)
										
//log macros - app						
#define R2_FATAL(...)			::ROUGE2::Log::GetClientLogger()->fatal(__VA_ARGS__)
#define R2_ERROR(...)			::ROUGE2::Log::GetClientLogger()->error(__VA_ARGS__)
#define R2_WARN(...)			::ROUGE2::Log::GetClientLogger()->warn(__VA_ARGS__)
#define R2_INFO(...)			::ROUGE2::Log::GetClientLogger()->info(__VA_ARGS__)
#define R2_TRACE(...)			::ROUGE2::Log::GetClientLogger()->trace(__VA_ARGS__)

// if distribution
/*
	put non useful logs for dist. / save unnec. log
*/