#include "core/Window.h"


namespace Az
{

	bool Window::InitSDL()
	{
		SetProcessDPIAware();
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
			return EXIT_FAILURE;
		}

		if (TTF_Init() == -1) {
			std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
			return EXIT_FAILURE;
		}

		if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) & (IMG_INIT_PNG | IMG_INIT_JPG))) {
			std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
			return EXIT_FAILURE;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
			std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
			return EXIT_FAILURE;
		}


		return EXIT_SUCCESS;
	}

	bool Window::AZCreateWindow(const char* Title, uint32_t width, uint32_t height)
	{
		if (InitSDL())
		{
			return EXIT_FAILURE;
		}

		// Set OpenGL attributes
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		m_Window = SDL_CreateWindow(
			Title,
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			width,
			height,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
		);
		if (!m_Window) {
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			SDL_Quit();
			return EXIT_FAILURE;
		}

		// Create an OpenGL context
		m_GLContext = SDL_GL_CreateContext(m_Window);
		if (!m_GLContext) {
			std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
			SDL_DestroyWindow(m_Window);
			SDL_Quit();
			return EXIT_FAILURE;
		}

		// Load OpenGL functions using GLAD
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
			std::cerr << "Failed to initialize GLAD!" << std::endl;
			SDL_GL_DeleteContext(m_GLContext);
			SDL_DestroyWindow(m_Window);
			SDL_Quit();
			return EXIT_FAILURE;
		}

		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		// Enable VSync
		SDL_GL_SetSwapInterval(1);

		glViewport(0, 0, width, height);


		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		m_Width = width;
		m_Height = height;

		m_ShouldClose = false;


		return EXIT_SUCCESS;
	}
	void Window::Close()
	{
		// Clean up resources
		SDL_GL_DeleteContext(m_GLContext);
		SDL_DestroyWindow(m_Window);

		Mix_CloseAudio();
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
	}
}