#include "./gl3w.h"

#include "./GLUtil.h"
#include "../LearnOpenGL/ApplicationBase.h"

bool GLUtil::m_hasInit = false;
GLuint GLUtil::m_drawTexture_program = 0;
GLuint GLUtil::m_drawTexVao = 0;
GLuint GLUtil::m_drawTex_index_buffer = 0;
GLuint GLUtil::m_drawTex_buffer[3] = {0, 0, 0};

GLuint GLUtil::m_cubeVao = 0;

GLuint GLUtil::m_cube_Position_buffer = 0;

GLuint GLUtil::m_cube_index_buffer = 0;

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

void GLUtil::SaveScreen(std::string fileName)
{
	
		int row_size = ((application::app->info.windowWidth * 3 + 3) & ~3);
		int data_size = row_size * application::app->info.windowHeight;
		unsigned char * data = new unsigned char[data_size];
#pragma pack (push, 1)
		struct
		{
			unsigned char identsize; // Size of following ID field
			unsigned char cmaptype; // Color map type 0 = none
			unsigned char imagetype; // Image type 2 = rgb
			short cmapstart; // First entry in palette
			short cmapsize; // Number of entries in palette
			unsigned char cmapbpp; // Number of bits per palette entry
			short xorigin; // X origin
			short yorigin; // Y origin
			short width; // Width in pixels
			short height; // Height in pixels
			unsigned char bpp; // Bits per pixel
			unsigned char descriptor; // Descriptor bits
		} tga_header;
#pragma pack (pop)
		glReadPixels(0, 0, // Origin
			application::app->info.windowWidth, application::app->info.windowHeight, // Size
			GL_BGR, GL_UNSIGNED_BYTE, // Format, type
			data); // Data
		memset(&tga_header, 0, sizeof(tga_header));
		tga_header.imagetype = 2;
		tga_header.width = (short)application::app->info.windowWidth;
		tga_header.height = (short)application::app->info.windowHeight;
		tga_header.bpp = 24;
		FILE * f_out = fopen((fileName + ".tga").c_str(), "wb");
		fwrite(&tga_header, sizeof(tga_header), 1, f_out);
		fwrite(data, data_size, 1, f_out);
		fclose(f_out);
		delete[] data;
	
}
