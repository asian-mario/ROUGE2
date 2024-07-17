#pragma once

#include <memory>

#ifdef R2_PLATFORM_WINDOWS
#define ROUGE2_API

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


namespace ROUGE2 {
	template<typename T> 
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}