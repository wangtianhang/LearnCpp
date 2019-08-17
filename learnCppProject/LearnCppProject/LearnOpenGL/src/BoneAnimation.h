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
	double m_framePerSecond = 30;
	/*std::vector<std::vector<Transform>> m_frameVec;*/
	float m_curTime = 0;
	std::vector<std::string> m_boneNameVec;
	std::vector<aiNodeAnim *> m_aiNodeAnimVec;

	void Update(float delta)
	{

	}
};