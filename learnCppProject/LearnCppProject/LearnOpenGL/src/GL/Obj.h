#pragma once

#include "gl3w.h"

struct Obj
{
public:
	bool m_isIndex = true;
	GLuint m_vao = 0;
	int m_vertexCount = 0; // indexÊýÁ¿
	
	bool m_isOpaque = true;
	GLenum m_blendFactor1 = GL_SRC_ALPHA;
	GLenum m_blendFactor2 = GL_ONE_MINUS_SRC_ALPHA;
	
	bool m_zwrite = true;
	bool m_ztest = true;
	GLenum m_zTestOp = GL_LEQUAL;

	bool m_cullFace = true;
	GLenum m_cullFaceType = GL_BACK;
	GLenum m_frontFace = GL_CW;

	bool m_useOutProgram = false;
	GLuint m_renderProgram = 0;
	GLuint m_outProgram = 0;

	void InitShader(std::string vertexShader, std::string pixelShader)
	{

	}

	void InitVAO(GLuint vao, int vertexCount, bool isIndex)
	{

	}

	void RenderObj()
	{

	}
};