#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_sdl2.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <core/Window.h>

namespace Az
{
	class ImGuiLayer
	{
	public:

		static void InitImGUI(Az::Window* window);
		static void ImplementFrame();

		static void Render();

		static void Shutdown();

		inline static bool IsReady() { return m_IsInitialized; }

		static bool MouseIsOverUI();

		inline static bool ReadyToDraw() { return (m_IsInitialized && m_FrameImplemented); }

	private:

		static Az::Window* m_WindowPtr;
		static bool m_IsInitialized;

		static bool m_FrameImplemented;
	};
}