#include "pch.h"

int blem; // 没有static前缀为全局变量
static int blem2; // 加了static前缀的变量被限制在文件内部访问

void TestExternFunc()
{

}

// static 可以限制函数只在文件内访问
static void TestStaticFunc()
{

}