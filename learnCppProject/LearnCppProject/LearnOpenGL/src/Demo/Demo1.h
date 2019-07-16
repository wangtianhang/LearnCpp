#pragma once

#include <string>

#include "../LearnOpengl/ApplicationBase.h"
#include "../IO/FileIO.h"

class Demo1 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;
	GLuint m_rendering_program = 0;
	GLuint m_vertex_array_object = 0;

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

		std::string vertex_shader_source = LoadTextFile("./Assets/shader/Demo1Vertex.txt");
		std::string fragment_shader_source = LoadTextFile("./Assets/shader/Demo1Pixel.txt");

		GLuint vertex = CreateShaderFromString(vertex_shader_source.c_str(), GL_VERTEX_SHADER, true);
		GLuint pixel = CreateShaderFromString(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER, true);
		m_rendering_program = CreateShaderProgram(vertex, pixel, true, true);
		glCreateVertexArrays(1, &m_vertex_array_object);
		glBindVertexArray(m_vertex_array_object);
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
		glPointSize(10);
		glDrawArrays(GL_POINTS, 0, 1);
	}

	virtual void shutdown()
	{
		application::shutdown();

		glDeleteProgram(m_rendering_program);
		glDeleteVertexArrays(1, &m_vertex_array_object);
	}
};