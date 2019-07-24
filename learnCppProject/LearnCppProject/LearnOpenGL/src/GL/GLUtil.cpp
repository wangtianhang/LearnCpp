#include "./GLUtil.h"

Matrix4x4 GLUtil::worldToCameraMatrix(Matrix4x4 cameraLocalToWorld)
{
	Matrix4x4 worldToLocal = cameraLocalToWorld.inverse();
	worldToLocal.m20 *= -1;
	worldToLocal.m21 *= -1;
	worldToLocal.m22 *= -1;
	worldToLocal.m23 *= -1;
	return worldToLocal;
}
