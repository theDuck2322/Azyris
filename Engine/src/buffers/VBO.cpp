#include "VBO.h"

namespace Az
{
	VBO::VBO(const f32* vertices, i64 size, GLenum usage)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
	}

	void VBO::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VBO::Clear() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 0, nullptr); // Clears without reallocating
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBO::Delete()
	{
		glDeleteBuffers(1, &m_ID);
	}
}
