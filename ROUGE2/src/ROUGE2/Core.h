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

#define BIT(x) (1 << x)