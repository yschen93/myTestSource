#include <iostream>

class Copy
{
public:
    Copy(int i = 0):_p(new int(i)) {std::cout << "Copy::Copy()" << std::endl;}
    ~Copy()
    {
        std::cout << "~Copy::Copy()" << std::endl;
        if (_p != nullptr)
            delete _p;
    }
    Copy(const Copy& rhs)
        :_p(new int(*rhs._p))
    {
        std::cout << "Copy(const Copy& rhs)" << std::endl;
    }

    Copy& operator=(const Copy& rhs)
    {
        std::cout << "Copy& operator=(const Copy& rhs)" << std::endl;
        if (this != &rhs) {
            delete _p;
            _p = new int(*rhs._p);
        }
        return *this;
    }
private:
    int *_p;
};

class Move
{
public:
    Move(int i = 0):_p(new int(i)) {std::cout << "Move::Move()" << std::endl;}
    ~Move()
    {
        std::cout << "~Move::Move()" << std::endl;
        if (_p != nullptr)
            delete _p;
    }
    Move(Move&& rhs)
    {
        std::cout << "Move(Move&& rhs)" << std::endl;
        _p = rhs._p;
        rhs._p = nullptr;
    }

    Move& operator=(Move&& rhs)
    {
        std::cout << "Move& operator=(Move&& rhs)" << std::endl;
        delete _p;
        _p = rhs._p;
        rhs._p = nullptr;
        return *this;
    }
private:
    int *_p;
};
int main() {
    Copy cp1;
    Copy cp2(cp1); //调用拷贝构造
    Copy cp3(std::move(cp1)); //构造拷贝构造，虽然用了std::move，生成了临时变量（右值）
    cp2 = cp3;

    Move mv1;
    //Move mv2(mv1); 错误，mv1不是临时变量，没有移动语意，所以无法调用移动构造
    Move mv3(std::move(mv1));
    mv3 = std::move(mv1);
    return 0;
}

//总结，拷贝的语意更容易满足，移动的语意，参数必须是临时变量
