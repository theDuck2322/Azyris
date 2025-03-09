#include "VAO.h"

namespace Az
{
	void VAO::Init()
	{
		glGenVertexArrays(1, &m_ID);
	}

	void VAO::LinkVBO(const VBO& vbo, u32 layout, i32 size, GLenum type, GLboolean normalized, i32 stride, void* offset)
	{
		this->Bind();
		vbo.Bind();

		// Configure vertex attribute
		glVertexAttribPointer(layout, size, type, normalized, stride, offset);
		glEnableVertexAttribArray(layout);

		vbo.Unbind();
		this->Unbind();
	}

	void VAO::Bind() const
	{
		glBindVertexArray(m_ID);
	}

	void VAO::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VAO::Delete()
	{
		glDeleteVertexArrays(1, &m_ID);
	}
}
