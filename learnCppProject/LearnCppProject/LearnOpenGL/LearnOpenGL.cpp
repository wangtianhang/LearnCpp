// LearnOpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


//#include "pch.h"
#include <iostream>

// int main()
// {
//     std::cout << "Hello World!\n"; 
// }

//#define _CRT_SECURE_NO_WARNINGS 1
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
//#include "sb7.h"
#include "./src/DebugMemory.h"

#include "./src/ApplicationBase.h"
#include "./src/ShaderHelper.h"
#include "./src/Learn3D/Matrix4x4.h"
#include "./src/PNGHelper.h"
#include "./src/MeshRenderObject.h"
#include "./src/Learn3D/Transform.h"
#include "./src/SceneRenderMgr.h"
#include "./src/ResourcesMgr.h"
#include "./src/Demo/Demo1.h"
#include "./src/Demo/Demo2.h"
#include "./src/Demo/Demo3.h"
#include "./src/Demo/Demo4.h"
#include "./src/Demo/Demo5.h"
#include "./src/Demo/Demo6.h"
#include "./src/Demo/Demo7.h"
#include "./src/Demo/Demo8.h"
#include "./src/Demo/Demo9.h"
#include "./src/Demo/Demo10.h"
#include "./src/Demo/Demo11.h"
#include "./src/Demo/Demo12.h"
#include "./src/Demo/Demo13.h"
#include "./src/Demo/Demo14.h"
#include "./src/Demo/Demo15.h"
#include "./src/Demo/Demo16.h"
#include "./src/Demo/Demo17.h"
#include "./src/Demo/Demo18.h"
#include "./src/Demo/Demo19.h"
#include "./src/Demo/Demo20.h"
#include "./src/Demo/Demo21.h"
#include "./src/Demo/Demo22.h"
#include "./src/Demo/Demo23.h"



// Derive my_application from sb7::application

// Our one and only instance of DECLARE_MAIN
//DECLARE_MAIN(my_application);

#pragma comment(lib,"glfw3.lib")
#pragma comment(lib,"libpng16d.lib")
//#pragma comment(lib,"zlibd.lib")
#pragma comment(lib,"assimp-vc140-mt.lib")
//#pragma comment(lib,"libfbxsdk.lib")

//my_application *app = 0;
int CALLBACK WinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)                  
{
	//Matrix4x4::Test();

	//Transform::Test();

	//GLUtil::Init();
	//_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	//_CrtSetBreakAlloc(139566);
	//_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	int demoId = 1;
	if (demoId == 1)
	{
		Demo23 *app = new Demo23;
		//Demo7 *app = new Demo7;
		app->run(app);
		delete app;
 	}

	_CrtDumpMemoryLeaks();

	//GLUtil::UnInit();
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
