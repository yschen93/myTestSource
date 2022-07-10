#include <iostream>
#include <vector>
class Copy
{
public:
    Copy(int i = 0) :_p(new int(i)) { std::cout << "Copy::Copy()" << std::endl; }
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
    int* _p;
};

class Move
{
public:
    Move(int i = 0) :_p(new int(i)) { std::cout << "Move::Move(" << *_p << "), this: " << this << std::endl;; }
    ~Move()
    {
        std::cout << "~Move::Move(), this = " << this << std::endl;
        if (_p != nullptr)
            delete _p;
    }
    Move(Move&& rhs)
    {
        std::cout << "Move(Move&& rhs), " << this << " from " << &rhs << std::endl;
        _p = rhs._p;
        rhs._p = nullptr;

        //上述可简写成
        //*this = std::move(rhs);
    }

    Move& operator=(Move&& rhs)
    {
        std::cout << "Move& operator=(Move&& rhs), " << this << " from " << &rhs << std::endl;
        if (this != nullptr)
        {
            delete _p;
            _p = rhs._p;
            rhs._p = nullptr;
        }
        return *this;
    }
private:
    int* _p;
};
int main() {
    //Copy cp1;
    //Copy cp2(cp1); //调用拷贝构造
    //Copy cp3(std::move(cp1)); //构造拷贝构造，虽然用了std::move，生成了临时变量（右值）
    //cp2 = cp3;

    //Move mv1;
    //Move mv2(mv1); 错误，mv1不是临时变量，没有移动语意，所以无法调用移动构造
    //Move mv3(Move());
    //mv3 = std::move(mv1);
    std::vector<Move> vm;
    vm.reserve(10);
    vm.push_back(Move(1));
    vm.push_back(Move(2));
    vm.insert(vm.begin(), Move(3));
    return 0;
}

//总结，拷贝的语意更容易满足，移动的语意，参数必须是临时变量
/* output */
/*
Move::Move(1), this: 004FF5F8
Move(Move && rhs), 009F65C0 from 004FF5F8
~Move::Move(), this = 004FF5F8
Move::Move(2), this: 004FF5EC
Move(Move && rhs), 009F65C4 from 004FF5EC
~Move::Move(), this = 004FF5EC
Move::Move(3), this: 004FF5E0
Move(Move && rhs), 004FF3E8 from 004FF5E0
Move(Move && rhs), 009F65C8 from 009F65C4
Move& operator=(Move&& rhs), 009F65C4 from 009F65C0
Move& operator=(Move&& rhs), 009F65C0 from 004FF3E8
~Move::Move(), this = 004FF3E8
~Move::Move(), this = 004FF5E0
~Move::Move(), this = 009F65C0
~Move::Move(), this = 009F65C4
~Move::Move(), this = 009F65C8
*/
