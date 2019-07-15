#include "pch.h"

#include "Test.h"

#include "./IOTest.h"
#include "./LimitTest.h"
#include "./TestArray.h"
#include "./TestString.h"
#include "./TestStructAndClass.h"
//#include "./TestEnum.h"
#include "./TestPointer.h"
#include "./TestNew.h"
#include "./TestTime.h"
#include "./TestFor.h"
#include "./TestFunction.h"
#include "./TestTemplate.h"
#include "./TestException.h"
#include "./TestRTTI.h"
#include "./TestSmartPointer.h"
#include "./TestSTLContainer.h"
#include "./TestFunctor.h"

typedef int gaga;

enum spectrum { red, orange, yellow, green, blue, violet, indigo, ultraviolet };
enum bits { one = 1, two = 2, four = 4, eight = 8 };

extern int blem;
//extern int blem2;
// 带和不带extern的效果貌似是一致的
void TestExternFunc();
extern void TestExternFunc();
//void TestStaticFunc();
extern "C" void spiff(int); // 跨语言调用

namespace wth
{

}

void Test()
{
	TestStdOutput();

	TestLimits();

	TestArray();

	//std::cin.get();
	TestString();

	TestStructAndClass();

	TestPointer();

	TestNewAndDelete();

	TestTime();

	TestFor();

	TestTextFileOutput();

	TestTextFileInput();

	TestBinaryFileInput();

	TestFunction();

	int rats;
	// 别名
	int & rodents = rats; // makes rodents an alias for rats 

	TestTemplate();

	blem = 1;
	//blem2 = 2;

	TestExternFunc();
	//TestStaticFunc();

	//spiff(1);

	TestException();

	TestRTTI();

	TestSmartPointer();

	TestSTLContainer();

	TestFunctor();
}