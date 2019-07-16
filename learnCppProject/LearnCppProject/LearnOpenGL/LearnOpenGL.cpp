// LearnOpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

// int main()
// {
//     std::cout << "Hello World!\n"; 
// }

//#define _CRT_SECURE_NO_WARNINGS 1

//#include "sb7.h"
#include "./src/LearnOpengl/ApplicationBase.h"
#include "./src/LearnOpengl/ShaderHelper.h"

// Derive my_application from sb7::application
class my_application : public application
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

 		std::string vertex_shader_source =
 		{
 			"#version 450 core \n"
 			" \n"
 			"void main(void) \n"
 			"{ \n"
 			" gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
 			"} \n"
 		};

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
// Our one and only instance of DECLARE_MAIN
//DECLARE_MAIN(my_application);

my_application *app = 0;
int CALLBACK WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)                  
{                                                   
my_application *app = new my_application;
app->run(app);                                  
delete app;                                     
return 0;                                       
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
