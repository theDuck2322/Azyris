#include "core/Input.h"

namespace Az
{
	// Initialize static members
	std::unordered_map<SDL_Keycode, bool> Input::m_CurrentKeys;
	std::unordered_map<SDL_Keycode, bool> Input::m_PreviousKeys;
	uint32_t Input::m_CurrentMouseButtons = 0;
	uint32_t Input::m_PreviousMouseButtons = 0;
	glm::vec2 Input::m_MousePosition = { 0.0f, 0.0f };

	void Input::Init()
	{
		m_CurrentKeys.clear();
		m_PreviousKeys.clear();
		m_CurrentMouseButtons = 0;
		m_PreviousMouseButtons = 0;
		m_MousePosition = { 0.0f, 0.0f };
	}

	void Input::Update()
	{
		// Copy current state to previous state
		m_PreviousKeys = m_CurrentKeys;
		m_PreviousMouseButtons = m_CurrentMouseButtons;

		// Update the current mouse button state
		int mouseX, mouseY;
		m_CurrentMouseButtons = SDL_GetMouseState(&mouseX, &mouseY);

		// Store the mouse position as floats in glm::vec2
		m_MousePosition = glm::vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));

		// Update the current key state
		const Uint8* keystates = SDL_GetKeyboardState(nullptr);
		for (const auto& key : m_CurrentKeys) {
			m_CurrentKeys[key.first] = keystates[SDL_GetScancodeFromKey(key.first)];
		}
	}

	// Keyboard functions
	bool Input::GetKey(AZ_Keycode key)
	{
		return m_CurrentKeys[key];
	}

	bool Input::GetKeyDown(AZ_Keycode key)
	{
		// Key is down this frame, but was not down the previous frame
		return m_CurrentKeys[key] && !m_PreviousKeys[key];
	}

	bool Input::GetKeyUp(AZ_Keycode key)
	{
		// Key was down last frame, but is not down this frame
		return !m_CurrentKeys[key] && m_PreviousKeys[key];
	}

	// Mouse functions
	glm::vec2 Input::GetMousePos()
	{
		return m_MousePosition;
	}

	float Input::GetMouseX()
	{
		return m_MousePosition.x;
	}

	float Input::GetMouseY()
	{
		return m_MousePosition.y;
	}

	bool Input::GetMouseButton(uint8_t button)
	{
		return m_CurrentMouseButtons & SDL_BUTTON(button);
	}

	bool Input::GetMouseButtonDown(uint8_t button)
	{
		// Button is down this frame, but was not down the previous frame
		return (m_CurrentMouseButtons & SDL_BUTTON(button)) && !(m_PreviousMouseButtons & SDL_BUTTON(button));
	}

	bool Input::GetMouseButtonUp(uint8_t button)
	{
		// Button was down last frame, but is not down this frame
		return !(m_CurrentMouseButtons & SDL_BUTTON(button)) && (m_PreviousMouseButtons & SDL_BUTTON(button));
	}
}
