#pragma once

#include "gl3w.h"

struct MeshData
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

	bool m_isShare = false; // �ǹ��������� ������Ҫdelete vao��vbo
};