#pragma once

#include "gl3w.h"
#include "./MeshFliter.h"
#include "./Material.h"
#include "./Learn3D/Transform.h"

struct MeshRenderObject
{
public:
	//bool m_isIndex = true;
	//GLuint m_vao = 0;
	//int m_vertexCount = 0; // indexÊýÁ¿
	Transform m_transform;

	MeshFliter m_meshData;
	
	Material m_material;

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
		if (m_material.m_isOpaque)
		{
			glDisable(GL_BLEND);
		}
		else
		{
			glEnable(GL_BLEND);
			glBlendFunc(m_material.m_blendFactor1, m_material.m_blendFactor2);
		}

		if (m_material.m_zwrite)
		{
			glDepthMask(true);
		}
		else
		{
			glDepthMask(false);
		}

		if (m_material.m_ztest)
		{
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(m_material.m_zTestOp);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}

		if (m_material.m_cullFace)
		{
			glEnable(GL_CULL_FACE);
			glCullFace(m_material.m_cullFaceType);
		}
		else
		{
			glDisable(GL_CULL_FACE);
		}

		
		if (m_material.m_useOutProgram)
		{
			glUseProgram(m_material.m_outProgram);
		}
		else
		{
			glUseProgram(m_material.m_renderProgram);
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

	void UnInit()
	{
		m_meshData.UnInit();

		m_material.UnInit();
	}
};