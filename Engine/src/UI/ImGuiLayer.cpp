#include <UI/ImGuiLayer.h>
#include <utils/Helpers.h>

namespace Az
{

	Az::Window* ImGuiLayer::m_WindowPtr = nullptr;
	bool ImGuiLayer::m_IsInitialized = false;
	bool ImGuiLayer::m_FrameImplemented = false;

	void ImGuiLayer::InitImGUI(Az::Window* window)
	{
		m_WindowPtr = window;
		AZ_Assert(m_WindowPtr != nullptr, "WindowPtr is nullptr!!");

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplSDL2_InitForOpenGL(m_WindowPtr->GetWindow(), m_WindowPtr->Get_GL_Context());
		ImGui_ImplOpenGL3_Init("#version 460");

		// Ensure a font is added and built
		io.Fonts->AddFontDefault();
		io.Fonts->Build();

		m_IsInitialized = true;
	}
	void ImGuiLayer::ImplementFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		m_FrameImplemented = true;
	}

	void ImGuiLayer::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		m_FrameImplemented = false;
	}

	void ImGuiLayer::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	bool ImGuiLayer::MouseIsOverUI()
	{

		return (ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow) || ImGui::IsAnyItemHovered());
	}
}

