#pragma once

#include "Core.h"

namespace MyView {
	
	class MYVIEW_API Application
	{
	public:
		Application();
		~Application();

		void Run();
	};

	// To be defined in client
	Application* CreateApplication();
}


