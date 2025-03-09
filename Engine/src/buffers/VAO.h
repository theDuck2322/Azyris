#pragma once

#include <glad/glad.h>
#include <buffers/VBO.h>
#include <Types.h>

namespace Az
{
	class VAO
	{
	public:
		VAO() = default;
		void Init();
		// Links a VBO to the VAO with configurable layout
		void LinkVBO(const VBO& vbo, u32 layout, i32 size, GLenum type, GLboolean normalized, i32 stride, void* offset);

		void Bind() const;
		void Unbind() const;
		void Delete();

	private:
		u32 m_ID; // VAO ID
	};
}
