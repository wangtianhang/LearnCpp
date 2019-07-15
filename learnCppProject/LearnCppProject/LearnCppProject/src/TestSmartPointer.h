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

// sharedptr��Ȼ���ᵼ�±��� ���ǻ������õĻ� ���ܵ����޷��ͷ� ����������weakptr�ĸ���
void TestSharedPtr()
{
	using namespace std;
	shared_ptr<string> country[5] =
	{
		shared_ptr<string>(new string("USA")),
		shared_ptr<string>(new string("CHN")),
		shared_ptr<string>(new string("RUS")),
		shared_ptr<string>(new string("FRA")),
		shared_ptr<string>(new string("GRB"))
	};

	shared_ptr<string> pwin;
	cout << pwin.use_count() << endl;//���0
	pwin = country[2];
	/*ʹ��shared_ptrʱ������������Ϊshared_ptr�������ü�����pwin��films[2]��ָ��ͬһ���ڴ棬
	���ͷſռ�ʱ��Ϊ����Ҫ�ж����ü���ֵ�Ĵ�С��˲�����ֶ��ɾ��һ������Ĵ���

	������share�Ϳ��Կ�������Դ���Ա����ָ�빲����ʹ�ü���������������Դ������ָ�빲��
	����ͨ����Ա����use_count()���鿴��Դ�������߸�����
	*/
	cout << pwin.use_count() << endl;//���2

	for (int i = 0; i < 5; ++i)
		cout << *country[i] << endl;
	cout << "The best is " << *pwin << endl;
}

std::unique_ptr<std::string> TestReturnUniquePtr() {
	return std::unique_ptr<std::string>(new std::string("RUS"));
}

void TestUniquePtr()
{
	using namespace std;
	unique_ptr<string> pa(new string("CHN"));
	//unique_ptrû��use_count()����
	unique_ptr<string> pb(new string("USA"));

	pb = move(pa);
	//p2=p1;//���󣬲���ֱ���õ��ں�
	if (pa == nullptr)
		cout << "pa����Ϊ��" << endl;

	cout << "*pb " << *pb << endl;//pb����ˡ�CHA��

	string* ps = pb.release();//��յ�ǰ����ָ����ָ����Դ����,������ָ��
	cout << "*ps " << *ps << endl;//ps����ˡ�CHA��

	pa.reset(ps);//����ָ����һ������
	cout << "*pa " << *pa << endl;//pa����ˡ�CHA��

	pb = TestReturnUniquePtr();//���պ����ķ���ֵ�����õ��ںţ���Ϊʹ�����ƶ����캯��
	cout << "*pb " << *pb << endl;//pb����ˡ�RUS��
}

void TestSmartPointer()
{
	std::cout << "TestSmartPointer ===============begin=================\n";
	//TestAutoPtr();
	TestSharedPtr();

	TestUniquePtr();

	std::cout << "TestSmartPointer ===============end=================\n";
}