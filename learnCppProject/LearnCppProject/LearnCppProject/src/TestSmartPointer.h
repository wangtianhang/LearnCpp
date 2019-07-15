#pragma once

#include <iostream>
#include <memory.h>

//auto_ptr这是C++98标准下的智能指针，现在常常已经被C++标准的其他智能指针取代。它的缺点是在转移所有权后会使运行期不安全。C++11新标准，用unique_ptr来代替auto_ptr原有功能，其用法介绍见第四部分unique_ptr。
void TestAutoPtr()
{
	std::auto_ptr<std::string> country[5] =
	{
		std::auto_ptr<std::string>(new std::string("USA")),
		std::auto_ptr<std::string>(new std::string("CHN")),
		std::auto_ptr<std::string>(new std::string("RUS")),
		std::auto_ptr<std::string>(new std::string("FRA")),
		std::auto_ptr<std::string>(new std::string("GRB"))
	};

	std::auto_ptr<std::string> pwin;
	pwin = country[2]; //将所有权从country[2]转让给pwin，此时country[2]不再引用该字符串从而变成空指针，在运行到循环时就会崩溃

	for (int i = 0; i < 5; ++i)
		std::cout << *country[i] << std::endl;//运行到[2]时崩溃，因为country[2]为空
	std::cout << "The best is " << *pwin << std::endl;
}

void TestSmartPointer()
{
	//TestAutoPtr();
}