#include <MyView.h>
#include <imgui/imgui.h>

#include "glm/gtc/matrix_transform.hpp"
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public MyView::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
		, m_Camera(-1280.f/720.f, 1280.f/720.f, -1.f, 1.f)
		, m_CameraPosition(0.0f)
		, m_Position(0.f)
	{
		m_VertexArray.reset(MyView::VertexArray::Create());

		float vertices[] = {
			-0.5f, -0.5f, 0.f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.f, 0.0f, 1.0f,
			 0.5f,  0.5f, 0.f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.f, 1.0f, 0.0f
		};

		m_VertexBuffer.reset(MyView::VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			MyView::BufferLayout layout = {
				{ MyView::ShaderDataType::Float3, "a_Position" },
				{ MyView::ShaderDataType::Float2, "a_TexCoord" }
			};

			m_VertexBuffer->SetLayout(layout);
		}

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[] = { 0, 1, 3, 1, 2, 3};
		m_IndexBuffer.reset(MyView::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			void main()
			{
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}

		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}

		)";
		
		m_Shader.reset(MyView::Shader::Create(vertexSrc, fragmentSrc));
		m_TextureShader.reset(MyView::Shader::Create("assets/shaders/Texture.glsl"));
		m_Texture = MyView::Texture2D::Create("assets/checkerboard.png");
		m_SpotifyLogo = MyView::Texture2D::Create("assets/spotify-512.png");

		std::dynamic_pointer_cast<MyView::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<MyView::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(MyView::Timestep ts) override
	{
		MV_TRACE("Delta time: {0} ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());

		/*----------------- Camera Testing -------------------------------------------------*/
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
			if (len > 0.1f)
			{
				m_Camera.SetPosition({ pos.x + (mousePosX / len) * m_CameraSpeed * ts, pos.y - (mousePosY / len) * m_CameraSpeed * ts, pos.z});
			}
		}
		/*------------------------------------------------------------------*/

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
		glm::mat4 transform1 = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0.25f, 0.0f));

		MyView::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1));
		MyView::RenderCommand::Clear();

		MyView::Renderer::BeginScene(m_Camera);
		{	
			m_Texture->Bind();
			MyView::Renderer::Submit(m_TextureShader, m_VertexArray, transform);
			m_SpotifyLogo->Bind();
			MyView::Renderer::Submit(m_TextureShader, m_VertexArray, transform1);

			MyView::Renderer::EndScene();
		}

		MV_INFO("ExampleLayer::Update");
		
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Triangle Color", &m_TriangleColor[0]);
		ImGui::End();
	}

	void OnEvent(MyView::Event& event) override
	{
		MV_TRACE("{0}", event.GetName());
	}

private:
	MyView::Ref<MyView::Shader> m_Shader, m_TextureShader;
	MyView::Ref<MyView::VertexBuffer> m_VertexBuffer;
	MyView::Ref<MyView::IndexBuffer> m_IndexBuffer;
	MyView::Ref<MyView::VertexArray> m_VertexArray;

	MyView::Ref<MyView::Texture2D> m_Texture, m_SpotifyLogo;

	MyView::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 2.f;
	float m_PrevMousePosX;
	float m_PrevMousePosY;
	glm::vec3 m_Position;
	glm::vec4 m_TriangleColor = { 0.8f, 0.2f, 0.3f, 0.0f };
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
