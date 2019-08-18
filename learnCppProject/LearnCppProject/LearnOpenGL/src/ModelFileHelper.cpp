#pragma once

//#include <iostream>
//#include <string>
#include <fstream>
#include<sstream>

#include "./ModelFileHelper.h"
#include "./GUtil.h"
#include "./Learn3D/MathHelper.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
/*

*/

extern MeshFliter GetMeshFilter(std::vector<Vector3> vertices,
std::vector<Vector3> normals,
std::vector<GLuint> indexs)
{
	MeshFliter ret;
	ret.m_frontFace = GL_CW;
	ret.m_bigIndex = true;

	GLfloat * vertex_positions = new GLfloat[vertices.size() * 3];
	GLuint * vertex_indices = new GLuint[indexs.size()];
	GLfloat * vertex_normals = new GLfloat[normals.size() * 3];

	for (int i = 0; i < vertices.size(); ++i)
	{
		vertex_positions[i * 3] = vertices[i].x;
		vertex_positions[i * 3 + 1] = vertices[i].y;
		vertex_positions[i * 3 + 2] = vertices[i].z;
	}

	for (int i = 0; i < indexs.size(); ++i)
	{
		vertex_indices[i] = indexs[i];
	}

	for (int i = 0; i < normals.size(); ++i)
	{
		vertex_normals[i * 3] = normals[i].x;
		vertex_normals[i * 3 + 1] = normals[i].y;
		vertex_normals[i * 3 + 2] = normals[i].z;
	}

	int size_vertex_positions = vertices.size() * 3 * 4;
	int size_vertex_indices = indexs.size() * 4;
	ret.drawVerticesCount = indexs.size();
	int size_vertex_normals = normals.size() * 3 * 4;

	//GLuint vao = 0;
	glGenVertexArrays(1, &ret.m_vao);
	glBindVertexArray(ret.m_vao);

	glGenBuffers(1, &ret.m_positionVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.m_positionVBO);
	glBufferData(GL_ARRAY_BUFFER,
		size_vertex_positions,
		vertex_positions,
		GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &ret.m_normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, ret.m_normalVBO);
	glBufferData(GL_ARRAY_BUFFER,
		size_vertex_normals,
		vertex_normals,
		GL_STATIC_DRAW);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(3);

	glGenBuffers(1, &ret.m_indexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.m_indexVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		size_vertex_indices,
		vertex_indices,
		GL_STATIC_DRAW);

	return ret;
}

Matrix4x4 Convert(aiMatrix4x4 offset)
{
	Matrix4x4 ret;

	ret.m00 = offset.a1;
	ret.m01 = offset.a2;
	ret.m02 = offset.a3;
	ret.m03 = offset.a4;

	ret.m10 = offset.b1;
	ret.m11 = offset.b2;
	ret.m12 = offset.b3;
	ret.m13 = offset.b4;

	ret.m20 = offset.c1;
	ret.m21 = offset.c2;
	ret.m22 = offset.c3;
	ret.m23 = offset.c4;

	ret.m30 = offset.d1;
	ret.m31 = offset.d2;
	ret.m32 = offset.d3;
	ret.m33 = offset.d4;

	return ret;
}

Transform * processHierarchyTransform(const aiNode * aiNolde, std::vector<Transform *> & boneTransformVec)
{
	Transform * transform = new Transform();
	transform->m_name = std::string(aiNolde->mName.C_Str());
	Matrix4x4 localToWorldMatrix = Convert(aiNolde->mTransformation);
	if (transform->m_name == "Bip001 Spine")
	{
		int test = 0;
		GUtil::Log("Bip001 Spine origin matrix " + localToWorldMatrix.ToString());
	}
	transform->m_localPostion = MathHelper::GetPosition(localToWorldMatrix);
	transform->m_localRotation = MathHelper::GetRotation(localToWorldMatrix);
	Vector3 localEuler = transform->GetLocalEulerAngles();
	transform->m_localScale = MathHelper::GetScale(localToWorldMatrix);
	for (unsigned int i = 0; i < aiNolde->mNumChildren; i++)
	{
		Transform * childTrans = processHierarchyTransform(aiNolde->mChildren[i], boneTransformVec);
		transform->m_childList.push_back(childTrans);
	}
	boneTransformVec.push_back(transform);
	return transform;
}

const aiNode * FindNode(const aiNode * node, aiString nodeName)
{
	if (node->mName == nodeName)
	{
		return node;
	}
	else
	{
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			const aiNode * childNode = FindNode(node->mChildren[i], nodeName);
			if (childNode != nullptr)
			{
				return childNode;
			}
		}
		return nullptr;
	}
}

void processBoneAnimation(std::vector<std::string> & boneNameVec, const aiScene *scene, aiAnimation *animation, std::vector<Transform *> & boneTransformVec, std::vector<aiNodeAnim *> & animVec)
{
	const aiNode * rootNode = FindNode(scene->mRootNode, aiString(animation->mChannels[0]->mNodeName));
	std::vector<Transform *> tmpBoneTransformVec;
	processHierarchyTransform(rootNode, tmpBoneTransformVec);
	for (int i = 0; i < boneNameVec.size(); ++i)
	{
		for (int j = 0; j < tmpBoneTransformVec.size(); ++j)
		{
			if (tmpBoneTransformVec[j]->m_name == boneNameVec[i])
			{
				boneTransformVec.push_back(tmpBoneTransformVec[j]);
				break;
			}
		}
	}
	for (int i = 0; i < boneNameVec.size(); ++i)
	{
		for (int j = 0; j < animation->mNumChannels; ++j)
		{
			if (animation->mChannels[j]->mNodeName == aiString(boneNameVec[i].c_str()))
			{
				animVec.push_back(animation->mChannels[j]);
				break;
			}
		}
	}
	for (int i = 0; i < boneTransformVec.size(); ++i)
	{
		GUtil::Log(boneTransformVec[i]->m_name + " localpos " + boneTransformVec[i]->GetLocalPosition().toString() + 
			" localeuler " + boneTransformVec[i]->GetLocalEulerAngles().toString());
	}
}

void processMesh(aiMesh *mesh, const aiScene *scene, bool inverseZ, MeshFliter & meshFilter, BoneAnimation & boneAnimation)
{
	std::vector<Vector3> vertices;
	std::vector<GLuint> indices;
	//std::vector<Texture> textures;
	std::vector<Vector3> normals;
	std::vector<BoneWeight> boneWeights;

	Matrix4x4 inverseMat = Matrix4x4::TRS(Vector3::zero(), Quaternion::Euler(Vector3(0, 180, 0)), Vector3::one());

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vector3 vertex;
		// 处理顶点位置、法线和纹理坐标
		vertex.x = mesh->mVertices[i].x;
		vertex.y = mesh->mVertices[i].y;
		vertex.z = mesh->mVertices[i].z;
		if (inverseZ)
		{
			vertex = inverseMat.MultiplyPoint(vertex);
		}
		vertices.push_back(vertex);

		Vector3 normal;
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;
		if (inverseZ)
		{
			normal = inverseMat.MultiplyVector(normal);
		}
		normals.push_back(normal);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	meshFilter = GetMeshFilter(vertices, normals, indices);

	//===================解析骨骼和骨骼动画=======================
	if (mesh->mNumBones == 0)
	{
		return;
	}
	meshFilter.m_vertices = vertices;
	for (int i = 0; i < vertices.size(); ++i)
	{
		boneWeights.push_back(BoneWeight());
	}

	std::vector<std::string> boneNameVec;
	int numBones = mesh->mNumBones;
	for (int i = 0; i < numBones; ++i)
	{
		aiBone * bone = mesh->mBones[i];
		Matrix4x4 bindPose = Convert(bone->mOffsetMatrix);
		meshFilter.m_bindPoses.push_back(bindPose);
		boneNameVec.push_back(bone->mName.C_Str());
		for (int j = 0; j < bone->mNumWeights; ++j)
		{
			aiVertexWeight weight = bone->mWeights[j];
			boneWeights[weight.mVertexId].AddWeight(j, weight.mWeight);
		}
	}

	if (scene->mNumAnimations > 0)
	{
		aiAnimation * animation = scene->mAnimations[0];
		boneAnimation.m_framePerSecond = animation->mTicksPerSecond;
		boneAnimation.m_totalFrame = animation->mDuration;
// 		for (int i = 0; i < animation->mNumChannels; ++i)
// 		{
// 			//aiNodeAnim * anim = animation->mChannels[0];
// 			//int test = 0;
// 			aiNodeAnim * anim = animation->mChannels[i];
// 		}
		
		processBoneAnimation(boneNameVec, scene, animation, boneAnimation.m_boneTransformVec, boneAnimation.m_aiNodeAnimVec);
	}
	//=========================================
}

void processNode(aiNode *node, const aiScene *scene, std::vector<MeshFliter>& meshFilterVec, std::vector<BoneAnimation> & boneAnimationVec, bool inverseZ)
{
	// 处理节点所有的网格（如果有的话）
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		MeshFliter meshFilter;
		BoneAnimation boneAnimation;
		processMesh(mesh, scene, inverseZ, meshFilter, boneAnimation);
		meshFilterVec.push_back(meshFilter);
		boneAnimationVec.push_back(boneAnimation);
	}
	// 接下来对它的子节点重复这一过程
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, meshFilterVec, boneAnimationVec, inverseZ);
	}
}

bool ModelFileHelper::loadMeshAsVAO(std::string path, std::vector<MeshFliter> & ret, bool inverseZ)
{
	std::vector<BoneAnimation> boneAnimation;
	return loadBoneAnimation(path, ret, boneAnimation, inverseZ);
}

bool ModelFileHelper::loadBoneAnimation(std::string path, std::vector<MeshFliter> & ret, std::vector<BoneAnimation> & boneAnimation, bool inverseZ /*= true*/)
{
	Assimp::Importer import;
	const aiScene *scene = import.ReadFile(path, aiProcessPreset_TargetRealtime_Quality | aiProcess_ConvertToLeftHanded);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		GUtil::Log(std::string("ERROR::ASSIMP::") + import.GetErrorString());
		return false;
	}
	std::string directory = path.substr(0, path.find_last_of('/'));

	//std::vector<MeshFliter> meshFilterVec;
	processNode(scene->mRootNode, scene, ret, boneAnimation, inverseZ);
	return true;
}

// void ObjFileHelper::load_obj(const char* filename, std::vector<Vector3> &vertices, std::vector<Vector3> &normals, std::vector<GLuint> &elements)
// {
// 	using namespace std;
// 	ifstream in(filename, ios::in);
// 	if (!in)
// 	{
// 		cerr << "Cannot open " << filename << endl; exit(1);
// 	}
// 
// 	string line;
// 	while (getline(in, line))
// 	{
// 		if (line.substr(0, 2) == "v ")
// 		{
// 			istringstream s(line.substr(2));
// 			Vector3 v;
// 			s >> v.x;
// 			s >> v.y;
// 			s >> v.z;
// 			vertices.push_back(v);
// 		}
// 		else if (line.substr(0, 2) == "f ")
// 		{
// 			istringstream s(line.substr(2));
// 			GLushort a, b, c;
// 			s >> a;
// 			s >> b;
// 			s >> c;
// 			a--;
// 			b--;
// 			c--;
// 			elements.push_back(a); elements.push_back(b); elements.push_back(c);
// 		}
// 		else if (line[0] == '#')
// 		{
// 			// ignoring this line
// 		}
// 		else
// 		{
// 			// ignoring this line
// 		}
// 	}
// 
// 	// 3dmax 为右手坐标系 需要转换下坐标
// //  	for (int i = 0; i < vertices.size(); ++i)
// //  	{
// //  		Vector3 iter = vertices[i];
// //  		iter.x = -iter.x;
// //  		vertices[i] = iter;
// //  	}
// 
// 	normals.resize(vertices.size(), Vector3(0.0, 0.0, 0.0));
// 	for (int i = 0; i < elements.size(); i += 3)
// 	{
// 		GLuint ia = elements[i];
// 		GLuint ib = elements[i + 1];
// 		GLuint ic = elements[i + 2];
// 		Vector3 v1 = vertices[ia];
// 		Vector3 v2 = vertices[ib];
// 		Vector3 v3 = vertices[ic];
// 		Vector3 normal = Vector3::Normalize(Vector3::Cross(
// 			v2 - v1,
// 			v3 - v1));
// 		normals[ia] = normals[ib] = normals[ic] = normal;
// 	}
// 
// }

// MeshFliter ObjFileHelper::loadObjAsVAO2(const char* filename)
// {
// 	MeshFliter ret;
// 	ret.m_frontFace = GL_CW;
// 
// 	std::vector<Vector3> vertices;
// 	std::vector<Vector3> normals;
// 	std::vector<GLuint> indexs;
// 	load_obj(filename, vertices, normals, indexs);
// 	GLfloat * vertex_positions = new GLfloat[vertices.size() * 3];
// 	GLuint * vertex_indices = new GLuint[indexs.size()];
// 	GLfloat * vertex_normals = new GLfloat[normals.size() * 3];
// 
// 	for (int i = 0; i < vertices.size(); ++i)
// 	{
// 		vertex_positions[i * 3] = vertices[i].x;
// 		vertex_positions[i * 3 + 1] = vertices[i].y;
// 		vertex_positions[i * 3 + 2] = vertices[i].z;
// 	}
// 
// 	for (int i = 0; i < indexs.size(); ++i)
// 	{
// 		vertex_indices[i] = indexs[i];
// 	}
// 
// 	for (int i = 0; i < normals.size(); ++i)
// 	{
// 		vertex_normals[i * 3] = normals[i].x;
// 		vertex_normals[i * 3 + 1] = normals[i].y;
// 		vertex_normals[i * 3 + 2] = normals[i].z;
// 	}
// 
// 	int size_vertex_positions = vertices.size() * 3 * 4;
// 	int size_vertex_indices = indexs.size() * 4;
// 	ret.drawVerticesCount = indexs.size();
// 	int size_vertex_normals = normals.size() * 3 * 4;
// 
// 	//GLuint vao = 0;
// 	glGenVertexArrays(1, &ret.m_vao);
// 	glBindVertexArray(ret.m_vao);
// 
// 	glGenBuffers(1, &ret.m_positionVBO);
// 	glBindBuffer(GL_ARRAY_BUFFER, ret.m_positionVBO);
// 	glBufferData(GL_ARRAY_BUFFER,
// 		size_vertex_positions,
// 		vertex_positions,
// 		GL_STATIC_DRAW);
// 	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
// 	glEnableVertexAttribArray(0);
// 
// 	glGenBuffers(1, &ret.m_normalVBO);
// 	glBindBuffer(GL_ARRAY_BUFFER, ret.m_normalVBO);
// 	glBufferData(GL_ARRAY_BUFFER,
// 		size_vertex_normals,
// 		vertex_normals,
// 		GL_STATIC_DRAW);
// 	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
// 	glEnableVertexAttribArray(3);
// 
// 	glGenBuffers(1, &ret.m_indexVBO);
// 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret.m_indexVBO);
// 	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
// 		size_vertex_indices,
// 		vertex_indices,
// 		GL_STATIC_DRAW);
// 
// 	return ret;
// }
