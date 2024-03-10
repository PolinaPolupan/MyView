#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace MyView {
	class MYVIEW_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
		
	};
}

// Core log macros
#define MV_CORE_TRACE(...)		::MyView::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MV_CORE_INFO(...)		::MyView::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MV_CORE_WARN(...)		::MyView::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MV_CORE_ERROR(...)		::MyView::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MV_CORE_FATAL(...)		::MyView::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define MV_TRACE(...)	::MyView::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MV_INFO(...)	::MyView::Log::GetClientLogger()->info(__VA_ARGS__)
#define MV_WARN(...)	::MyView::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MV_ERROR(...)	::MyView::Log::GetClientLogger()->error(__VA_ARGS__)
#define MV_FATAL(...)	::MyView::Log::GetClientLogger()->fatal(__VA_ARGS__)