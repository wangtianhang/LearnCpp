#pragma once

#include <string>

#include "../LearnOpengl/ApplicationBase.h"
#include "../IO/FileIO.h"
#include "../Learn3D/Mathf.h"
#include "../Learn3D/Vector4.h"
#include "../Learn3D/Vector3.h"
#include "../Learn3D/Matrix4x4.h"
#include "../GL/GLUtil.h"
#include "../Graphic/PNGHelper.h"
#include "../GUtil/GUtil.h"
#include "../../include/sb7ktx.h"

// png纹理 demo
class Demo7 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;
	GLuint m_rendering_program = 0;
	//GLuint m_vertex_array_object = 0;

	GLuint m_buffer[3];
	GLuint m_vao;

	GLuint m_texture;

	GLuint m_texture2;

	//GLuint m_texture3;

	virtual void startup()
	{
		application::startup();

		std::string vertex_shader_source = LoadTextFile("./Assets/shader/Demo7Vertex.txt");
		std::string fragment_shader_source = LoadTextFile("./Assets/shader/Demo7Pixel.txt");

		GLuint vertex = CreateShaderFromString(vertex_shader_source.c_str(), GL_VERTEX_SHADER, true);
		GLuint pixel = CreateShaderFromString(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER, true);
		m_rendering_program = CreateShaderProgram(vertex, pixel, true, true);
		//glCreateVertexArrays(1, &m_vertex_array_object);
		//glBindVertexArray(m_vertex_array_object);

		TestBufferWithVAO();

		TestLoadTexture();
	}

	void TestLoadTexture()
	{
//		int width = 0;
//		int height = 0;
//		bool isAlpha = false;
//		GLubyte * data = PNGHelper::ReadPngFile("./Assets/texture/story_aiji_LG_cn.png", width, height, isAlpha);
		//GLubyte * data = PNGHelper::ReadPngFile("./Assets/texture/battleFont.png", width, height, isAlpha);
// 		int width, height;
// 		bool hasAlpha;
// 		char filename[] = "./Assets/texture/story_aiji_LG_cn.png";
// 		GLubyte *data;
// 		PNGHelper::loadPngImage(filename, width, height, hasAlpha, &data);
// 		GLubyte * data = (GLubyte*)malloc(width * height * 4);
//  		for (int i = 0; i < width; ++i)
//  		{
//  			for (int j = 0; j < height; ++j)
//  			{
//  				int index = (i * 124 + j) * 4;
//  				data[index] = 255;
// 				data[index + 1] = 0;
// 				data[index + 2] = 0;
// 				data[index + 3] = 128;
//  			}
//  		}

// 		if (data == NULL)
// 		{
// 			return;
// 		}
// 		GUtil::Log("加载纹理成功");
// 		int size = isAlpha ? 4 : 3;
// 		int length = width * height * size;
// 		glGenTextures(1, &m_texture);
// 		glBindTexture(GL_TEXTURE_2D, m_texture);
		// Specify the amount of storage we want to use for the texture
// 		glTextureStorage2D(m_texture, // Texture object
// 			1, // 1 mipmap level
// 			GL_RGBA8UI, // 32-bit floating-point RGBA data
// 			width, height); // 256 x 256 texels
// 		// Assume that "texture" is a 2D texture that we created earlier
// 		glTextureSubImage2D(m_texture, // Texture object
// 			0, // Level 0
// 			0, 0, // Offset 0, 0
// 			width, height, // 256 x 256 texels, replace entire image
// 			GL_RGBA_INTEGER, // Four-channel data
// 			GL_UNSIGNED_BYTE, // 每个分量的结构
// 			data); // Pointer to data
		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		//glTexImage2D(GL_TEXTURE_2D, 0, isAlpha ? GL_RGBA : GL_RGB, width, height, 0, isAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glEnable(GL_TEXTURE_2D);
		//glBindTexture(GL_TEXTURE_2D, m_texture);
		//free(data);

		m_texture = PNGHelper::LoadPngAsGLTexture("./Assets/texture/story_aiji_LG_cn.png");

		m_texture2 = sb7::ktx::file::load("./Assets/texture/tree.ktx");

		//m_texture3 = PNGHelper::ReadPngFile2("./Assets/texture/story_aiji_LG_cn.png", width, height);
	}

	void TestBufferWithVAO()
	{
// 		static const GLfloat vertex_positions[] =
// 		{
// 			-0.25f,  0.25f, -0.25f,
// 			-0.25f, -0.25f, -0.25f,
// 			 0.25f, -0.25f, -0.25f,
// 
// 			 0.25f, -0.25f, -0.25f,
// 			 0.25f,  0.25f, -0.25f,
// 			-0.25f,  0.25f, -0.25f,
// 
// 			 0.25f, -0.25f, -0.25f,
// 			 0.25f, -0.25f,  0.25f,
// 			 0.25f,  0.25f, -0.25f,
// 
// 			 0.25f, -0.25f,  0.25f,
// 			 0.25f,  0.25f,  0.25f,
// 			 0.25f,  0.25f, -0.25f,
// 
// 			 0.25f, -0.25f,  0.25f,
// 			-0.25f, -0.25f,  0.25f,
// 			 0.25f,  0.25f,  0.25f,
// 
// 			-0.25f, -0.25f,  0.25f,
// 			-0.25f,  0.25f,  0.25f,
// 			 0.25f,  0.25f,  0.25f,
// 
// 			-0.25f, -0.25f,  0.25f,
// 			-0.25f, -0.25f, -0.25f,
// 			-0.25f,  0.25f,  0.25f,
// 
// 			-0.25f, -0.25f, -0.25f,
// 			-0.25f,  0.25f, -0.25f,
// 			-0.25f,  0.25f,  0.25f,
// 
// 			-0.25f, -0.25f,  0.25f,
// 			 0.25f, -0.25f,  0.25f,
// 			 0.25f, -0.25f, -0.25f,
// 
// 			 0.25f, -0.25f, -0.25f,
// 			-0.25f, -0.25f, -0.25f,
// 			-0.25f, -0.25f,  0.25f,
// 
// 			-0.25f,  0.25f, -0.25f,
// 			 0.25f,  0.25f, -0.25f,
// 			 0.25f,  0.25f,  0.25f,
// 
// 			 0.25f,  0.25f,  0.25f,
// 			-0.25f,  0.25f,  0.25f,
// 			-0.25f,  0.25f, -0.25f
// 		};
// 
// 		// Create the vertex array object
// 		glCreateVertexArrays(1, &m_vao);
// 		// Get create two buffers
// 		glCreateBuffers(1, &m_buffer);
// 		// Initialize the first buffer
// 		glNamedBufferStorage(m_buffer, sizeof(vertex_positions), vertex_positions, 0);
// 		// Bind it to the vertex array - offset zero, stride = sizeof(vec3)
// 		int tmp = sizeof(Vector3);
// 		// tmp == 12 ....
// 		glVertexArrayVertexBuffer(m_vao, 0, m_buffer, 0, sizeof(Vector3));
// 		// Tell OpenGL what the format of the attribute is
// 		glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
// 		// Tell OpenGL which vertex buffer binding to use for this attribute
// 		glVertexArrayAttribBinding(m_vao, 0, 0);
// 		// Enable the attribute
// 		glEnableVertexArrayAttrib(m_vao, 0);

		static const GLfloat positions[] = { 0.5, -0.5, 0.5,
		-0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,
		-0.5, -0.5, 0.5,
		-0.5, 0.5, 0.5,
		0.5, 0.5, 0.5
		};
		static const GLfloat colors[] = { 1,0,0,
		0,1,0,
		0,0,1,
		0,1,0,
		1,0,0,
		0,0,1};

		static const GLfloat uvs[] = {
			1,0,
			0,0,
			1,1,
			0,0,
			0,1,
			1,1
		};

		// Create the vertex array object
		glCreateVertexArrays(1, &m_vao);
		// Get create two buffers
		glCreateBuffers(3, &m_buffer[0]);
		// Initialize the first buffer
		glNamedBufferStorage(m_buffer[0], sizeof(positions), positions, 0);
		// Bind it to the vertex array - offset zero, stride = sizeof(vec3)
		int tmp = sizeof(Vector3);
		// tmp == 12 ....
		glVertexArrayVertexBuffer(m_vao, 0, m_buffer[0], 0, sizeof(Vector3));
		// Tell OpenGL what the format of the attribute is
		glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		// Tell OpenGL which vertex buffer binding to use for this attribute
		glVertexArrayAttribBinding(m_vao, 0, 0);
		// Enable the attribute
		glEnableVertexArrayAttrib(m_vao, 0);
		// Perform similar initialization for the second buffer
		glNamedBufferStorage(m_buffer[1], sizeof(colors), colors, 0);
		glVertexArrayVertexBuffer(m_vao, 1, m_buffer[1], 0, sizeof(Vector3));
		glVertexArrayAttribFormat(m_vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_vao, 1, 1);
		glEnableVertexArrayAttrib(m_vao, 1);

		glNamedBufferStorage(m_buffer[2], sizeof(uvs), uvs, 0);
		int sizeofvector2 = 8;
		glVertexArrayVertexBuffer(m_vao, 2, m_buffer[2], 0, sizeofvector2);
		glVertexArrayAttribFormat(m_vao, 2, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_vao, 2, 2);
		glEnableVertexArrayAttrib(m_vao, 2);
	}

	virtual void render(double currentTime)
	{
		float delta = currentTime - m_accTime;
		m_accTime = currentTime;

		RenderUpdate(delta);
	}



	void RenderUpdate(float delta)
	{
		// Simply clear the window with red
		static const GLfloat white[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, white);

// 		Vector3 euler = Vector3(m_accTime * 10, 0, 0);
// 		Matrix4x4 model_localToWorld = Matrix4x4::TRS(Vector3(-1, 0, 0), Quaternion::Euler(euler), Vector3::one() * 2);
// 		Vector3 cameraPos = Vector3(0, 0, -10);
// 		Vector3 cameraEuler = Vector3::zero();
// 		Matrix4x4 cameraLocalToWorld = Matrix4x4::TRS(cameraPos, Quaternion::Euler(cameraEuler), Vector3::one());
// 		// camera worldToLocal
// 		Matrix4x4 view = GLUtil::worldToCameraMatrix(cameraLocalToWorld);
// 		float aspect = (float)info.windowWidth / info.windowHeight;
// 		float fov = 60;
// 		float nearPlane = 0.3;
// 		float farPlane = 1000;
// 		Matrix4x4 project = Matrix4x4::Perspective(fov, aspect, nearPlane, farPlane);
// 		Matrix4x4 mvp = project * view * model_localToWorld;
// 		glUseProgram(m_rendering_program);
// 		GLuint mvpLocation = glGetUniformLocation(m_rendering_program, "mvp_matrix");
// 		float mvpMatrixArray[16];
// 		mvp.GetMatrixArray(mvpMatrixArray);
// 		glUniformMatrix4fv(mvpLocation, 1, true, mvpMatrixArray);
// 
// 		glEnable(GL_CULL_FACE);
// 		glCullFace(GL_BACK);
// 
// 		// 这种先bind再draw很蛋疼。。
// 		glBindVertexArray(m_vao);
// 		glDrawArrays(GL_TRIANGLES, 0, 36);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint unit = 0;
		glUseProgram(m_rendering_program);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		int location = glGetUniformLocation(m_rendering_program, "texture1");
		glUniform1i(location, 0);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	virtual void shutdown()
	{
		application::shutdown();

		glDeleteProgram(m_rendering_program);
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(3, m_buffer);
		glDeleteTextures(1, &m_texture);
		glDeleteTextures(1, &m_texture2);
	}
};