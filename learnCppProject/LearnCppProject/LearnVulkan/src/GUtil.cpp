#include "./GUtil.h"

void GUtil::Log(std::string log)
{
	//std::cout << log << std::endl;
	log += "\n";
	OutputDebugStringA(log.c_str());
}

void GUtil::Print(std::string log)
{
	OutputDebugStringA(log.c_str());
}