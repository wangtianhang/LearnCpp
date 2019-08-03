#pragma once

#include <string>

#include <gl3w.h>

#pragma warning(disable:4996) // 等价于#define _CRT_SECURE_NO_WARNINGS 1 后面这个宏定义感觉不太好用

GLuint CreateShaderFromFile(const char * filename,
	GLenum shader_type,
	bool check_errors);

GLuint CreateShaderFromString(const char * source,
	GLenum shader_type,
	bool check_errors, std::string shaderPath = "");

GLuint CreateShaderProgram(GLuint vertex, GLuint pixel, bool delete_shader, bool check_errors);