#include <iostream>

#if 0
enum season
{
	spring,
	summer,
	winter
};

enum other
{
	spring,
	summer,
	winter
};
#endif

//方法1
#if 0
namespace Season
{
	enum season
	{
		spring,
		summer,
		winter
	};
}

class Other
{
public:
	enum other
	{
		spring,
		summer,
		winter
	};
};
#endif

//方法2
enum class season
{
	spring,
	summer,
	winter
};

enum class other
{
	spring,
	summer,
	winter
};

int main(int argc, char* argv[])
{
	//season s = summer; //错误。会产生歧义，编译器不知道具体是season还是other的summer
	//解决方法1
	//Season::season s = Season::spring;
	//Other::other o = Other::summer;

	//解决方法2
	season s = season::spring;
	other o = other::summer;
	std::cout << static_cast<int>(s) << std::endl;
	std::cout << static_cast<int>(o) << std::endl;
}
