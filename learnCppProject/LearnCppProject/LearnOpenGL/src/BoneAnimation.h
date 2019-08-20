#pragma once

#include <vector>

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//#include <assimp/anim.h>

#include "./Learn3D/Transform.h"

// struct OneBone
// {
// public:
// 	std::string m_boneName;
// 	Transform m_bone;
// };

struct VectorKey
{
public:
	double mTime;
	Vector3 mValue;
};

struct QuatKey
{
public:
	double mTime;
	Quaternion mValue;
};

struct ChannelFrameData
{
public:
	std::vector<VectorKey> m_posKeyVec;
	std::vector<QuatKey> m_quaKeyVec;
	std::vector<VectorKey> m_scaleVec;
};

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
	//std::vector<aiNodeAnim *> m_aiNodeAnimVec;
	std::vector<Transform *> m_fullTransformVec;
	std::vector<ChannelFrameData *> m_channelVec;

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
		float oneFrameSpan = 1 / m_framePerSecond;
		for (int i = 0; i < m_channelVec.size(); ++i)
		{
			ChannelFrameData* iter = m_channelVec[i];
			for (int j = 0; j < iter->m_posKeyVec.size(); ++j)
			{
				iter->m_posKeyVec[j].mTime *= oneFrameSpan;
			}
			for (int j = 0; j < iter->m_quaKeyVec.size(); ++j)
			{
				iter->m_quaKeyVec[j].mTime *= oneFrameSpan;
			}
			for (int j = 0; j < iter->m_scaleVec.size(); ++j)
			{
				iter->m_scaleVec[j].mTime *= oneFrameSpan;
			}
		}
	}

	void UnInit()
	{
		for (int i = 0; i < m_channelVec.size(); ++i)
		{
			delete m_channelVec[i];
		}
	}

// 	Vector3 Convert(aiVector3D tmp)
// 	{
// 		return Vector3(tmp.x, tmp.y, tmp.z);
// 	}
// 
// 	Quaternion Convert(aiQuaternion tmp)
// 	{
// 		return Quaternion(tmp.x, tmp.y, tmp.z, tmp.w);
// 	}

	void Update(float delta)
	{
		Init();

		m_curTime += delta;

		//float oneFrameSpan = 1 / m_framePerSecond;
		// 这里先不考虑性能了。。
		for (int i = 0; i < m_fullTransformVec.size(); ++i)
		{
			if (m_fullTransformVec[i]->m_name == "Bip001")
			{
				int test = 0;
			}

			{
				VectorKey beginPosKey;
				VectorKey endPosKey;
				GetPosKey(m_curTime, m_channelVec[i], beginPosKey, endPosKey);
				float weight = (m_curTime - beginPosKey.mTime) / (endPosKey.mTime - beginPosKey.mTime);
				Vector3 beginLocalPos = beginPosKey.mValue;
				Vector3 endLocalPos = endPosKey.mValue;
				Vector3 curLocalPos = Vector3::Lerp(beginLocalPos, endLocalPos, weight);

				m_fullTransformVec[i]->SetLocalPosition(curLocalPos);
			}


			{
				QuatKey beginQuaKey;
				QuatKey endQuaKey;
				GetQuaKey(m_curTime, m_channelVec[i], beginQuaKey, endQuaKey);
				float weight = (m_curTime - beginQuaKey.mTime) / (endQuaKey.mTime - beginQuaKey.mTime);
				Quaternion beginLocalQua = beginQuaKey.mValue;
				Quaternion endLocalQua =endQuaKey.mValue;
				Quaternion curQua = Quaternion::Slerp(beginLocalQua, endLocalQua, weight);

				m_fullTransformVec[i]->SetLocalRotation(curQua);
			}
		}
	}

	void GetPosKey(float & time, ChannelFrameData * channelData, VectorKey & beginKey, VectorKey & endKey)
	{
		if (channelData->m_posKeyVec.size() == 1)
		{
			beginKey = channelData->m_posKeyVec[0];
			endKey = channelData->m_posKeyVec[0];
			return;
		}
		if (time >= channelData->m_posKeyVec[channelData->m_posKeyVec.size() - 1].mTime)
		{
			//beginKey = channelData->m_posKeyVec[channelData->m_posKeyVec.size() - 2];
			//endKey = channelData->m_posKeyVec[channelData->m_posKeyVec.size() - 1];
			//return;
			time -= channelData->m_posKeyVec[channelData->m_posKeyVec.size() - 1].mTime;
		}
		if (time == 0)
		{
			beginKey = channelData->m_posKeyVec[0];
			endKey = channelData->m_posKeyVec[1];
			return;
		}

		for (int i = 0; i < channelData->m_posKeyVec.size(); ++i)
		{
			if (time < channelData->m_posKeyVec[i].mTime)
			{
				beginKey = channelData->m_posKeyVec[i - 1];
				endKey = channelData->m_posKeyVec[i];
				return;
			}
		}
	}

	void GetQuaKey(float & time, ChannelFrameData * channelData, QuatKey & beginKey, QuatKey & endKey)
	{
		if (channelData->m_quaKeyVec.size() == 1)
		{
			beginKey = channelData->m_quaKeyVec[0];
			endKey = channelData->m_quaKeyVec[0];
			return;
		}
		if (time >= channelData->m_quaKeyVec[channelData->m_quaKeyVec.size() - 1].mTime)
		{
			//beginKey = channelData->m_quaKeyVec[channelData->m_quaKeyVec.size() - 2];
			//endKey = channelData->m_quaKeyVec[channelData->m_quaKeyVec.size() - 1];
			//return;
			time -= channelData->m_quaKeyVec[channelData->m_quaKeyVec.size() - 1].mTime;
		}
		if (time == 0)
		{
			beginKey = channelData->m_quaKeyVec[0];
			endKey = channelData->m_quaKeyVec[1];
			return;
		}

		for (int i = 0; i < channelData->m_quaKeyVec.size(); ++i)
		{
			if (time < channelData->m_quaKeyVec[i].mTime)
			{
				beginKey = channelData->m_quaKeyVec[i - 1];
				endKey = channelData->m_quaKeyVec[i];
				return;
			}
		}
	}
};