#pragma once

#include "../Learn3D/Matrix4x4.h"
#include "../LearnOpenGL/ApplicationBase.h"
#include "../LearnOpenGL/ShaderHelper.h"
#include "../IO/FileIO.h"

struct GLUtil 
{
	static bool m_hasInit;
	static GLuint m_drawTexture_program;
	static GLuint m_vao;
	static GLuint m_index_buffer;
	static GLuint m_buffer[3];

	static void Init()
	{
		if (m_hasInit)
		{
			return;
		}
		m_hasInit = true;

		InitDrawTextureData();
	}

	static void InitDrawTextureData()
	{
		std::string vertex_shader_source = LoadTextFile("./Assets/shader/Demo7Vertex.txt");
		std::string fragment_shader_source = LoadTextFile("./Assets/shader/Demo7Pixel.txt");
		GLuint vertex = CreateShaderFromString(vertex_shader_source.c_str(), GL_VERTEX_SHADER, true);
		GLuint pixel = CreateShaderFromString(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER, true);
		m_drawTexture_program = CreateShaderProgram(vertex, pixel, true, true);

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

	static Matrix4x4 worldToCameraMatrix(Matrix4x4 cameraLocalToWorld);

	static Matrix4x4 GenViewMatrix(Vector3 cameraPos, Vector3 cameraEuler);

	static Matrix4x4 GenMVP(Vector3 modelPos, Vector3 modelEuler, Vector3 modelScale, 
		Vector3 cameraPos, Vector3 cameraEuler, float fov, float aspect, float nearZ, float farZ);

	static void SetMVP(int shaderProgramId, int mvpLocation, Matrix4x4 mvp);

	// »­Ïß¿ò
	static void SetDrawOutLine()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	// ÏòÆÁÄ»»­ÎÆÀí
// 	static void DrawTextureToScreen(GLuint texture)
// 	{
// 		Init();
// 
// 		//glViewport(0, 0, application::app->info.windowWidth, application::app->info.windowHeight);
// 		glViewport(0, 0, application::app->info.windowWidth, application::app->info.windowHeight);
// 
// 		DrawFullTexture(texture);
// 	}

	static void DrawFullTexture(GLuint texture)
	{
		Init();

		GLboolean isBlendEnable = false;
		glGetBooleanv(GL_BLEND, &isBlendEnable);
		glEnable(GL_BLEND);
		//glGetBooleanv(GL_BLEND, &isBlendEnable);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLuint unit = 0;
		glUseProgram(m_drawTexture_program);

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, texture);
		int location = glGetUniformLocation(m_drawTexture_program, "texture1");
		glUniform1i(location, unit);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);



		if (!isBlendEnable)
		{
			glDisable(GL_BLEND);
		}
	}

	static void SaveScreen(std::string fileName)
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
};


