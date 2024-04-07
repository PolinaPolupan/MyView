#pragma once

#include "Core.h"
#include "Window.h"
#include "Events\ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "MyView/Renderer/Shader.h"
#include "MyView/Renderer/Buffer.h"
#include "MyView/Renderer/VertexArray.h"
#include "MyView/Renderer/OrthographicCamera.h"

namespace MyView {
	
	class MYVIEW_API Application
	{
	public:
		Application();
		~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::shared_ptr<VertexArray> m_VertexArray;

		OrthographicCamera m_Camera;

	private:
		static Application* s_Instance;
	};

	// To be defined in client
	Application* CreateApplication();
}


