#include <MyView.h>

class Sandbox : public MyView::Application
{
public: 
	Sandbox()
	{

	}
	~Sandbox()
	{

	}

};

MyView::Application* MyView::CreateApplication()
{
	return new Sandbox();
}
