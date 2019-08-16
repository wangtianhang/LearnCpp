#pragma once

#include <vector>

#include "./Learn3D/Transform.h"

struct BoneAnimation
{
public:
	int m_framePerSecond = 30;
	std::vector<std::vector<Transform>> m_frameVec;
};