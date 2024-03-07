#pragma once

#ifdef MV_PLATFORM_WINDOWS
	#ifdef MV_BUILD_DLL
		#define MYVIEW_API __declspec(dllexport)
	#else
		#define MYVIEW_API __declspec(dllimport)
	#endif // MV_BUILD_DLL
#else 
	#error Only support Windows
#endif
