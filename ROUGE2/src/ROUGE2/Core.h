#pragma once

#ifdef R2_PLATFORM_WINDOWS
	#ifdef R2_BUILD_DLL
		#define ROUGE2_API __declspec(dllexport)

	#else
		#define ROUGE2_API __declspec(dllimport)
	#endif

#else
	#error ROUGE2 ONLY SUPPORTS x64 WINDOWS!
#endif

#ifdef R2_ENABLE_ASSERTS
	#define R2_ASSERT(x, ...) { if(!(x)) { R2_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define R2_CORE_ASSERT(x, ...) { if(!(x)) { R2_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define R2_ASSERT(x, ...)
	#define R2_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define R2_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)