#pragma once

#include <Azyris.h>
#include <zPlayer.h>
#include <Managers/MapManager.h>

class Application
{
public:

	void ProcessEvents();

	void Run();

private: // CORE
	Az::Window m_Window;
	Az::Camera2D m_Camera;
	Az::Shader m_Shader;

private: // Game stuff
	Az::Scene m_Scene;

	zPlayer m_Player;
};