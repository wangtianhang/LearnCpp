#pragma once

//#include <iostream>
//#include <string>
#include <fstream>
#include<sstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./DebugMemory.h"

#include "./ModelFileHelper.h"
#include "./GUtil.h"
#include "./Learn3D/MathHelper.h"


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

	delete vertex_positions;
	delete vertex_indices;
	delete vertex_normals;

	return ret;
}

#pragma region boneAnimation




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
//	if (transform->m_name == "Bip001 Pelvis")
//	{
// 		int test = 0;
// 		GUtil::Log(transform->m_name + " origin matrix \n" + localToWorldMatrix.ToString());
// 		Quaternion qua = MathHelper::GetRotation(localToWorldMatrix);
// 		GUtil::Log("euler1 " + qua.eulerAngles().toString());
		//GUtil::Log("euler2 " + dxQua.eulerAngles().toString());
	
// 		Matrix4x4 src = localToWorldMatrix;
// 		Matrix4x4 des = src;
// 		des.m01 = -src.m01;
// 		des.m02 = -src.m02;
// 		des.m02 = -src.m03;
// 
// 		des.m10 = -src.m10;
// 
// 		des.m20 = -src.m20;
// 		des.m23 = -src.m23;
// 
// 		Matrix4x4 x = des * src.inverse();
// 		GUtil::Log(transform->m_name + " x matrix \n" + x.ToString());
// 		GUtil::Log(MathHelper::GetPosition(x).toString());
// 		GUtil::Log(MathHelper::GetRotation(x).eulerAngles().toString());
// 		GUtil::Log(MathHelper::GetScale(x).toString());
//	}
	// 下面这两处很奇怪 不知道为何需要转一下
	bool copyUnity = false;
	Vector3 pos = MathHelper::GetPosition(localToWorldMatrix);
	if (copyUnity)
	{
		pos.x = -pos.x;
		pos.z = -pos.z;
	}

	transform->SetLocalPosition(pos);
	Vector3 euler = MathHelper::GetRotation(localToWorldMatrix).eulerAngles();
	if (copyUnity)
	{
		euler.x = -euler.x;
		euler.z = -euler.z;
	}
	transform->SetLocalEulerAngles(euler);
	Vector3 scale = MathHelper::GetScale(localToWorldMatrix);
	transform->SetLocalScale(scale);
// 	if (transform->m_name == "Bip001 Pelvis")
// 	{
// 		int test = 0;
// 	}
	
	for (unsigned int i = 0; i < aiNolde->mNumChildren; i++)
	{
		Transform * childTrans = processHierarchyTransform(aiNolde->mChildren[i], boneTransformVec);
		Vector3 cacheLocalPos = childTrans->GetLocalPosition();
		Vector3 cacheLocalEuler = childTrans->GetLocalEulerAngles();
		Vector3 cacheLocalScale = childTrans->GetLocalScale();
		childTrans->SetParent(transform);
		childTrans->SetLocalPosition(cacheLocalPos);
		childTrans->SetLocalEulerAngles(cacheLocalEuler);
		childTrans->SetLocalScale(cacheLocalScale);
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

// Vector3 Convert(aiVector3D tmp)
// {
// 	return Vector3(tmp.x, tmp.y, tmp.z);
// }
// 
// Quaternion Convert(aiQuaternion tmp)
// {
// 	return Quaternion(tmp.x, tmp.y, tmp.z, tmp.w);
// }

// Vector3 Convert(aiVector3D tmp)
// {
// 	return Vector3(tmp.x, tmp.y, tmp.z);
// }
// 
// Quaternion Convert(aiQuaternion tmp)
// {
// 	return Quaternion(tmp.x, tmp.y, tmp.z, tmp.w);
// }

VectorKey Covnert2(aiVectorKey key)
{
	VectorKey ret;
	ret.mTime = key.mTime;
	ret.mValue = Vector3(key.mValue.x, key.mValue.y, key.mValue.z);
	return ret;
}

QuatKey Convert3(aiQuatKey key)
{
	QuatKey ret;
	ret.mTime = key.mTime;
	ret.mValue = Quaternion(key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w);
	return ret;
}

void processBoneAnimation(std::vector<std::string> & boneNameVec, const aiScene *scene, aiAnimation *animation, BoneAnimation * boneAnimation)
{
	const aiNode * bone001 = FindNode(scene->mRootNode, aiString("Bone001"));
// 	Matrix4x4 localToWorldMatrix = Convert(bone001->mTransformation);
// 	GUtil::Log("Bone001 origin matrix " + localToWorldMatrix.ToString());
// 	GUtil::Log(MathHelper::GetPosition(localToWorldMatrix).toString());
// 	GUtil::Log(MathHelper::GetRotation(localToWorldMatrix).eulerAngles().toString());
// 	GUtil::Log(MathHelper::GetScale(localToWorldMatrix).toString());

	const aiNode * bip001Node = FindNode(scene->mRootNode, aiString(animation->mChannels[0]->mNodeName));
	std::vector<Transform *> fullBoneTransformVec;
	Transform * bip001Transform = processHierarchyTransform(bip001Node, fullBoneTransformVec);

	bool debug = true;
	if (debug)
	{
		// todo Bone001 的parent还有好几层。。从父节点感觉可以读取出旋转和缩放数据
		Transform * bone001 = new Transform;
		bone001->m_name = "Bone001";
		bone001->SetLocalEulerAngles(Vector3(0, 270, 180));
		bone001->SetLocalScale(Vector3(0.05256505f, 0.05256505f, 0.05256505f));
		Vector3 cacheLocalPos = bip001Transform->GetLocalPosition();
		Vector3 cacheLocalEuler = bip001Transform->GetLocalEulerAngles();
		Vector3 cacheLocalScale = bip001Transform->GetLocalScale();
		bip001Transform->SetParent(bone001);
		bip001Transform->SetLocalPosition(cacheLocalPos);
		bip001Transform->SetLocalEulerAngles(cacheLocalEuler);
		bip001Transform->SetLocalScale(cacheLocalScale);
		fullBoneTransformVec.push_back(bone001);
	}

	for (int i = 0; i < boneNameVec.size(); ++i)
	{
		for (int j = 0; j < fullBoneTransformVec.size(); ++j)
		{
			if (fullBoneTransformVec[j]->m_name == boneNameVec[i])
			{
				boneAnimation->m_boneTransformVec.push_back(fullBoneTransformVec[j]);
				break;
			}
		}
	}

	std::vector<Transform *> allAnimationTransformVec;
	for (int j = 0; j < animation->mNumChannels; ++j)
	{
		for (int i = 0; i < fullBoneTransformVec.size(); ++i)
		{
			if (animation->mChannels[j]->mNodeName == aiString(fullBoneTransformVec[i]->m_name.c_str()))
			{
				allAnimationTransformVec.push_back(fullBoneTransformVec[i]);
				aiNodeAnim * nodeAnim = animation->mChannels[j];
				ChannelFrameData * data = new ChannelFrameData();

				for (int i = 0; i < nodeAnim->mNumPositionKeys; ++i)
				{
					data->m_posKeyVec.push_back(Covnert2(nodeAnim->mPositionKeys[i]));
				}
				for (int i = 0; i < nodeAnim->mNumRotationKeys; ++i)
				{
					data->m_quaKeyVec.push_back(Convert3(nodeAnim->mRotationKeys[i]));
				}
				for (int i = 0; i < nodeAnim->mNumScalingKeys; ++i)
				{
					data->m_scaleVec.push_back(Covnert2(nodeAnim->mScalingKeys[i]));
				}

				boneAnimation->m_channelVec.push_back(data);
				break;
			}
		}
	}

	//boneAnimation->m_boneTransformVec = boneTransformVec;
	boneAnimation->m_fullTransformVec = allAnimationTransformVec;

//	if (false)
//	{
// 		for (int i = 0; i < fullBoneTransformVec.size(); ++i)
// 		{
// 			Transform * iter = fullBoneTransformVec[i];
// 			if (iter->m_name == "Bone001"
// 				|| iter->m_name == "Bip001"
// 				|| iter->m_name == "Bip001 Pelvis"
// 				|| iter->m_name == "Bip001 Spine")
// 			{
// 				if (iter->m_name == "Bone001")
// 				{
// 					int test = 0;
// 				}
// 				if (iter->m_name == "Bip001")
// 				{
// 					int test = 0;
// 				}
// 				if (iter->m_name == "Bip001 Pelvis")
// 				{
// 					int test = 0;
// 				}
// 				GUtil::Log(iter->m_name + " localpos " + iter->GetLocalPosition().toString() +
// 					" localeuler " + iter->GetLocalEulerAngles().toString() +
// 					" localScale " + iter->GetLocalScale().toString() +
// 					" worldPos " + iter->GetPosition().toString() +
// 					" worldEuler " + iter->GetEulerAngles().toString() +
// 					" worldScale " + iter->GetLossyScale().toString());
// 			}
// 		}
//	}


// 	for (int i = 0; i < boneTransformVec.size(); ++i)
// 	{
// 		Transform * iter = boneTransformVec[i];
// 		{
// // 			GUtil::Log(iter->m_name + " localpos " + iter->GetLocalPosition().toString() +
// // 				" localeuler " + iter->GetLocalEulerAngles().toString() + 
// // 				" worldPos " + iter->GetPosition().toString() + 
// // 				" worldEuler " + iter->GetEulerAngles().toString() + 
// // 			    " worldScale " + iter->GetLossyScale().toString());
// 		}
// 	}
	//aiQuaternion key = animVec[0]->mRotationKeys[0].mValue;
	//Quaternion bip001Qua = Quaternion(key.x, key.y, key.z, key.w);
	//GUtil::Log("bip001 euler " + bip001Qua.eulerAngles().toString());
	
	
}

void processMesh(aiMesh *mesh, const aiScene *scene, bool inverseZ, bool readBone, MeshFliter & meshFilter, BoneAnimation * pBoneAnimation)
{
	std::vector<Vector3> vertices;
	std::vector<GLuint> indices;
	//std::vector<Texture> textures;
	std::vector<Vector3> normals;
	

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

	
	

	//===================解析骨骼和骨骼动画=======================
	if (!readBone)
	{
		meshFilter = GetMeshFilter(vertices, normals, indices);
		return;
	}

	if (mesh->mNumBones == 0)
	{
		return;
	}
	//meshFilter.m_vertices = vertices;
	std::vector<BoneWeight> boneWeights;
	for (int i = 0; i < vertices.size(); ++i)
	{
		boneWeights.push_back(BoneWeight());
	}
	//meshFilter.m_normals = normals;

	std::vector<std::string> boneNameVec;
	//int numBones = mesh->mNumBones;
	std::vector<Matrix4x4> bindPoses;
	for (int i = 0; i < mesh->mNumBones; ++i)
	{
		aiBone * bone = mesh->mBones[i];
		Matrix4x4 bindPose = Convert(bone->mOffsetMatrix);
		bindPoses.push_back(bindPose);
		boneNameVec.push_back(bone->mName.C_Str());
		for (int j = 0; j < bone->mNumWeights; ++j)
		{
			aiVertexWeight weight = bone->mWeights[j];
			boneWeights[weight.mVertexId].AddWeight(i, weight.mWeight);
		}
	}

	if (scene->mNumAnimations > 0)
	{
		aiAnimation * animation = scene->mAnimations[0];
		pBoneAnimation->m_framePerSecond = animation->mTicksPerSecond;
		pBoneAnimation->m_totalFrame = animation->mDuration;
// 		for (int i = 0; i < animation->mNumChannels; ++i)
// 		{
// 			//aiNodeAnim * anim = animation->mChannels[0];
// 			//int test = 0;
// 			aiNodeAnim * anim = animation->mChannels[i];
// 		}
		
		processBoneAnimation(boneNameVec, scene, animation, pBoneAnimation);
	}
	//=====================测试静态骨骼数据====================

// 	GUtil::Log("vertexCount " + vertices.size());
// 	std::string vertexData;
// 	for (int i = 0; i < 100; ++i)
// 	{
// 		vertexData += vertices[i].toString() + "\n";
// 	}
// 	GUtil::Log("vertexData \n" + vertexData);
// 
// 	std::vector<Matrix4x4> vertexToModel;
// 	for (int i = 0; i < boneNameVec.size(); ++i)
// 	{
// 		Matrix4x4 mat = boneAnimation->m_boneTransformVec[i]->GetLocalToWorldMatrix() * bindPoses[i];
// 		vertexToModel.push_back(mat);
// 	}
	
// 	std::vector<Vector3> posVertices;
// 	for (int i = 0; i < vertices.size(); ++i)
// 	{
// 		Vector3 iter = vertices[i];
// 		BoneWeight weight = boneWeights[i];
// 		Matrix4x4 mat0 = vertexToModel[weight.m_index0];
// 		Matrix4x4 mat1 = vertexToModel[weight.m_index1];
// 		Matrix4x4 mat2 = vertexToModel[weight.m_index2];
// 		Matrix4x4 mat3 = vertexToModel[weight.m_index3];
// 		Vector3 newPos = mat0.MultiplyPoint(iter) * weight.m_weight0 + 
// 			mat1.MultiplyPoint(iter) * weight.m_weight1 + 
// 			mat2.MultiplyPoint(iter) * weight.m_weight2 + 
// 			mat3.MultiplyPoint(iter) * weight.m_weight3;
// 		posVertices.push_back(newPos);
// 	}
	//===========================================
	meshFilter = GetMeshFilter(vertices, normals, indices);
	meshFilter.m_vertices = vertices;
	meshFilter.m_normals = normals;
	meshFilter.m_bindPoses = bindPoses;
	meshFilter.m_boneWeights = boneWeights;
	//meshFilter = GetMeshFilter(posVertices, normals, indices);
}

#pragma endregion

void processNode(aiNode *node, const aiScene *scene, bool readBone, std::vector<MeshFliter>& meshFilterVec, std::vector<BoneAnimation *> & boneAnimationVec, bool inverseZ)
{
	// 处理节点所有的网格（如果有的话）
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		MeshFliter meshFilter;
		BoneAnimation * boneAnimation = new BoneAnimation(); 
		processMesh(mesh, scene, inverseZ, readBone, meshFilter, boneAnimation);
		meshFilterVec.push_back(meshFilter);
		boneAnimationVec.push_back(boneAnimation);
	}
	// 接下来对它的子节点重复这一过程
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, readBone, meshFilterVec, boneAnimationVec, inverseZ);
	}
}

bool ModelFileHelper::loadMeshAsVAO(std::string path, std::vector<MeshFliter> & ret, bool inverseZ)
{
	std::vector<BoneAnimation *> boneAnimation;
	return loadBoneAnimation(path, ret, boneAnimation, inverseZ, false);
}

bool ModelFileHelper::loadBoneAnimation(std::string path, std::vector<MeshFliter> & ret, std::vector<BoneAnimation *> & boneAnimation, bool inverseZ /*= true*/, bool readBone)
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
	processNode(scene->mRootNode, scene, readBone, ret, boneAnimation, inverseZ);
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
