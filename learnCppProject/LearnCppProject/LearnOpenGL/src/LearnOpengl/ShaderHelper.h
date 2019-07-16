#pragma once

#include <string>

#include <gl3w.h>

GLuint CreateShader(const char * source,
	GLenum shader_type,
	bool check_errors);

GLuint CreateShaderProgram(GLuint vertex, GLuint pixel, bool delete_shader, bool check_errors);