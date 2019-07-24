#pragma once

#include <string>

#include "../LearnOpengl/ApplicationBase.h"
#include "../IO/FileIO.h"
#include "../Learn3D/Mathf.h"
#include "../Learn3D/Vector4.h"
#include "../Learn3D/Vector3.h"

class Demo3 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;
	GLuint m_rendering_program = 0;
	//GLuint m_vertex_array_object = 0;

	GLuint m_buffer[2];
	GLuint m_vao;

	virtual void startup()
	{
		application::startup();

		std::string vertex_shader_source = LoadTextFile("./Assets/shader/Demo3Vertex.txt");
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
		static const GLfloat positions[] = { 0.25, -0.25, 0.5,
		-0.25, -0.25, 0.5,
		0.25, 0.25, 0.5 };
		static const GLfloat colors[] = { 1,0,0,
		0,1,0,
		0,0,1};
		// Create the vertex array object
		glCreateVertexArrays(1, &m_vao);
		// Get create two buffers
		glCreateBuffers(2, &m_buffer[0]);
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
		glClearBufferfv(GL_COLOR, 0, white);

		glUseProgram(m_rendering_program);
		//glPointSize(10);

// 		GLfloat attrib[] = { Mathf::Sin(m_accTime) * 0.5f,
// 						Mathf::Cos(m_accTime) * 0.6f,
// 						0.0f, 0.0f };
// 
// 		GLfloat attrib2[] = { Mathf::Sin(m_accTime) * 0.5f,
// 				Mathf::Cos(m_accTime) * 0.6f,
// 				0.0f, 0.0f };
// 		// Update the value of input attribute 0
// 		glVertexAttrib4fv(0, attrib);
// 		glVertexAttrib4fv(1, attrib2);
// 
		// 这种先bind再draw很蛋疼。。
		glBindVertexArray(m_vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(m_vertex_array_object, )
	}

	virtual void shutdown()
	{
		application::shutdown();

		glDeleteProgram(m_rendering_program);
		glDeleteVertexArrays(1, &m_vao);
	}
};