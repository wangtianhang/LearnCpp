#pragma once

#include "gl3w.h"

#include <vector>

#include "./BoneWeight.h"
#include "./Learn3D/Vector3.h"
#include "./Learn3D/Matrix4x4.h"

struct MeshFliter
{
public:
	//Matrix4x4 m_localToWorld;

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
	bool m_bigIndex = false;

	//bool m_isShared = false;
	//int m_ShareCount = 1; // 非共享的情况下 不用了要delete vao和vbo
	std::vector<Vector3> m_vertices;
	std::vector<Matrix4x4> m_bindPoses;
	std::vector<BoneWeight> m_boneWeights;

	void UnInit();
//	{
// 		if (m_isShared)
// 		{
// 			if (m_ShareCount -= 1)
// 			{
// 				if (m_ShareCount > 0)
// 				{
// 					return;
// 				}
// 			}
// 		}

// 		glDeleteVertexArrays(1, &m_vao);
// 		glDeleteBuffers(1, &m_positionVBO);
// 		if (m_colorVBO != 0)
// 		{
// 			glDeleteBuffers(1, &m_colorVBO);
// 		}
// 		if (m_uvVBO != 0)
// 		{
// 			glDeleteBuffers(1, &m_uvVBO);
// 		}
// 		if (m_normalVBO != 0)
// 		{
// 			glDeleteBuffers(1, &m_normalVBO);
// 		}
// 		if (m_tangentVBO != 0)
// 		{
// 			glDeleteBuffers(1, &m_tangentVBO);
// 		}
// 		if (m_indexVBO != 0)
// 		{
// 			glDeleteBuffers(1, &m_indexVBO);
// 		}

//	}
};


