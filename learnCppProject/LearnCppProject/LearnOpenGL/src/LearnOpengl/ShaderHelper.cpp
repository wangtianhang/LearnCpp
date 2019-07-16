#include "ShaderHelper.h"

GLuint CreateShader(const char * source,
	GLenum shader_type,
	bool check_errors)
{
	GLuint sh;

	sh = glCreateShader(shader_type);

	const char * strings[] = { source };
	glShaderSource(sh, 1, strings, nullptr);

	glCompileShader(sh);

	if (check_errors)
	{
		GLint status = 0;
		glGetShaderiv(sh, GL_COMPILE_STATUS, &status);

		if (!status)
		{
			char buffer[4096];
			glGetShaderInfoLog(sh, 4096, NULL, buffer);
#ifdef _WIN32
			OutputDebugStringA(buffer);
			OutputDebugStringA("\n");
#else
			fprintf(stderr, "%s\n", buffer);
#endif
			goto fail_compile_shader;
		}
	}

	return sh;

fail_compile_shader:
	glDeleteShader(sh);

	return 0;
}

GLuint CreateShaderProgram(GLuint vertex, GLuint pixel, bool delete_shaders, bool check_errors)
{
	//int i;

	GLuint program;

	program = glCreateProgram();

// 	for (i = 0; i < shader_count; i++)
// 	{
// 		glAttachShader(program, shaders[i]);
// 	}
	glAttachShader(program, vertex);
	glAttachShader(program, pixel);

	glLinkProgram(program);

	if (check_errors)
	{
		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);

		if (!status)
		{
			char buffer[4096];
			glGetProgramInfoLog(program, 4096, NULL, buffer);
#ifdef _WIN32
			OutputDebugStringA(buffer);
			OutputDebugStringA("\n");
#endif
			glDeleteProgram(program);
			return 0;
		}
	}

	if (delete_shaders)
	{
// 		for (i = 0; i < shader_count; i++)
// 		{
// 			glDeleteShader(shaders[i]);
// 		}
		glDeleteShader(vertex);
		glDeleteShader(pixel);
	}

	return program;
}
