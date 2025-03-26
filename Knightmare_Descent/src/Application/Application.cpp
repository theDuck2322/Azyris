#include "Application/Application.h"

void Application::ProcessEvents()
{
	while (SDL_PollEvent(&m_Window.event))
	{
		ImGui_ImplSDL2_ProcessEvent(&m_Window.event);


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
				//m_Camera.SetSize(w, h);
				glViewport(0, 0, w, h);
			}
			else if (m_Window.event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
			{
				int w = m_Window.event.window.data1;
				int h = m_Window.event.window.data2;
				m_Window.SetSize(w, h);
				//m_Camera.SetSize(w, h);
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
					//m_Camera.SetSize(1280, 720);
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
	m_Camera = Az::Camera2D(0, 1920, 0, 1080);
	m_Shader.load("Engine/Assets/shaders/batchShader.vert", "Engine/Assets/shaders/batchShader.frag");
	Az::Texture texture;
	texture.loadFromFile("Knightmare_Descent/Assets/Entities/Soldier.png");
	

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

	OrcEnemy enemy;
	enemy.Start(glm::vec3(100, 100, -0.5));
	enemy.SetTexture("Knightmare_Descent/Assets/Entities/Orc.png");

	Az::ImGuiLayer::InitImGUI(&m_Window);
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImFontConfig font_cfg;
	font_cfg.SizePixels = 64.0f; // Set the desired font size

	// Load the default font at the specified size
	ImFont* biggerFont = io.Fonts->AddFontDefault(&font_cfg);
	IM_ASSERT(biggerFont && "Failed to load the default font!");

	// Build the font atlas again
	io.Fonts->Build();

	m_Player.m_Inventory = Inventory(24, "Test Inventory");
	Item sword("Sword", 1);
	Item shield("Shield", 2);

	m_Player.m_Inventory.AddItem(&sword);
	m_Player.m_Inventory.AddItem(&shield);

	while (!m_Window.ShouldClose())
	{
		// START FRAME THINGS, engine update things:
		Az::Timer::UpdateTime();
		Az::Input::Update();
		m_Window.Clear(0, 0, 0, 1);
		m_B2Scene.UpdateScene(Az::Timer::deltaTime);

		// PROCESS EVENTS FOR WINDOW:
		ProcessEvents();

		// GAME OBJECTS UPDATE HERE:

		m_Player.Update();
		m_Camera.SetPosition(m_Player.GetDST().Position - (m_Camera.GetSize() / 2.0f));
		enemy.Update();

		// GAME DRAWING HERE
		Az::Renderer::BeginBatch(); // start batch

		m_Player.Render();
		enemy.Render();
		m_World.RenderMap();

		Az::Renderer::EndBatch(); // end batch

		// UI DRAWING HERE
		Az::ImGuiLayer::ImplementFrame();

		m_Player.RenderUI();

		Az::Renderer::RenderText(std::to_string(int(1.0 / Az::Timer::deltaTime)),
			glm::vec3(0), 
			biggerFont, 
			glm::vec4(1, 1, 1, 1));

		Az::ImGuiLayer::Render();

		
		m_Window.SwapBuffers();

	}

	Az::ImGuiLayer::Shutdown();

	Az::Renderer::Shutdown();

	m_Window.Close();

}
