#pragma once

#include "./gl3w.h"

struct RenderTexture
{
public:
	GLuint m_fbo = 0;
	GLuint m_colorTex = 0;
	GLuint m_depthTex = 0;
	int m_width = 0;
	int m_height = 0;
};