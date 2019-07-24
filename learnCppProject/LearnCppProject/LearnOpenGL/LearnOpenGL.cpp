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
#include "./src/Demo/Demo1.h"
#include "./src/Demo/Demo2.h"
#include "./src/Demo/Demo3.h"
#include "./src/Demo/Demo4.h"
#include "./src/Demo//Demo5.h"
#include "./src/Learn3D/Matrix4x4.h"

// Derive my_application from sb7::application

// Our one and only instance of DECLARE_MAIN
//DECLARE_MAIN(my_application);

//my_application *app = 0;
int CALLBACK WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)                  
{
	Matrix4x4::Test();

	int demoId = 1;
	if (demoId == 1)
	{
		Demo5 *app = new Demo5;
		app->run(app);
		delete app;
	}                              
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
