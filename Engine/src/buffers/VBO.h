#pragma once

#include <glad/glad.h>
#include <utils/Types.h>

namespace Az
{
	class VBO
	{
	public:
		VBO() = default;
		VBO(const f32* vertices, i64 size, GLenum usage = GL_STATIC_DRAW);

		void Bind() const;
		void Clear() const;
		void Unbind() const;
		void Delete();

	private:
		u32 m_ID; // VBO ID
	};
}
