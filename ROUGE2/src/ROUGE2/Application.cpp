#include "r2pch.h"
#include "Application.h"
#include "ROUGE2/Log.h"

#include <glad/glad.h>
#include "Input.h"


namespace ROUGE2 {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) //temp will be moved
	{
		switch (type)
		{
		case ROUGE2::ShaderDataType::Vec:    return GL_FLOAT;
		case ROUGE2::ShaderDataType::Vec2:   return GL_FLOAT;
		case ROUGE2::ShaderDataType::Vec3:   return GL_FLOAT;
		case ROUGE2::ShaderDataType::Vec4:   return GL_FLOAT;
		case ROUGE2::ShaderDataType::Mat3:     return GL_FLOAT;
		case ROUGE2::ShaderDataType::Mat4:     return GL_FLOAT;
		case ROUGE2::ShaderDataType::VecInt:      return GL_INT;
		case ROUGE2::ShaderDataType::VecInt2:     return GL_INT;
		case ROUGE2::ShaderDataType::VecInt3:     return GL_INT;
		case ROUGE2::ShaderDataType::VecInt4:     return GL_INT;
		case ROUGE2::ShaderDataType::Bool:     return GL_BOOL;
		}

		R2_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Application::Application()
	{
		R2_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);


		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.0f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.0f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.0f, 0.2f, 1.0f
		};
		/*
			small aside : in the future when importing blender models it will be oriented 90 degrees counter-clockwise from its original rotation
			as it operates on X, Z, Y basis.
		*/

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Vec3, "a_Position" },
				{ ShaderDataType::Vec4, "a_Color" }
			};

			m_VertexBuffer->SetLayout(layout);
		}
		
		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.GetComponentCount(), ShaderDataTypeToOpenGLBaseType(element.type), element.normalized ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void*)element.offset);
			index++;
		}

		
		unsigned int indices[3] = { 0, 1, 2 };
		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		std::string vertexSrc = R"(
			#version 330
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			
			out vec3 v_Position;
			out vec4 v_Color;

			void main(){
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
				
			}			


		)"; //dont judge this is temporary testing

		std::string fragmentSrc = R"(
			#version 330
			
			layout(location = 0) out vec4 col;
			in vec3 v_Position;
			in vec4 v_Color;

			void main(){
				col = vec4(v_Position + 0.5, 1.0);
				col = v_Color;
				
			}			


		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{
	}
	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();

	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		R2_CORE_LOG_TRACE("{0}", e);
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			if (e.Handled) {
				break;
			}
		}
		/*
			prevents layers below overlay handling event if there is an event on the overlay layer - button on overlay & action on 3d world layer
		*/
	}
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) {
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		m_Shader->Unbind();
		return true;
	}
}