#include "Application/Application.h"

void Application::ProcessEvents()
{
	while (SDL_PollEvent(&m_Window.event))
	{
		if (m_Window.event.type == SDL_QUIT)
		{
			m_Window.setShouldClose(true);
		}
		if (Az::Input::GetKey(AZ_ESCAPE))
		{
			m_Window.setShouldClose(true);
		}

		// Handle window resize
		if (m_Window.event.type == SDL_WINDOWEVENT)
		{
			if (m_Window.event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				int w = m_Window.event.window.data1;
				int h = m_Window.event.window.data2;
				m_Window.setSize(w, h);
				m_Camera.setSize(w, h);
				glViewport(0, 0, w, h);
			}
			else if (m_Window.event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				int w = m_Window.event.window.data1;
				int h = m_Window.event.window.data2;
				m_Window.setSize(w, h);
				m_Camera.setSize(w, h);
				glViewport(0, 0, w, h);
			}
		}
		if (m_Window.event.type == SDL_KEYDOWN)
		{
			if (m_Window.event.key.keysym.sym == SDLK_F11)
			{
				int w, h;
				glm::vec2 size = m_Window.getSize();

				w = size.x;
				h = size.y;

				// Check if the window is currently in fullscreen mode
				Uint32 isFullscreen = SDL_GetWindowFlags(m_Window.GetWindow()) & SDL_WINDOW_FULLSCREEN_DESKTOP;
				if (isFullscreen) {
					// Switch to windowed mode
					SDL_SetWindowFullscreen(m_Window.GetWindow(), 0);
					SDL_SetWindowSize(m_Window.GetWindow(), 1280, 720); // Restore the original window size
					SDL_SetWindowPosition(m_Window.GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED); // Center the window

					m_Window.setSize(1280, 720);
					m_Camera.setSize(1280, 720);
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
	
	Az::Input::Init();

	Az::Renderer::BindCamera(&m_Camera);
	Az::Renderer::BindShader(&m_Shader);
	Az::Renderer::Init();

	m_Scene.CreateSpace(glm::vec2(0.0f, 0.0f));
	Az::BoxCollider2D::SetScene(m_Scene.GetSpace());
	Az::Shapes::Rect dst;
	dst.Position = glm::vec3(0, 0, 0);
	dst.Size = glm::vec3(250, 250 * 29.0f / 48.0f, 1);
	MapManager m_World;

	m_World.LoadMap();
	Az::Shapes::Rect p;
	
	p.Position = glm::vec3(0, 0, -9);
	p.Size = glm::vec3(1024 * 7);

	Az::Shapes::Rect col; // 3, 15 12
	col.Position = glm::vec3(16, 16, 0);
	//col.Position = glm::vec3(0);
	col.Size = glm::vec3(16 * 7 * 13, 16* 7, 1);
	
	glm::vec4 color = glm::vec4(1.0f);

	Az::BoxCollider2D wallCol;
	wallCol.CreateCollider(col);

	m_Player.Start(dst);
	m_Player.SetTexture(texture);



	while (!m_Window.shouldClose())
	{
		Az::Timer::UpdateTime();
		Az::Input::Update();
		m_Window.Clear(0, 0, 0, 1);

		//std::cout << 1 / Az::Timer::deltaTime << std::endl;

		m_Scene.UpdateScene(Az::Timer::deltaTime);
		//cpSpaceSetDamping(m_Scene.GetSpace(), 1.f); // Applies damping to all bodies


		ProcessEvents();

		m_Player.Update();
		glm::vec3 pos = m_Player.GetDST().Position - 
			glm::vec3(m_Window.getSize() / 2.0f, 0) + 
			glm::vec3(m_Player.GetDST().Size.x, m_Player.GetDST().Size.y, 0) / 2.0f;
		m_Camera.SetPosition(pos);


		Az::Renderer::ResetStats();
		Az::Renderer::BeginBatch();
		
		Az::Renderer::DrawQuad(col, color);

		Az::Renderer::DrawQuad(m_Player.GetDST(), m_Player.GetSRC(), m_Player.GetTexture(), m_Player.playerFlipped());
		Az::Renderer::DrawQuad(m_Player.GetDST(), glm::vec4(1, 0, 0, 1));
		//Az::BatchRenderer::DrawQuad(glm::vec3(m_Player.GetDST().Position.x, m_Player.GetDST().Position.y, 10), glm::vec3(m_Player.GetDST().Size.y), glm::vec4(0, 1, 0, 1));

		m_World.RenderMap();

		Az::Renderer::EndBatch();
		Az::Renderer::Flush();

		m_Window.SwapBuffers();
	}

	Az::Renderer::Shutdown();

	m_Window.Close();

}
