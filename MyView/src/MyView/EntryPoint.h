#pragma once

#ifdef MV_PLATFORM_WINDOWS

extern MyView::Application* MyView::CreateApplication();

int main(int argc, char** argv)
{
	MyView::Log::Init();
	MV_CORE_WARN("Initialized log!");
	MV_WARN("Hi!");

	auto app = MyView::CreateApplication();
	app->Run();
	delete app;
}

#endif