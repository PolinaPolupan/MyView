#pragma once

#include <memory>

#ifdef MV_PLATFORM_WINDOWS
	#if MV_DYNAMIC_LINK
		#ifdef MV_BUILD_DLL
			#define MYVIEW_API __declspec(dllexport)
		#else
			#define MYVIEW_API __declspec(dllimport)
		#endif // MV_BUILD_DLL
	#else 
		#define MYVIEW_API
	#endif
	#else 
		#error Only supports Windows
#endif

#ifdef MV_DEBUG 
	#define MV_ENABLE_ASSERTS
#endif

#ifdef MV_ENABLE_ASSERTS
	#define MV_ASSERT(x, ...) { if(!(x)) { MV_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define MV_CORE_ASSERT(x, ...) { if(!(x)) { MV_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define MV_ASSERT(x, ...)
	#define MV_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define MV_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace MyView {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}