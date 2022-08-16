//
// Created by 谭鑫 on 2022/8/12.
//
#include <iostream>
using namespace std;

class SelfManager
{
public:
    SelfManager()
    {
        std::cout << "SelfManager()" << std::endl;
    }
    ~SelfManager()
    {
        std::cout << "~SelfManager()" << std::endl;
    }
};

int main(int argc, char *argv[])
{
    int a, b = 0;
    SelfManager();
    try{
        if (b == 0)
            throw b;
        int c = a / b;

    }catch(int b)
    {
        std::cout << "catch" << std::endl;
        //std::cout << e.what() << std::endl;
    }
    return 0;
}
