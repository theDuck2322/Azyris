#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <AzyrisKeys.h>

namespace Az
{
	class Input
	{
	public:
		// Initialize state tracking for the Input system
		static void Init();

		// Keyboard functions
		static bool GetKey(AZ_Keycode key);           // Check if key is held down
		static bool GetKeyDown(AZ_Keycode key);       // Check if key was just pressed
		static bool GetKeyUp(AZ_Keycode key);         // Check if key was just released

		// Mouse functions
		static glm::vec2 GetMousePos();               // Get current mouse position
		static float GetMouseX();                     // Get mouse X position
		static float GetMouseY();                     // Get mouse Y position
		static bool GetMouseButton(uint8_t button);   // Check if mouse button is held down
		static bool GetMouseButtonDown(uint8_t button); // Check if mouse button was just pressed
		static bool GetMouseButtonUp(uint8_t button); // Check if mouse button was just released

		// Updates input states each frame; call this in your game loop
		static void Update();

	private:
		// State tracking variables (all static)
		static std::unordered_map<SDL_Keycode, bool> m_CurrentKeys;
		static std::unordered_map<SDL_Keycode, bool> m_PreviousKeys;
		static uint32_t m_CurrentMouseButtons;
		static uint32_t m_PreviousMouseButtons;
		static glm::vec2 m_MousePosition;
	};
}
