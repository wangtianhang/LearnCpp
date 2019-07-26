#pragma once

#include "../Learn3D/Matrix4x4.h"

struct GLUtil 
{
	static Matrix4x4 worldToCameraMatrix(Matrix4x4 cameraLocalToWorld);

	static Matrix4x4 GenViewMatrix(Vector3 cameraPos, Vector3 cameraEuler);

	static Matrix4x4 GenMVP(Vector3 modelPos, Vector3 modelEuler, Vector3 modelScale, 
		Vector3 cameraPos, Vector3 cameraEuler, float fov, float aspect, float nearZ, float farZ);

	static void SetMVP(int shaderProgramId, int mvpLocation, Matrix4x4 mvp);

	// »­Ïß¿ò
	static void SetDrawOutLine()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
};


