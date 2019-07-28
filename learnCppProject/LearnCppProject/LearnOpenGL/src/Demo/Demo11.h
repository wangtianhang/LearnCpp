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

// time query demo
class Demo11 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;
	//GLuint m_rendering_program = 0;
	//GLuint m_vertex_array_object = 0;

	//GLuint m_buffer[3];
	//GLuint m_vao;

	GLuint m_texture;
	//GLuint m_index_buffer;
	//GLuint m_texture2;

	//GLuint m_texture3;
	GLuint          m_fbo;
	GLuint          m_color_texture;
	GLuint          m_depth_texture;
	int m_fboSize = 512;

	GLuint m_timeQuery = 0;

	virtual void startup()
	{
		application::startup();

		TestLoadTexture();

		InitFbo();
	}

	void TestLoadTexture()
	{
		m_texture = PNGHelper::LoadPngAsGLTexture("./Assets/texture/story_aiji_LG_cn.png");
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

		glGenQueries(1, &m_timeQuery);
		glBeginQuery(GL_TIME_ELAPSED, m_timeQuery);

		OpenFbo();

		GLUtil::DrawFullTexture(m_texture);

		CloseFbo();

		glEndQuery(GL_TIME_ELAPSED);

		GLint stopTimerAvailable = 0;
		while (!stopTimerAvailable) {
			glGetQueryObjectiv(m_timeQuery, GL_QUERY_RESULT_AVAILABLE, &stopTimerAvailable);
		}
		// 返回的结果为纳秒
		GLuint spanTimeNanoSecond = 0;
		glGetQueryObjectuiv(m_timeQuery, GL_QUERY_RESULT, &spanTimeNanoSecond);
		GUtil::Log("耗时 " + std::to_string((double)spanTimeNanoSecond / 1000 / 1000) + " ms");

		GLUtil::DrawFullTexture(m_color_texture);
	}

	void InitFbo()
	{
		//int size = 512;
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glGenTextures(1, &m_color_texture);
		glBindTexture(GL_TEXTURE_2D, m_color_texture);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_fboSize, m_fboSize);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenTextures(1, &m_depth_texture);
		glBindTexture(GL_TEXTURE_2D, m_depth_texture);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT32F, m_fboSize, m_fboSize);

		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_color_texture, 0);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depth_texture, 0);

		static const GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
		glDrawBuffers(1, draw_buffers);
	}

	void OpenFbo()
	{
		// 设置viewPort
		// bind fbo
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		glViewport(0, 0, m_fboSize, m_fboSize);
		static const GLfloat white[] = { 0.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, white);
		glClearBufferfi(GL_DEPTH_STENCIL, 0, 1.0f, 0);
	}

	void CloseFbo()
	{
		// 恢复viewPort
		// unbind fbo
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, application::app->info.windowWidth, application::app->info.windowHeight);
	}

	virtual void shutdown()
	{
		application::shutdown();

		//glDeleteProgram(m_rendering_program);
		//glDeleteVertexArrays(1, &m_vao);
		//glDeleteBuffers(3, m_buffer);
		glDeleteTextures(1, &m_texture);
		//glDeleteBuffers(1, &m_index_buffer);
	}


};