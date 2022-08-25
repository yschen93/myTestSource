#include <iostream>

class A
{
public:
	A() { std::cout << "A():this=" << this << std::endl; }
	~A() { std::cout << "~A():this=" << this << std::endl; }
	A(const A& other)
	{
		std::cout << "copy construct: " << this << " from " << &other << std::endl;
	}
	void foo() const
	{
		*a = 10; //1.编译通过，因为const代表此函数不能改变成员变量值。不代表不可改变指针所指向的对象
	}
	void dis()
	{

	}
private:
	int* a;
};

A foo()
{
	A a;
	return a;
}

void bar(A&& a) //或者改成A&&
{

}

int main(int argc, char* argv[])
{
	//2.用const T&
	//const A& b = foo();
	//b.dis(); 调用错误，因为b是一个const对象，只能调用const成员函数
	//3.用T&&
	A&& b = foo(); //对于临时对象（将亡值）的右值引用
	b.dis();

	bar(A()); //4.函数入参之所以写成const T&或T&&，是为了能够传入临时变量（将亡值）
}

/*const T&和T&&比较
* 基本可以划等号，唯一区别是对于const T&对象，不可调用非const成员函数
*/
