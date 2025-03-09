#include "EBO.h"

namespace Az
{


	EBO::EBO(u32* indices, i64 size, GLenum usage)
	{
		glGenBuffers(1, &m_ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
	}
	void EBO::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}
	void EBO::Clear()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 0, nullptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void EBO::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	void EBO::Delete()
	{
		glDeleteBuffers(1, &m_ID);
	}
}