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

	void Update(float delta)
	{
		Init();

		m_curTime += delta;

		//float oneFrameSpan = 1 / m_framePerSecond;
		// 这里先不考虑性能了。。
		for (int i = 0; i < m_boneTransformVec.size(); ++i)
		{
			aiVectorKey *beginPosKey;
			aiVectorKey *endPosKey;
			GetPosKey(m_curTime, m_aiNodeAnimVec[i], &beginPosKey, &endPosKey);
			float weight = (m_curTime - beginPosKey->mTime) / (endPosKey->mTime - beginPosKey->mTime);
			Vector3 beginLocalPos = Convert(beginPosKey->mValue);
			Vector3 endLocalPos = Convert(endPosKey->mValue);
			Vector3 curLocalPos = Vector3::Lerp(beginLocalPos, endLocalPos, weight);

			m_boneTransformVec[i]->SetLocalPosition(curLocalPos);
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
		for (int i = 0; i < animation->mNumPositionKeys; ++i)
		{
			if (time < animation->mPositionKeys[i].mTime)
			{

			}
		}
	}

	aiVectorKey * GetEulerKey(float time)
	{

	}
};