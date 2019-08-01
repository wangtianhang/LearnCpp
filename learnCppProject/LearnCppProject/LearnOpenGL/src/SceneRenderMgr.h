#pragma once

#include <vector>

#include "./MeshRenderObject.h"

class SceneRenderMgr
{
public:
	std::vector<MeshRenderObject *> m_renderGoVec;

	void Update(float delta);
};

