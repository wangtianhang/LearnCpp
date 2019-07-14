#pragma once
#include <iostream>
#include <exception>

class BadException
{
public:
	std::string m_msg;
};

void TestException()
{
	std::cout << "TestException ===============begin=================\n";
	try
	{
		BadException exception = BadException();
		exception.m_msg = "throw ref exception";
		throw exception;
	}
	catch (BadException& e)
	{
		std::cout << e.m_msg << std::endl;
	}

	try
	{
		BadException * pException = new BadException();
		pException->m_msg = "throw pointer exception";
		throw pException;
	}
	catch (BadException* e)
	{
		std::cout << e->m_msg << std::endl;
		delete e;
		e = NULL;
	}

	try
	{
		//c++异常连空指针都抓不住。。也是太弱
		//BadException * pException = new BadException();
		//delete pException;
		//pException = nullptr;
		//pException->m_msg = "test null pointer";
	}
	catch (BadException* e)
	{

	}

	try
	{

	}
	catch (std::bad_alloc & e)
	{

	}
	catch (std::exception & e)
	{

	}
	std::cout << "TestException ===============end=================\n";
}