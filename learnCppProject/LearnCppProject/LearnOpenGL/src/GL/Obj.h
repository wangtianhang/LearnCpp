#pragma once

#include "gl3w.h"
#include "../Graphic/MeshData.h"

struct Obj
{
public:
	//bool m_isIndex = true;
	//GLuint m_vao = 0;
	//int m_vertexCount = 0; // indexÊýÁ¿
	MeshData m_meshData;
	
	bool m_isOpaque = true;
	GLenum m_blendFactor1 = GL_SRC_ALPHA;
	GLenum m_blendFactor2 = GL_ONE_MINUS_SRC_ALPHA;
	
	bool m_zwrite = true;
	bool m_ztest = true;
	GLenum m_zTestOp = GL_LEQUAL;

	bool m_cullFace = true;
	GLenum m_cullFaceType = GL_BACK;
	//GLenum m_frontFace = GL_CW;

	bool m_useOutProgram = false;
	GLuint m_renderProgram = 0;
	GLuint m_outProgram = 0;

// 	void InitShader(std::string vertexShader, std::string pixelShader)
// 	{
// 
// 	}

// 	void InitVAO(GLuint vao, int vertexCount, bool isIndex)
// 	{
// 
// 	}

	void RenderObj()
	{
		if (m_isOpaque)
		{
			glDisable(GL_BLEND);
		}
		else
		{
			glEnable(GL_BLEND);
			glBlendFunc(m_blendFactor1, m_blendFactor2);
		}

		if (m_zwrite)
		{
			glDepthMask(true);
		}
		else
		{
			glDepthMask(false);
		}

		if (m_ztest)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(m_zTestOp);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}

		if (m_cullFace)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(m_cullFaceType);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		
		if (m_useOutProgram)
		{
			glUseProgram(m_outProgram);
		}
		else
		{
			glUseProgram(m_renderProgram);
		}
		
		glFrontFace(m_meshData.m_frontFace);
		glBindVertexArray(m_meshData.m_vao);
		if (m_meshData.m_isIndex)
		{
			glDrawElements(GL_TRIANGLES, m_meshData.drawVerticesCount, GL_UNSIGNED_SHORT, 0);
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_meshData.drawVerticesCount);
		}
	}
};