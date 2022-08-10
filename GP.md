# 类模板（能够实现偏特化）
## 两类偏特化
+ “数量”偏特化
```
#include <iostream>

using namespace std;

template<typename T1, typename T2>
class foo
{
public:
	foo(const T1& t1, const T2& t2)
		:t1_(t1), t2_(t2)
	{}
	void print() const
	{
		std::cout << "class foo" << std::endl;
		std::cout << "t1: " << t1_ << ", t2: " << t2_ << std::endl;
	}
private:
	T1 t1_;
	T2 t2_;
};

template<>
class foo<int, double>
{
public:
	foo(const int& t1, const double& t2)
		:t1_(t1), t2_(t2)
	{}
	void print() const
	{
		std::cout << "class foo<int, double>" << std::endl;
		std::cout << "t1: " << t1_ << ", t2: " << t2_ << std::endl;
	}
private:
	int t1_;
	double t2_;
};

template<typename T2>
class foo<int, T2>
{
public:
	foo(const int& t1, const double& t2)
		:t1_(t1), t2_(t2)
	{}
	void print() const
	{
		std::cout << "class foo<int, T2>" << std::endl;
		std::cout << "t1: " << t1_ << ", t2: " << t2_ << std::endl;
	}
private:
	int t1_;
	double t2_;
};

//========================================================

template<class T>
class baz
{
public:
	baz(const T t)
		:t_(t)
	{}
	void print() const
	{
		std::cout << "class baz" << std::endl;
		std::cout << "t: " << t_ << std::endl;
	}
private:
	T t_;
};

template<class T>
class baz<T*>
{
public:
	baz(T* t)
		:t_(t)
	{}
	void print() const
	{
		std::cout << "baz<T*>" << std::endl;
		std::cout << "t: " << t_ << std::endl;
	}
private:
	T* t_;
};

int main()
{
	foo<int, int> f1(3, 4);
	f1.print();
	foo<int, double> f2(3, 4);
	f2.print();
	foo<double, double> f3(3, 4);
	f3.print();

	int a = 10;
	baz<int*> b(&a);
	b.print();
}
```

+ “范围偏特化”

# 函数模板（语法上不能够实现偏特化）
# 成员模板（待研究）
