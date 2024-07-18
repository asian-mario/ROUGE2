#pragma once

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#define R2_PLATFORM_WINDOWS
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif
#elif defined(__APPLE__) || defined(__MACH__)
#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"
#elif TARGET_OS_IPHONE == 1
#define R2_PLATFORM_IOS
#error "IOS is not supported!"
#elif TARGET_OS_MAC == 1
#define R2_PLATFORM_MACOS
#error "MacOS is not supported!"
#else
#error "Unknown Apple platform!"
#endif
 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined */
#elif defined(__ANDROID__)
#define R2_PLATFORM_ANDROID
#error "Android is not supported!"
#elif defined(__linux__)
#define R2_PLATFORM_LINUX
#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection


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