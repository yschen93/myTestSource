//
// Created by 谭鑫 on 2022/9/28.
//
#include <iostream>
#include <sstream>

void print()
{
    std::cout << "the end......" << std::endl;
}

template<typename T, typename... type>
void print(const T& firstArg, type... args)
{
    std::cout << "sizeof: " << sizeof...(args) << std::endl;
    std::cout << "firstArg: " << firstArg << std::endl;
    print(args...);
}

int main(int argc, char *argv[])
{
    std::string str;
    int index = 0;
    while (std::cin >> str)
    {
        std::cout << "[" << index << "]: " << str << std::endl;
        index++;
    }
}