#include <MyView.h>
#include <imgui/imgui.h>

class ExampleLayer : public MyView::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		MV_INFO("ExampleLayer::Update");
		
	}

	void OnImGuiRender() override
	{
		ImGui::Text("Hello");
	}

	void OnEvent(MyView::Event& event) override
	{
		MV_TRACE("{0}", event.GetName());
	}
};


class Sandbox : public MyView::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{
	}

};

MyView::Application* MyView::CreateApplication()
{
	return new Sandbox();
}
