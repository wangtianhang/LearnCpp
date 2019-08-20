#pragma once

#include "gl3w.h"
#include "./MeshFliter.h"
#include "./Material.h"
#include "./Learn3D/Transform.h"
#include "./BoneAnimation.h"

struct MeshRenderObject
{
public:
	//bool m_isIndex = true;
	//GLuint m_vao = 0;
	//int m_vertexCount = 0; // indexÊýÁ¿
	Transform m_transform;

	MeshFliter m_meshData;
	
	Material m_material;

	BoneAnimation * m_boneAnimation;

	GLfloat * m_vertex_positions = NULL;
	GLfloat * m_vertex_normals = NULL;

// 	void InitShader(std::string vertexShader, std::string pixelShader)
// 	{
// 
// 	}

// 	void InitVAO(GLuint vao, int vertexCount, bool isIndex)
// 	{
// 
// 	}

// 	void UnInit()
// 	{
// 
// 	}

	void UnInit()
	{
		if (m_boneAnimation != nullptr)
		{
			m_boneAnimation->UnInit();
			delete m_boneAnimation;
			m_boneAnimation = NULL;
		}

		m_meshData.UnInit();

		m_material.UnInit();

		if (m_vertex_positions != nullptr)
		{
			delete m_vertex_positions;
			m_vertex_positions = nullptr;
		}

		if (m_vertex_normals != nullptr)
		{
			delete m_vertex_normals;
			m_vertex_normals = nullptr;
		}
	}

	void SetBoneAnimation(BoneAnimation * boneAnimation)
	{
		m_boneAnimation = boneAnimation;
		//if (m_vertex_positions == nullptr)
		{
			m_vertex_positions = new GLfloat[m_meshData.m_vertices.size() * 3];
		}
		//if (m_vertex_normals == nullptr)
		{
			m_vertex_normals = new GLfloat[m_meshData.m_normals.size() * 3];
		}
	}

	void UpdateSkin(float delta)
	{
		if (m_boneAnimation != NULL)
		{
			m_boneAnimation->Update(delta);

			std::vector<Matrix4x4> vertexToModel;
			for (int i = 0; i < m_meshData.m_bindPoses.size(); ++i)
			{
				Matrix4x4 mat = m_boneAnimation->m_boneTransformVec[i]->GetLocalToWorldMatrix() * m_meshData.m_bindPoses[i];
				vertexToModel.push_back(mat);
			}

			int count = m_meshData.m_vertices.size();
			for (int i = 0; i < count; ++i)
			{
				Vector3 iter = m_meshData.m_vertices[i];
				Vector3 normal = m_meshData.m_normals[i];
				BoneWeight weight = m_meshData.m_boneWeights[i];
				Matrix4x4 mat0 = vertexToModel[weight.m_index0];
				Matrix4x4 mat1 = vertexToModel[weight.m_index1];
				Matrix4x4 mat2 = vertexToModel[weight.m_index2];
				Matrix4x4 mat3 = vertexToModel[weight.m_index3];
				Vector3 newPos = mat0.MultiplyPoint(iter) * weight.m_weight0 +
					mat1.MultiplyPoint(iter) * weight.m_weight1 +
					mat2.MultiplyPoint(iter) * weight.m_weight2 +
					mat3.MultiplyPoint(iter) * weight.m_weight3;
				//posVertices.push_back(newPos);
				Vector3 newNormal = mat0.MultiplyVector(normal) * weight.m_weight0 +
					mat1.MultiplyVector(normal) * weight.m_weight1 +
					mat2.MultiplyVector(normal) * weight.m_weight2 +
					mat3.MultiplyVector(normal) * weight.m_weight3;
				m_vertex_positions[3 * i] = newPos.x /*+ Mathf::Sin(m_boneAnimation->m_curTime)*/;
				m_vertex_positions[3 * i + 1] = newPos.y;
				m_vertex_positions[3 * i + 2] = newPos.z;
				m_vertex_normals[3 * i] = newNormal.x;
				m_vertex_normals[3 * i + 1] = newNormal.y;
				m_vertex_normals[3 * i + 2] = newNormal.z;
			}

			int size_vertex_positions = m_meshData.m_vertices.size() * 3 * 4;
			glBindBuffer(GL_ARRAY_BUFFER, m_meshData.m_positionVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size_vertex_positions, m_vertex_positions);
			glBindBuffer(GL_ARRAY_BUFFER, m_meshData.m_normalVBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size_vertex_positions, m_vertex_normals);
		}
	}

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

		
// 		if (m_material.m_useOutProgram)
// 		{
// 			glUseProgram(m_material.m_outProgram);
// 		}
// 		else
// 		{
			glUseProgram(m_material.m_renderProgram);
/*		}*/
		
		glFrontFace(m_meshData.m_frontFace);
		glBindVertexArray(m_meshData.m_vao);
		if (m_meshData.m_isIndex)
		{
			if (m_meshData.m_bigIndex)
			{
				glDrawElements(GL_TRIANGLES, m_meshData.drawVerticesCount, GL_UNSIGNED_INT, 0);
			}
			else
			{
				glDrawElements(GL_TRIANGLES, m_meshData.drawVerticesCount, GL_UNSIGNED_SHORT, 0);
			}
			
		}
		else
		{
			glDrawArrays(GL_TRIANGLES, 0, m_meshData.drawVerticesCount);
		}
	}


};