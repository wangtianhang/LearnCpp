#include "pch.h"

#include "Test.h"

#include "./IOTest.h"
#include "./LimitTest.h"
#include "./TestArray.h"
#include "./TestString.h"
#include "./TestStruct.h"
#include "./TestEnum.h"
#include "./TestPointer.h"
#include "./TestNew.h"
#include "./TestTime.h"

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
}