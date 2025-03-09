#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <Windows.h>

namespace Az
{
	class Window
	{
	public:

		bool AZCreateWindow(const char* Title, uint32_t width, uint32_t height);
		void Close();

		inline SDL_Window* GetWindow() { return m_Window; }
		inline SDL_GLContext Get_GL_Context() { return m_GLContext; }

		inline glm::vec2 getSize() { return glm::vec2(m_Width, m_Height); }

		inline void Clear(glm::vec4 clearColor)
		{
			glClearColor(
				clearColor.r,
				clearColor.g,
				clearColor.b,
				clearColor.a
			);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}
		inline void Clear(float r, float g, float b, float a)
		{
			glClearColor(r, g, b, a); 
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		inline bool shouldClose() { return m_ShouldClose; }
		inline void setShouldClose(bool value) { m_ShouldClose = value; }

		inline void SwapBuffers() { SDL_GL_SwapWindow(m_Window); }

		inline void setSize(uint32_t width, uint32_t height) { m_Width = width; m_Height = height; }

	public:

		SDL_Event event = { 0 };

	private:
		bool InitSDL();
		bool m_ShouldClose = true;
		uint32_t m_Width, m_Height;

		SDL_Window* m_Window;
		SDL_GLContext m_GLContext;
	};

}