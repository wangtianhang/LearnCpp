#pragma once

#include <string>

#include "../LearnOpengl/ApplicationBase.h"
#include "../IO/FileIO.h"
#include "../Learn3D/Mathf.h"
#include "../Learn3D/Vector4.h"
#include "../Learn3D/Vector3.h"
#include "../Learn3D/Matrix4x4.h"
#include "../GL/GLUtil.h"

// blinnphong demo
class Demo12 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;
	GLuint m_rendering_program = 0;
	//GLuint m_vertex_array_object = 0;

	GLuint m_buffer;
	GLuint m_vao;

	virtual void startup()
	{
		application::startup();

		std::string vertex_shader_source = LoadTextFile("./Assets/shader/Demo6Vertex.txt");
		std::string fragment_shader_source = LoadTextFile("./Assets/shader/Demo1Pixel.txt");

		GLuint vertex = CreateShaderFromString(vertex_shader_source.c_str(), GL_VERTEX_SHADER, true);
		GLuint pixel = CreateShaderFromString(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER, true);
		m_rendering_program = CreateShaderProgram(vertex, pixel, true, true);
		//glCreateVertexArrays(1, &m_vertex_array_object);
		//glBindVertexArray(m_vertex_array_object);

		TestBufferWithVAO();
	}

	void TestBufferWithVAO()
	{
		static const GLfloat vertex_positions[] =
		{
			-0.25f,  0.25f, -0.25f,
			-0.25f, -0.25f, -0.25f,
			 0.25f, -0.25f, -0.25f,

			 0.25f, -0.25f, -0.25f,
			 0.25f,  0.25f, -0.25f,
			-0.25f,  0.25f, -0.25f,

			 0.25f, -0.25f, -0.25f,
			 0.25f, -0.25f,  0.25f,
			 0.25f,  0.25f, -0.25f,

			 0.25f, -0.25f,  0.25f,
			 0.25f,  0.25f,  0.25f,
			 0.25f,  0.25f, -0.25f,

			 0.25f, -0.25f,  0.25f,
			-0.25f, -0.25f,  0.25f,
			 0.25f,  0.25f,  0.25f,

			-0.25f, -0.25f,  0.25f,
			-0.25f,  0.25f,  0.25f,
			 0.25f,  0.25f,  0.25f,

			-0.25f, -0.25f,  0.25f,
			-0.25f, -0.25f, -0.25f,
			-0.25f,  0.25f,  0.25f,

			-0.25f, -0.25f, -0.25f,
			-0.25f,  0.25f, -0.25f,
			-0.25f,  0.25f,  0.25f,

			-0.25f, -0.25f,  0.25f,
			 0.25f, -0.25f,  0.25f,
			 0.25f, -0.25f, -0.25f,

			 0.25f, -0.25f, -0.25f,
			-0.25f, -0.25f, -0.25f,
			-0.25f, -0.25f,  0.25f,

			-0.25f,  0.25f, -0.25f,
			 0.25f,  0.25f, -0.25f,
			 0.25f,  0.25f,  0.25f,

			 0.25f,  0.25f,  0.25f,
			-0.25f,  0.25f,  0.25f,
			-0.25f,  0.25f, -0.25f
		};

		// Create the vertex array object
		glCreateVertexArrays(1, &m_vao);
		// Get create two buffers
		glCreateBuffers(1, &m_buffer);
		// Initialize the first buffer
		glNamedBufferStorage(m_buffer, sizeof(vertex_positions), vertex_positions, 0);
		// Bind it to the vertex array - offset zero, stride = sizeof(vec3)
		int tmp = sizeof(Vector3);
		// tmp == 12 ....
		glVertexArrayVertexBuffer(m_vao, 0, m_buffer, 0, sizeof(Vector3));
		// Tell OpenGL what the format of the attribute is
		glVertexArrayAttribFormat(m_vao, 0, 3, GL_FLOAT, GL_FALSE, 0);
		// Tell OpenGL which vertex buffer binding to use for this attribute
		glVertexArrayAttribBinding(m_vao, 0, 0);
		// Enable the attribute
		glEnableVertexArrayAttrib(m_vao, 0);


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
		static const GLfloat white[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		static const GLfloat ones[] = { 1.0f };
		glClearBufferfv(GL_COLOR, 0, white);
		glClearBufferfv(GL_DEPTH, 0, ones);

		Vector3 euler = Vector3(m_accTime * 10, 0, 0);
		Matrix4x4 model_localToWorld = Matrix4x4::TRS(Vector3(-1, 0, 0), Quaternion::Euler(euler), Vector3::one() * 2);
		Vector3 cameraPos = Vector3(0, 0, -10);
		Vector3 cameraEuler = Vector3::zero();
		Matrix4x4 cameraLocalToWorld = Matrix4x4::TRS(cameraPos, Quaternion::Euler(cameraEuler), Vector3::one());
		// camera worldToLocal
		Matrix4x4 view = GLUtil::worldToCameraMatrix(cameraLocalToWorld);
		float aspect = (float)info.windowWidth / info.windowHeight;
		float fov = 60;
		float nearPlane = 0.3;
		float farPlane = 1000;
		Matrix4x4 project = Matrix4x4::Perspective(fov, aspect, nearPlane, farPlane);
		Matrix4x4 mvp = project * view * model_localToWorld;
		//Matrix4x4 mvp = model_localToWorld * view * project;
		glUseProgram(m_rendering_program);
		GLuint mvpLocation = glGetUniformLocation(m_rendering_program, "mvp_matrix");
		float mvpMatrixArray[16];
		mvp.GetMatrixArray(mvpMatrixArray);
		glUniformMatrix4fv(mvpLocation, 1, true, mvpMatrixArray);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		// 这种先bind再draw很蛋疼。。
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		//glDrawArrays(m_vertex_array_object, )


	}

	virtual void shutdown()
	{
		application::shutdown();

		glDeleteProgram(m_rendering_program);
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_buffer);
	}
};