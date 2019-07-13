#include "pch.h"

#include "Test.h"

#include "./IOTest.h"
#include "./LimitTest.h"
#include "./TestArray.h"
#include "./TestString.h"
#include "./TestStruct.h"
//#include "./TestEnum.h"
#include "./TestPointer.h"
#include "./TestNew.h"
#include "./TestTime.h"
#include "./TestFor.h"
#include "./TestFunction.h"
#include "./TestTemplate.h"

typedef int gaga;

enum spectrum { red, orange, yellow, green, blue, violet, indigo, ultraviolet };
enum bits { one = 1, two = 2, four = 4, eight = 8 };

void Test()
{
	TestStdOutput();

	TestLimits();

	TestArray();

	//std::cin.get();
	TestString();

	TestStruct();

	TestPointer();

	TestNewAndDelete();

	TestTime();

	TestFor();

	TestTextFileOutput();

	TestTextFileInput();

	TestBinaryFileInput();

	TestFunction();

	int rats;
	// ±ðÃû
	int & rodents = rats; // makes rodents an alias for rats 

	TestTemplate();
}