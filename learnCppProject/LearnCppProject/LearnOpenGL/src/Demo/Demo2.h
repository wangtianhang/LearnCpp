#pragma once

#include <string>

#include "../LearnOpengl/ApplicationBase.h"
#include "../IO/FileIO.h"
#include "../Learn3D/Mathf.h"
#include "../Learn3D/Vector4.h"

// 设置顶点属性测试
class Demo2 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;
	GLuint m_rendering_program = 0;
	GLuint m_vertex_array_object = 0;

	GLuint m_buffer = 0;

	virtual void startup()
	{
		application::startup();

		// 		static const GLchar * vertex_shader_source[] =
		// 		{
		// 		"#version 450 core \n"
		// 		" \n"
		// 		"void main(void) \n"
		// 		"{ \n"
		// 		" gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
		// 		"} \n"
		// 		};

		/*
		std::string vertex_shader_source =
		{
			"#version 450 core \n"
			" \n"
			"void main(void) \n"
			"{ \n"
			" gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
			"} \n"
		};
		*/

		/*
		std::string fragment_shader_source =
		{
		"#version 450 core \n"
		" \n"
		"out vec4 color; \n"
		" \n"
		"void main(void) \n"
		"{ \n"
		" color = vec4(0.0, 0.8, 1.0, 1.0); \n"
		"} \n"
		};
		*/

		std::string vertex_shader_source = LoadTextFile("./Assets/shader/Demo2Vertex.txt");
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
		// Create a buffer
		glCreateBuffers(1, &m_buffer);
		// Specify the data store parameters for the buffer
		glNamedBufferStorage(
			m_buffer, // Name of the buffer
			1024 * 1024, // 1 MiB of space
			NULL, // No initial data
			GL_MAP_WRITE_BIT | GL_DYNAMIC_STORAGE_BIT); // Allow map for writing
			// Now bind it to the context using the GL_ARRAY_BUFFER binding point
		glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

		// This is the data that we will place into the buffer object
		static const float data[] =
		{
		0.25, -0.25, 0.5, 1.0,
		-0.25, -0.25, 0.5, 1.0,
		0.25, 0.25, 0.5, 1.0
		};
		glNamedBufferSubData(m_buffer, 0, sizeof(data), data);

		glCreateVertexArrays(1, &m_vertex_array_object);
		//glBindVertexArray(m_vertex_array_object);
		// First, bind a vertex buffer to the VAO
		glVertexArrayVertexBuffer(m_vertex_array_object, // Vertex array object
			0, // First vertex buffer binding
			m_buffer, // Buffer object
			0, // Start from the beginning
			sizeof(Vector4)); // Each vertex is one vec4
			// Now, describe the data to OpenGL, tell it where it is, and turn on automatic
			// vertex fetching for the specified attribute
		glVertexArrayAttribFormat(m_vertex_array_object, // Vertex array object
				0, // First attribute
				4, // Four components
				GL_FLOAT, // Floating-point data
				GL_FALSE, // Normalized - ignored for floats
					0); // First element of the vertex
		glEnableVertexArrayAttrib(m_vertex_array_object, 0);
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
		static const GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		glClearBufferfv(GL_COLOR, 0, red);

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
		glBindVertexArray(m_vertex_array_object);
 		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawArrays(m_vertex_array_object, )
	}

	virtual void shutdown()
	{
		application::shutdown();

		glDeleteProgram(m_rendering_program);
		glDeleteVertexArrays(1, &m_vertex_array_object);
	}
};