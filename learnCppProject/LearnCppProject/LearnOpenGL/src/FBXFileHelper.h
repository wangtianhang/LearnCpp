#pragma once

#include <vector>

#include "./MeshFliter.h"
#include "./Learn3D/Transform.h"
#include "./BoneAnimation.h"

struct FBXFileHelper
{
public:
	//static bool loadFBXAsModel(std::string path, MeshFliter & ret, BoneAnimation & bones);

	static bool logFbx(std::string path);

	//static bool loadFbxMeshes(std::string path, std::vector<MeshFliter> & ret);
};