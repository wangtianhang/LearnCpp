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

// mrt demo
class Demo10 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;
	GLuint m_rendering_program = 0;
	//GLuint m_vertex_array_object = 0;

	GLuint m_buffer[3] = { 0, 0, 0 };
	GLuint m_vao = 0;

	GLuint m_texture = 0;
	GLuint m_index_buffer = 0;
	//GLuint m_texture2;

	//GLuint m_texture3;
	GLuint          m_fbo = 0;
	//GLuint          m_color_texture;
	GLuint          m_color_texture[3] = { 0, 0, 0 };
	GLuint          m_depth_texture = 0;
	int m_fboSize = 512;

	virtual void startup()
	{
		application::startup();

		std::string vertex_shader_source = LoadTextFile("./Assets/shader/Demo7Vertex.txt");
		std::string fragment_shader_source = LoadTextFile("./Assets/shader/Demo10Pixel.txt");

		GLuint vertex = CreateShaderFromString(vertex_shader_source.c_str(), GL_VERTEX_SHADER, true);
		GLuint pixel = CreateShaderFromString(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER, true);
		m_rendering_program = CreateShaderProgram(vertex, pixel, true, true);

		TestBufferWithVAO();

		TestLoadTexture();

		InitFbo();
	}

	void TestLoadTexture()
	{
		m_texture = PNGHelper::LoadPngAsGLTexture("./Assets/texture/story_aiji_LG_cn.png");
	}

	void TestBufferWithVAO()
	{
		static const GLfloat vertex_positions[] = {
			1, -1, 0.5,
		-1, -1, 0.5,
		1, 1, 0.5,
		-1, 1, 0.5
		};
		static const GLfloat colors[] = {
		1,0,0,
		0,1,0,
		0,0,1,
		1,0,0 };

		static const GLfloat uvs[] = {
			1,0,
			0,0,
			1,1,
			0,1
		};

		static const GLushort vertex_indices[] =
		{
			0,1,2,
			1,3,2
		};

		// Create the vertex array object
		glCreateVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		// Get create two buffers
		glCreateBuffers(3, &m_buffer[0]);
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer[0]);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(vertex_positions),
			vertex_positions,
			GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, m_buffer[1]);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(colors),
			colors,
			GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, m_buffer[2]);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(uvs),
			uvs,
			GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(2);


		glGenBuffers(1, &m_index_buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_index_buffer);
		int tmp2 = sizeof(vertex_indices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			tmp2,
			vertex_indices,
			GL_STATIC_DRAW);

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

		OpenFbo();

		GLboolean isBlendEnable = false;
		glGetBooleanv(GL_BLEND, &isBlendEnable);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint unit = 0;
		glUseProgram(m_rendering_program);

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		int location = glGetUniformLocation(m_rendering_program, "texture1");
		glUniform1i(location, unit);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
		
		if (!isBlendEnable)
		{
			glDisable(GL_BLEND);
		}
		//GLUtil::DrawFullTexture(m_texture);

		CloseFbo();

		GLUtil::DrawFullTexture(m_color_texture[2]);
	}

	void InitFbo()
	{
		//int size = 512;
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		static const GLenum draw_buffers[] =
		{
		GL_COLOR_ATTACHMENT0,
		GL_COLOR_ATTACHMENT1,
		GL_COLOR_ATTACHMENT2
		};

		glGenTextures(3, &m_color_texture[0]);

// 		glGenTextures(1, &m_color_texture);
// 		glBindTexture(GL_TEXTURE_2D, m_color_texture);
// 		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_fboSize, m_fboSize);
// 
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color_texture, 0);
		// For each one...
		for (int i = 0; i < 3; i++)
		{
			// Bind and allocate storage for it
			glBindTexture(GL_TEXTURE_2D, m_color_texture[i]);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_fboSize, m_fboSize);
			// Set its default filter parameters
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// Attach it to our framebuffer object as color attachments
			glFramebufferTexture(GL_FRAMEBUFFER, draw_buffers[i], m_color_texture[i], 0);
		}

		glGenTextures(1, &m_depth_texture);
		glBindTexture(GL_TEXTURE_2D, m_depth_texture);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, m_fboSize, m_fboSize);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depth_texture, 0);

		//static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(3, draw_buffers);
	}

	void OpenFbo()
	{
		// ����viewPort
		// bind fbo
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glViewport(0, 0, m_fboSize, m_fboSize);
		static const GLfloat white[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, white);
		glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);
	}

	void CloseFbo()
	{
		// �ָ�viewPort
		// unbind fbo
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, application::app->info.windowWidth, application::app->info.windowHeight);
	}

	virtual void shutdown()
	{
		application::shutdown();

		glDeleteProgram(m_rendering_program);
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(3, m_buffer);
		glDeleteTextures(1, &m_texture);
		glDeleteBuffers(1, &m_index_buffer);
		glDeleteFramebuffers(1, &m_fbo);
		glDeleteTextures(3, m_color_texture);
		glDeleteTextures(1, &m_depth_texture);
	}

	virtual void onKey(int key, int action)
	{
		std::string keyStr = std::to_string(key);
		std::string actionStr = std::to_string(action);
		GUtil::Log("onKey key " + keyStr + " action " + actionStr);
		if (key == GLFW_KEY_S && action == 1)
		{
			//GLUtil::SaveScreen("screenShot");
			//GUtil::Log("save screen shot");
		}
	}
};