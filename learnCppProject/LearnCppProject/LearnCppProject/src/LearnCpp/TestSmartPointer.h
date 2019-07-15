#pragma once

#include <iostream>
#include <memory.h>

using namespace std;

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

// sharedptr最然不会导致崩溃 但是互相引用的话 可能导致无法释放 这又引出了weakptr的概念
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
	cout << pwin.use_count() << endl;//输出0
	pwin = country[2];
	/*使用shared_ptr时运行正常，因为shared_ptr采用引用计数，pwin和films[2]都指向同一块内存，
	在释放空间时因为事先要判断引用计数值的大小因此不会出现多次删除一个对象的错误。

	从名字share就可以看出了资源可以被多个指针共享，它使用计数机制来表明资源被几个指针共享。
	可以通过成员函数use_count()来查看资源的所有者个数。
	*/
	cout << pwin.use_count() << endl;//输出2

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
	//unique_ptr没有use_count()方法
	unique_ptr<string> pb(new string("USA"));

	pb = move(pa);
	//p2=p1;//错误，不能直接用等于号
	if (pa == nullptr)
		cout << "pa现在为空" << endl;

	cout << "*pb " << *pb << endl;//pb变成了“CHA”

	string* ps = pb.release();//清空当前智能指针所指的资源对象,并返回指针
	cout << "*ps " << *ps << endl;//ps变成了“CHA”

	pa.reset(ps);//重置指向另一个对象
	cout << "*pa " << *pa << endl;//pa变成了“CHA”

	pb = TestReturnUniquePtr();//接收函数的返回值可以用等于号，因为使用了移动构造函数
	cout << "*pb " << *pb << endl;//pb变成了“RUS”
}

class B;
class A
{
public:
	weak_ptr<B> pb_weak;
	~A()
	{
		cout << "A delete\n";
	}
};
class B
{
public:
	shared_ptr<A> pa_;
	~B()
	{
		cout << "B delete\n";
	}
	void print() {
		cout << "This is B" << endl;
	}
};

void TestWeakPtr()
{
	shared_ptr<B> pb(new B());
	cout << "pb.use_count " << pb.use_count() << endl;//1
	shared_ptr<A> pa(new A());
	cout << "pa.use_count " << pa.use_count() << endl;//1

	pb->pa_ = pa;
	cout << "pb.use_count " << pb.use_count() << endl;//1
	cout << "pa.use_count " << pa.use_count() << endl;//2

	pa->pb_weak = pb;
	cout << "pb.use_count " << pb.use_count() << endl;//1：弱引用不会增加所指资源的引用计数use_count()的值
	cout << "pa.use_count " << pa.use_count() << endl;//2

	shared_ptr<B> p = pa->pb_weak.lock();
	p->print();//不能通过weak_ptr直接访问对象的方法，须先转化为shared_ptr
	cout << "pb.use_count " << pb.use_count() << endl;//2
	cout << "pa.use_count " << pa.use_count() << endl;//2

	//函数结束时，正确的情况下，应该调用A和B的析构函数
	/*资源B的引用计数一直就只有1，当pb析构时，B的计数减一，变为0，B得到释放，
B释放的同时也会使A的计数减一，同时pa自己析构时也会使资源A的计数减一，那么A的计数为0，A得到释放。
*/
}

void TestSmartPointer()
{
	std::cout << "TestSmartPointer ===============begin=================\n";
	//TestAutoPtr();
	TestUniquePtr();

	TestSharedPtr();

	TestWeakPtr();
	std::cout << "TestSmartPointer ===============end=================\n";
}