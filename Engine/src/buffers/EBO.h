#pragma once

#include <glad/glad.h>
#include <Types.h>

namespace Az
{
	class EBO
	{
	public:
		EBO() = default;
		EBO(u32* indices, i64 size, GLenum usage = GL_STATIC_DRAW);

		void Bind();
		void Clear();
		void Unbind();
		void Delete();

	private:

		u32 m_ID;
	};
}