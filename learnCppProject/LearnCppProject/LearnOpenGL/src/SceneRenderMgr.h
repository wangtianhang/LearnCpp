#pragma once

#include <vector>

#include "./MeshRenderObject.h"

class SceneRenderMgr
{
public:
	std::vector<MeshRenderObject *> m_renderGoVec;

	void Update(float delta);

	void UnInit()
	{
		for (int i = 0; i < m_renderGoVec.size(); i++)
		{
			m_renderGoVec[i]->UnInit();
		}
	}
};

