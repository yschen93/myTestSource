#include <iostream>
#include <functional>


int main(int argc, char* argv[])
{
    //1
    //说明lambda表达式的本质，是一个函数包裹器
    std::function<int(int)> foo = [](int a = 10){return a;}; //说明lambda表达式的本质，是一个函数包裹器
    std::cout << foo(4) << std::endl;

    //2
    //mutable说明(必须跟(参数列表))
    //lambda表达式本身是一个闭包，即跟外部上下文隔离，但可通过
    //值捕获和引用捕获破坏闭包
    //[&]可改变值本身
    //[=]外部的值在lambda表达式内部是read-only，若要形式上的改变，则需加上mutable
    int a = 100, b = 200;
    auto bar = [=]() mutable {
        a = 10; //若没有mutable，则此编译不过
        b = 20; //若没有mutable，则此编译不过
        std::cout << a << ":" << b << std::endl;
    };
    bar();
    std::cout << a << ":" << b << std::endl;


    //3
    //说明lambda表达式和仿函数的关系：lambda表达式是匿名的仿函数
    double salary;
    std::cin >> salary;
    // if (salary > 30000) {
    //     std::cout << [salary](double rate, double base){
    //         return (salary - base) * rate;
    //     }(0.3, 20000) << std::endl;
    // } else if (salary > 10000) {
    //     std::cout << [salary](double rate, double base){
    //         return (salary - base) * rate;
    //     }(0.2, 10000) << std::endl;
    // } else {
    //     std::cout << [salary](double rate, double base){
    //         return (salary - base) * rate;
    //     }(0.1, 5000) << std::endl;
    // }

    //or
    double highrate = 0.3, hightbase = 20000;
    double middlerate = 0.2, middlebase = 10000;
    double lowrate = 0.1, lowtbase = 5000;
    if (salary > 30000) {
        std::cout << [highrate, hightbase](double salary){
            return (salary - hightbase) * highrate;
        }(salary) << std::endl;
    } else if (salary > 10000) {
        std::cout << [middlerate, middlebase](double salary){
            return (salary - middlebase) * middlerate;
        }(salary) << std::endl;
    } else {
        std::cout << [lowrate, lowtbase](double salary){
            return (salary - lowtbase) * lowrate;
        }(salary) << std::endl;
    }
    return 0;
}
