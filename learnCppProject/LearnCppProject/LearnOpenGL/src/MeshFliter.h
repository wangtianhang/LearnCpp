#pragma once

#include "gl3w.h"

struct MeshFliter
{
public:
	GLuint m_vao = 0;
	
	GLuint m_positionVBO = 0;
	GLuint m_colorVBO = 0;
	GLuint m_uvVBO = 0;
	GLuint m_normalVBO = 0;
	GLuint m_tangentVBO = 0;
	GLuint m_indexVBO = 0;

	int drawVerticesCount = 0;
	bool m_isIndex = true;
	GLenum m_frontFace = GL_CCW;

	int m_ShareCount = 1; // 非共享的情况下 不用了要delete vao和vbo

	void UnInit()
	{
		if (m_ShareCount -= 1)
		{
			if (m_ShareCount > 0)
			{
				return;
			}
		}

		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_positionVBO);
		if (m_colorVBO != 0)
		{
			glDeleteBuffers(1, &m_colorVBO);
		}
		if (m_uvVBO != 0)
		{
			glDeleteBuffers(1, &m_uvVBO);
		}
		if (m_normalVBO != 0)
		{
			glDeleteBuffers(1, &m_normalVBO);
		}
		if (m_tangentVBO != 0)
		{
			glDeleteBuffers(1, &m_tangentVBO);
		}
		if (m_indexVBO != 0)
		{
			glDeleteBuffers(1, &m_indexVBO);
		}
	}
};