#pragma once

#include <iostream>
#include <memory.h>

//auto_ptr����C++98��׼�µ�����ָ�룬���ڳ����Ѿ���C++��׼����������ָ��ȡ��������ȱ������ת������Ȩ���ʹ�����ڲ���ȫ��C++11�±�׼����unique_ptr������auto_ptrԭ�й��ܣ����÷����ܼ����Ĳ���unique_ptr��
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
	pwin = country[2]; //������Ȩ��country[2]ת�ø�pwin����ʱcountry[2]�������ø��ַ����Ӷ���ɿ�ָ�룬�����е�ѭ��ʱ�ͻ����

	for (int i = 0; i < 5; ++i)
		std::cout << *country[i] << std::endl;//���е�[2]ʱ��������Ϊcountry[2]Ϊ��
	std::cout << "The best is " << *pwin << std::endl;
}

void TestSmartPointer()
{
	//TestAutoPtr();
}