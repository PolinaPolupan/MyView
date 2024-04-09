#include <MyView.h>
#include <imgui/imgui.h>

class ExampleLayer : public MyView::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
		, m_Camera(-1280.f/720.f, 1280.f/720.f, -1.f, 1.f)
		, m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(MyView::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.f,  1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.f,  0.0f, 1.0f, 0.0f, 1.0f,
			 0.f,   0.5f, 0.f,  0.0f, 0.0f, 1.0f, 1.0f,
		};

		m_VertexBuffer.reset(MyView::VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			MyView::BufferLayout layout = {
				{ MyView::ShaderDataType::Float3, "a_Position" },
				{ MyView::ShaderDataType::Float4, "a_Color" }
			};

			m_VertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(MyView::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Color = a_Color;
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}

		)";

		m_Shader.reset(new MyView::Shader(vertexSrc, fragmentSrc));
	}

	void OnUpdate(MyView::Timestep ts) override
	{
		MV_TRACE("Delta time: {0} ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		bool shift = MyView::Input::IsKeyPressed(MV_KEY_RIGHT_SHIFT) || MyView::Input::IsKeyPressed(MV_KEY_LEFT_SHIFT);
		bool middleMouseButton = MyView::Input::IsMouseButtonPressed(MV_MOUSE_BUTTON_MIDDLE);

		if (shift && middleMouseButton)
		{
			auto pos = m_Camera.GetPosition();
			auto mousePos = MyView::Input::GetMousePos();

			auto mousePosX = m_PrevMousePosX - mousePos.first;
			auto mousePosY = m_PrevMousePosY - mousePos.second;
			m_PrevMousePosX = mousePos.first;
			m_PrevMousePosY = mousePos.second;
			float len = std::sqrt((mousePosX * mousePosX + mousePosY * mousePosY));
			if (len > 0.f)
			{
				m_Camera.SetPosition({ pos.x + (mousePosX / len) * m_CameraSpeed * ts, pos.y + (mousePosY / len) * m_CameraSpeed * ts, pos.z});
			}
		}
		MyView::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		MyView::RenderCommand::Clear();

		MyView::Renderer::BeginScene(m_Camera);
		{
			MyView::Renderer::Submit(m_Shader, m_VertexArray);

			MyView::Renderer::EndScene();
		}

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

private:
	std::shared_ptr<MyView::Shader> m_Shader;
	std::shared_ptr<MyView::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<MyView::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<MyView::VertexArray> m_VertexArray;

	MyView::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 3.f;
	float m_PrevMousePosX;
	float m_PrevMousePosY;
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
