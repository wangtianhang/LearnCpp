#pragma once

#include "gl3w.h"

struct MeshData
{
public:
	GLuint m_vao = 0;
	GLuint m_positionVBO = 0;
	GLuint m_normalVBO = 0;
	GLuint m_indexVBO = 0;
	int drawVerticesCount = 0;
	GLenum m_frontFace = GL_CCW;
};