#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/*1.拷贝构造/赋值，移动构造/赋值，实现其一种语境（拷贝、移动），则另一种语境默认无；
 *2.要想实现两种语义，则需手动实现拷贝和移动；
 */

class my_string
{
public:
	my_string(const char* str)
		:_str(new char[strlen(str) + 1])
	{
		strcpy_s(_str, strlen(str) + 1, str);
	}

	my_string()
		:_str(new char(1))
	{
		*_str = '\0';
	}

	my_string(const my_string& rhs)
		:_str(new char[strlen(rhs._str) + 1])
	{
		std::cout << "my_string::my_string(const my_string& rhs)" << std::endl;
		strcpy_s(_str, strlen(rhs._str) + 1, rhs._str);
	}

	//移动构造，某种特定场景下的浅拷贝
	my_string(my_string&& rhs)
	{
		std::cout << "my_string::my_string(my_string&& rhs)" << std::endl;
		_str = rhs._str;
		rhs._str = nullptr; //1.结合析构函数的指针判断，避免把内存释放
	}
	
	my_string& operator=(const my_string& rhs)
	{
		if (this == &rhs)
			return *this;
		delete []_str;
		_str = new char [strlen(rhs._str)+1];
		strcpy_s(_str, strlen(rhs._str) + 1, rhs._str);
		return *this;
	}

	friend ostream& operator<<(ostream& out, my_string& rhs);

	~my_string()
	{
		if (_str != nullptr) //2.避免内存释放
			delete []_str;
	}
private:
	char* _str;
};

ostream& operator<<(ostream& out, my_string& rhs)
{
	out << rhs._str << std::endl;
	return out;
}

int main(int argc, char* argv[])
{
	string s1 = "123";
	my_string s2 = "456";
	my_string s3 = s2;
	my_string s4 = std::move(s3); //调用拷贝构造
	std::cout << s1 << std::endl; //调用移动构造
}
