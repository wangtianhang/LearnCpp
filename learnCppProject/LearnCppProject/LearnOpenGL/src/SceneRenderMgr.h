#pragma once

#include <vector>

#include "./MeshRenderObject.h"

class SceneRenderMgr
{
public:

	std::vector<MeshRenderObject> m_renderGoVec;

	void Update(float delta)
	{
		// step1 draw shadow depth

		// step2 draw opaque render go with shadow

		// step3 draw skybox
	}
};

