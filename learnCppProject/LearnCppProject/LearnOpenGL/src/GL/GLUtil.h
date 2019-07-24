#pragma once

#include "../Learn3D/Matrix4x4.h"

struct GLUtil 
{
	static Matrix4x4 worldToCameraMatrix(Matrix4x4 cameraLocalToWorld);
};


