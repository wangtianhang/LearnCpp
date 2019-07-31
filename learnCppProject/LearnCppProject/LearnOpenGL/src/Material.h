#pragma once

#include "./gl3w.h"

struct Material
{
	bool m_isOpaque = true;
	GLenum m_blendFactor1 = GL_SRC_ALPHA;
	GLenum m_blendFactor2 = GL_ONE_MINUS_SRC_ALPHA;

	bool m_zwrite = true;
	bool m_ztest = true;
	GLenum m_zTestOp = GL_LEQUAL;

	bool m_cullFace = true;
	GLenum m_cullFaceType = GL_BACK;
	//GLenum m_frontFace = GL_CW;

	GLuint m_renderProgram = 0;

	bool m_useOutProgram = false;
	GLuint m_outProgram = 0;

	int m_ShareCount = 1;

	void UnInit()
	{
		if (m_ShareCount -= 1)
		{
			if (m_ShareCount > 0)
			{
				return;
			}
		}

		// todo É¾³ıshaderÊ²Ã´µÄ
	}
};