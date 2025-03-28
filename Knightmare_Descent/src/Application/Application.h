#pragma once

#include <Azyris.h>
#include <zPlayer.h>
#include <Managers/MapManager.h>
#include <OrcEnemy.h>

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
	Az::B2_Scene m_B2Scene;

	MapManager m_World;

	zPlayer m_Player;

	std::vector<OrcEnemy> m_OrcEnemies;
};