#pragma once

#include "./MeshFliter.h"
#include "./Material.h"

class ResourcesMgr
{
public:
	void AddMeshFilterRef(MeshFliter * mesh)
	{

	}

	void ReleaseMeshFilter(MeshFliter * mesh)
	{
		// todo 共享计数器来判定是否释放资源
	}

	void AddMaterialRef(Material * mat)
	{

	}

	void ReleaseMaterial(Material * mat)
	{

	}
};

