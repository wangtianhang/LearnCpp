#pragma once

#include <vector>

#include "./MeshFliter.h"
#include "./Learn3D/Transform.h"
#include "./BoneAnimation.h"

struct FBXFileHelper
{
public:
	static bool loadObjAsVAO(std::string path, MeshFliter & ret, BoneAnimation & bones);
};