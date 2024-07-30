#include "r2pch.h"
#include "Application.h"
#include "ROUGE2/Core/Log.h"
#include "ROUGE2/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace ROUGE2 {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;


	Application::Application()
	{
		OSVI_PROFILE_FUNCTION();

		R2_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}


	Application::~Application()
	{
	}
	void Application::PushLayer(Layer* layer) {
		OSVI_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer) {
		OSVI_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();

	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));


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
		OSVI_PROFILE_FUNCTION();
		while (m_Running)
		{
			OSVI_PROFILE_SCOPE("Application::Run Loop");
			float time = (float)glfwGetTime(); //later added to platform class
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized) {
				{
					OSVI_PROFILE_SCOPE("LayerStack onUpdate");
					for (Layer* layer : m_LayerStack) {
						layer->OnUpdate(timestep);
					}
				}
				m_ImGuiLayer->Begin();
				{
					OSVI_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : m_LayerStack) {
						layer->OnImGuiRender();
					}
				}
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		OSVI_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}