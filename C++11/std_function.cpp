#include <iostream>
#include <functional>
#include <vector>

//std::function，可调用对象的包装器，可包装的对象有：函数，函数指针，lambda，仿函数

using Proc = std::function<int(int, int)>;

int foo(int x, int y)
{
    return x - y;
}

int baz(int x, int y)
{
    return x * y;
}

typedef int (*funp)(int x, int y);

class bar
{
public:
    bar() { std::cout << "bar::bar()" << std::endl; }
    int operator()(int x, int y)
    {
        if (y != 0)
            return x / y;
        return 0;
    }
};

int main() {
    //1.lambda
    Proc proc = [](int x, int y)  ->int { return x + y; }; //也可写作 auto proc = ...
    std::cout << proc(2, 3) << std::endl;

    //2.函数
    //没必要这么写，这样相当于调用了function(function&& other)
    //可以直接写成proc = foo;
    proc = std::function<int(int, int)>(std::move(foo));
    std::cout << proc(5, 2) << std::endl;

    //3.函数指针
    funp fp = baz;
    proc = fp;
    std::cout << proc(2, 5) << std::endl; //可以直接用bar()构造一个临时对象，然后oprator()调用仿函数

    //4.仿函数
    std::cout << bar()(100, 5) << std::endl; //可以直接用bar()构造一个临时对象，然后oprator()调用仿函数
    proc = bar();
    std::cout << proc(10, 2) << std::endl;  //或者把bar()临时对象赋值给std::function包装器，然后调用


    std::vector<std::function<int(int, int)> > v =
    {
        {[](int x, int y)  ->int { return x + y; }}, // lambda
        {foo},                                       // 函数
        {fp},                                        //函数指针
        {bar()}                                      //仿函数
    };

    return 0;
}

