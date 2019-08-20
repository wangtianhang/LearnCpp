#pragma once

#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "./Learn3D/Transform.h"

// struct OneBone
// {
// public:
// 	std::string m_boneName;
// 	Transform m_bone;
// };

struct BoneAnimation
{
public:
	float m_framePerSecond = 30;
	int m_totalFrame = 0;
	/*std::vector<std::vector<Transform>> m_frameVec;*/
	//int m_beginFrame = 550;
	//int m_endFrame = 590;

	float m_curTime = 0;
	//std::vector<std::string> m_boneNameVec;
	std::vector<Transform *> m_boneTransformVec;
	std::vector<aiNodeAnim *> m_aiNodeAnimVec;

	//std::vector<int> m_curKey;

	bool m_hasInit = false;
	void Init()
	{
		if (m_hasInit)
		{
			return;
		}
		m_hasInit = true;

// 		for (int i = 0; i < m_aiNodeAnimVec.size(); ++i)
// 		{
// 			m_curKey.push_back(0);
// 		}
	}

	Vector3 Convert(aiVector3D tmp)
	{
		return Vector3(tmp.x, tmp.y, tmp.z);
	}

	Quaternion Convert(aiQuaternion tmp)
	{
		return Quaternion(tmp.x, tmp.y, tmp.z, tmp.w);
	}

	void Update(float delta)
	{
		Init();

		m_curTime += delta;

		//float oneFrameSpan = 1 / m_framePerSecond;
		// 这里先不考虑性能了。。
		for (int i = 0; i < m_boneTransformVec.size(); ++i)
		{
			{
				aiVectorKey beginPosKey;
				aiVectorKey endPosKey;
				GetPosKey(m_curTime, m_aiNodeAnimVec[i], beginPosKey, endPosKey);
				float weight = (m_curTime - beginPosKey.mTime) / (endPosKey.mTime - beginPosKey.mTime);
				Vector3 beginLocalPos = Convert(beginPosKey.mValue);
				Vector3 endLocalPos = Convert(endPosKey.mValue);
				Vector3 curLocalPos = Vector3::Lerp(beginLocalPos, endLocalPos, weight);

				m_boneTransformVec[i]->SetLocalPosition(curLocalPos);
			}


			{
				aiQuatKey beginQuaKey;
				aiQuatKey endQuaKey;
				GetQuaKey(m_curTime, m_aiNodeAnimVec[i], beginQuaKey, endQuaKey);
				float weight = (m_curTime - beginQuaKey.mTime) / (endQuaKey.mTime - beginQuaKey.mTime);
				Quaternion beginLocalQua = Convert(beginQuaKey.mValue);
				Quaternion endLocalQua = Convert(endQuaKey.mValue);
				Quaternion curQua = Quaternion::Slerp(beginLocalQua, endLocalQua, weight);

				m_boneTransformVec[i]->SetLocalRotation(curQua);
			}
		}
	}

	void GetPosKey(float time, aiNodeAnim * animation, aiVectorKey & beginKey, aiVectorKey & endKey)
	{
		if (time == 0)
		{
			beginKey = animation->mPositionKeys[0];
			endKey = animation->mPositionKeys[1];
			return;
		}
		if (time >= animation->mPositionKeys[animation->mNumPositionKeys - 1].mTime)
		{
			beginKey = animation->mPositionKeys[animation->mNumPositionKeys - 2];
			endKey = animation->mPositionKeys[animation->mNumPositionKeys - 1];
			return;
		}
		for (int i = 0; i < animation->mNumPositionKeys; ++i)
		{
			if (time < animation->mPositionKeys[i].mTime)
			{
				beginKey = animation->mPositionKeys[i - 1];
				endKey = animation->mPositionKeys[i];
				return;
			}
		}
	}

	void GetQuaKey(float time, aiNodeAnim * animation, aiQuatKey & beginKey, aiQuatKey & endKey)
	{
		if (time == 0)
		{
			beginKey = animation->mRotationKeys[0];
			endKey = animation->mRotationKeys[1];
			return;
		}
		if (time >= animation->mRotationKeys[animation->mNumRotationKeys - 1].mTime)
		{
			beginKey = animation->mRotationKeys[animation->mNumRotationKeys - 2];
			endKey = animation->mRotationKeys[animation->mNumRotationKeys - 1];
			return;
		}
		for (int i = 0; i < animation->mNumRotationKeys; ++i)
		{
			if (time < animation->mRotationKeys[i].mTime)
			{
				beginKey = animation->mRotationKeys[i - 1];
				endKey = animation->mRotationKeys[i];
				return;
			}
		}
	}
};