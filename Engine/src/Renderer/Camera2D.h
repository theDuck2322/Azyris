#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Types.h>

namespace Az
{
	class Camera2D
	{
	public:
		Camera2D() = default;
		Camera2D(float left, float right, float bottom, float top);

		void setSize(float width, float height);

		glm::vec2 GetCameraSize() { return m_Size; }

		glm::vec3& GetPosition() { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		f64 GetRotation() const { return m_Rotation; }
		void SetRotation(f64 rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();
	private:

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;

		glm::vec2 m_Size;

		f64 m_Rotation;

	};
}