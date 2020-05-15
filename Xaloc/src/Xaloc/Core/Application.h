#pragma once

#include "Core.h"

#include "Window.h"

#include "Xaloc/Renderer/Renderer.h"

#include "Xaloc/Core/LayerStack.h"
#include "Xaloc/Events/Event.h"
#include "Xaloc/Events/ApplicationEvent.h"

#include "Xaloc/Core/Timestep.h"

#include "Xaloc/ImGui/ImGuiLayer.h"


namespace Xaloc {


	struct ApplicationSpec
	{
		std::string Name;

		RendererAPI::API TargetGraphics;

		unsigned int Width = 1280;
		unsigned int Height = 720;
	};
	

	class Application
	{
	public:
		Application(ApplicationSpec spec);
		virtual ~Application() = default;

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }

		
		inline static std::string GetName() { return s_Instance->m_Name; }

		inline static float GetFPS() { return s_Instance->m_FPS; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;

		std::string m_Name;
		
		bool m_Running = true;
		bool m_Paused = false; // Whether the game is running in a freezed state
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		float m_FPS = 0.0f;

	private:
		static Application* s_Instance;
	};

	// To be defined in the client application
	Application* CreateApplication();

}
