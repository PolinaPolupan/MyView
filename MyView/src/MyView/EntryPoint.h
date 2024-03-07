#pragma once

#ifdef MV_PLATFORM_WINDOWS

extern MyView::Application* MyView::CreateApplication();

int main(int argc, char** argv)
{
	auto app = MyView::CreateApplication();
	app->Run();
	delete app;
}

#endif