#pragma once

#include <string>

#include "../ApplicationBase.h"
#include "../FileIO.h"
#include "../Learn3D/Mathf.h"
#include "../Learn3D/Vector4.h"
#include "../Learn3D/Vector3.h"
#include "../Learn3D/Matrix4x4.h"
#include "../GLHelper.h"
#include "../PNGHelper.h"
#include "../GUtil.h"
#include "sb7ktx.h"

// drawindex demo
class Demo8 : public application
{
public:
	// Our rendering function

	double m_accTime = 0;
	GLuint m_rendering_program = 0;
	//GLuint m_vertex_array_object = 0;

	GLuint m_buffer[3];
	GLuint m_vao;

	GLuint m_texture;
	GLuint m_index_buffer;
	//GLuint m_texture2;

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
		m_texture = PNGHelper::LoadPngAsGLTexture("./Assets/texture/story_aiji_LG_cn.png");

		//m_texture2 = sb7::ktx::file::load("./Assets/texture/tree.ktx");

	}

	void TestBufferWithVAO()
	{
		static const GLfloat vertex_positions[] = {
			0.5, -0.5, 0.5,
		-0.5, -0.5, 0.5,
		0.5, 0.5, 0.5,
		-0.5, 0.5, 0.5
		};
		static const GLfloat colors[] = { 
		1,0,0,
		0,1,0,
		0,0,1,
		1,0,0};

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


		// Perform similar initialization for the second buffer
//  		glNamedBufferStorage(m_buffer[1], sizeof(colors), colors, 0);
//  		glVertexArrayVertexBuffer(m_vao, 1, m_buffer[1], 0, sizeof(Vector3));
//  		glVertexArrayAttribFormat(m_vao, 1, 3, GL_FLOAT, GL_FALSE, 0);
//  		glVertexArrayAttribBinding(m_vao, 1, 1);
//  		glEnableVertexArrayAttrib(m_vao, 1);
 
//  		glNamedBufferStorage(m_buffer[2], sizeof(uvs), uvs, 0);
//  		int sizeofvector2 = 8;
//  		glVertexArrayVertexBuffer(m_vao, 2, m_buffer[2], 0, sizeofvector2);
//  		glVertexArrayAttribFormat(m_vao, 2, 2, GL_FLOAT, GL_FALSE, 0);
//  		glVertexArrayAttribBinding(m_vao, 2, 2);
//  		glEnableVertexArrayAttrib(m_vao, 2);
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

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint unit = 0;
		glUseProgram(m_rendering_program);

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		int location = glGetUniformLocation(m_rendering_program, "texture1");
		glUniform1i(location, unit);

		//glBindVertexArray(m_vao);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
	}

	virtual void shutdown()
	{
		application::shutdown();

		glDeleteProgram(m_rendering_program);
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(3, m_buffer);
		glDeleteTextures(1, &m_texture);
		glDeleteBuffers(1, &m_index_buffer);
	}
};