#include "Application/Application.h"

void Application::ProcessEvents()
{
	while (SDL_PollEvent(&m_Window.event))
	{
		if (m_Window.event.type == SDL_QUIT)
		{
			m_Window.SetShouldClose(true);
		}
		if (Az::Input::GetKey(AZ_ESCAPE))
		{
			m_Window.SetShouldClose(true);
		}

		// Handle window resize
		if (m_Window.event.type == SDL_WINDOWEVENT)
		{
			if (m_Window.event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				int w = m_Window.event.window.data1;
				int h = m_Window.event.window.data2;
				m_Window.SetSize(w, h);
				m_Camera.SetSize(w, h);
				glViewport(0, 0, w, h);
			}
			else if (m_Window.event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				int w = m_Window.event.window.data1;
				int h = m_Window.event.window.data2;
				m_Window.SetSize(w, h);
				m_Camera.SetSize(w, h);
				glViewport(0, 0, w, h);
			}
		}
		if (m_Window.event.type == SDL_KEYDOWN)
		{
			if (m_Window.event.key.keysym.sym == SDLK_F11)
			{
				int w, h;
				glm::vec2 size = m_Window.GetSize();

				w = size.x;
				h = size.y;

				// Check if the window is currently in fullscreen mode
				Uint32 isFullscreen = SDL_GetWindowFlags(m_Window.GetWindow()) & SDL_WINDOW_FULLSCREEN_DESKTOP;
				if (isFullscreen) {
					// Switch to windowed mode
					SDL_SetWindowFullscreen(m_Window.GetWindow(), 0);
					SDL_SetWindowSize(m_Window.GetWindow(), 1280, 720); // Restore the original window size
					SDL_SetWindowPosition(m_Window.GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED); // Center the window

					m_Window.SetSize(1280, 720);
					m_Camera.SetSize(1280, 720);
					glViewport(0, 0, 1280, 720);
				}
				else {
					// Switch to fullscreen borderless mode
					SDL_SetWindowFullscreen(m_Window.GetWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
			}
		}

	}
}


void Application::Run()
{
	Az::SetWorkingDir();
	system("dir");
	m_Window.AZCreateWindow("Knightmare Descent", 1280, 720);
	m_Camera = Az::Camera2D(0, 1280, 0, 720);
	m_Shader.load("Engine/Assets/shaders/batchShader.vert", "Engine/Assets/shaders/batchShader.frag");
	Az::Texture texture;
	texture.loadFromFile("Knightmare_Descent/Assets/Entities/Soldier.png");
	
	m_CPScene.CreateSpace(glm::vec2(0.0f, 0.0f));
	Az::CP_BoxCollider2D::SetScene(m_CPScene.GetSpace());

	m_B2Scene.CreateScene(glm::vec3(0, 0, 0));
	Az::B2_BoxCollider::SetScene(m_B2Scene.GetScene());

	Az::Input::Init();

	Az::Renderer::BindCamera(&m_Camera);
	Az::Renderer::BindShader(&m_Shader);
	Az::Renderer::Init();


	m_B2Scene.SetIterations();

	m_World.LoadMap();
	m_World.CreateColliders();

	m_Player.Start();
	m_Player.SetTexture(texture);


	while (!m_Window.ShouldClose())
	{
		Az::Timer::UpdateTime();
		Az::Input::Update();
		m_Window.Clear(0, 0, 0, 1);
	


		m_CPScene.UpdateScene(Az::Timer::deltaTime);
		m_B2Scene.UpdateScene(Az::Timer::deltaTime);


		ProcessEvents();

		m_Player.Update();
		glm::vec3 pos = m_Player.GetDST().Position - (m_Camera.GetSize() / 2.0f);
		m_Camera.SetPosition(pos);


		Az::Renderer::ResetStats();
		Az::Renderer::BeginBatch();



		/*
		for (auto& i : m_World.GetColliders())
		{
			Az::Renderer::DrawQuad(i.GetHitbox(), glm::vec4(0.62, 0.153, 0.333, 1));
		}
		*/



		Az::Renderer::DrawQuad(m_Player.GetDST(), m_Player.GetSRC(), m_Player.GetTexture(), m_Player.playerFlipped());
		//Az::Renderer::DrawRect(m_Player.GetDST(), glm::vec4(1, 0, 0, 1));
		m_World.RenderMap();

		Az::Renderer::EndBatch();
		Az::Renderer::Flush();

		m_Window.SwapBuffers();
	}

	Az::Renderer::Shutdown();

	m_Window.Close();

}
