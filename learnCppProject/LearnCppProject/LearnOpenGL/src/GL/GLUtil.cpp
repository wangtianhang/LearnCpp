#include "./gl3w.h"

#include "./GLUtil.h"

bool GLUtil::m_hasInit = false;
GLuint GLUtil::m_drawTexture_program = 0;
GLuint GLUtil::m_vao = 0;
GLuint GLUtil::m_index_buffer = 0;
GLuint GLUtil::m_buffer[3] = {0, 0, 0};

Matrix4x4 GLUtil::worldToCameraMatrix(Matrix4x4 cameraLocalToWorld)
{
	Matrix4x4 worldToLocal = cameraLocalToWorld.inverse();
	worldToLocal.m20 *= -1;
	worldToLocal.m21 *= -1;
	worldToLocal.m22 *= -1;
	worldToLocal.m23 *= -1;
	return worldToLocal;
}

Matrix4x4 GLUtil::GenViewMatrix(Vector3 cameraPos, Vector3 cameraEuler)
{
	Matrix4x4 cameraLocalToWorld = Matrix4x4::TRS(cameraPos, Quaternion::Euler(cameraEuler), Vector3::one());
	Matrix4x4 view = GLUtil::worldToCameraMatrix(cameraLocalToWorld);
	return view;
}

Matrix4x4 GLUtil::GenMVP(Vector3 modelPos, Vector3 modelEuler, Vector3 modelScale, Vector3 cameraPos, Vector3 cameraEuler, float fov, float aspect, float nearZ, float farZ)
{
	//Vector3 euler = Vector3(m_accTime * 10, 0, 0);
	Matrix4x4 model_localToWorld = Matrix4x4::TRS(modelPos, Quaternion::Euler(modelEuler), modelScale);
	//Vector3 cameraPos = Vector3(0, 0, -10);
	//Vector3 cameraEuler = Vector3::zero();
	//Matrix4x4 cameraLocalToWorld = Matrix4x4::TRS(cameraPos, Quaternion::Euler(cameraEuler), Vector3::one());
	// camera worldToLocal
	//Matrix4x4 view = GLUtil::worldToCameraMatrix(cameraLocalToWorld);
	Matrix4x4 view = GLUtil::GenViewMatrix(cameraPos, cameraEuler);
	//float aspect = (float)info.windowWidth / info.windowHeight;
	//float fov = 60;
	//float nearPlane = 0.3;
	//float farPlane = 1000;
	Matrix4x4 project = Matrix4x4::Perspective(fov, aspect, nearZ, farZ);
	Matrix4x4 mvp = project * view * model_localToWorld;
	return mvp;
}

void GLUtil::SetMVP(int shaderProgramId, int mvpLocation, Matrix4x4 mvp)
{
	glUseProgram(shaderProgramId);
	//GLuint mvpLocation = glGetUniformLocation(m_rendering_program, "mvp_matrix");
	float mvpMatrixArray[16];
	mvp.GetMatrixArray(mvpMatrixArray);
	glUniformMatrix4fv(mvpLocation, 1, true, mvpMatrixArray);
}
