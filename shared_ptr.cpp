#include <iostream>
#include <memory>

class A
{
public:
    void operator()(A* p)
    {
        std::cout << "release_self" << std::endl;
    }
};

void release_self(A* p)
{
    std::cout << "release_self" << std::endl;
}

int main(int argc, char* argv[])
{
    std::shared_ptr<int> sp(new int(10));
    std::cout << sp.use_count() << std::endl;
    std::shared_ptr<int>sp2(sp);
    std::shared_ptr<int>sp3(sp);
    std::cout << sp.use_count() << std::endl;

    sp.reset();
    std::cout << sp.use_count() << std::endl; //打印0
    std::cout << sp2.use_count() << std::endl;//打印2
    std::cout << sp3.use_count() << std::endl;//打印2
#if 0
    std::shared_ptr<A> sp(new A());
    std::cout << sp.use_count() << std::endl;  //打印1
    std::shared_ptr<A> sp1(sp);
    std::cout << sp.use_count() << std::endl;  //打印2
    sp1.reset(new A(), [](A* p) {std::cout << "release" << std::endl; });
    //sp1.reset(new A(), A()); 可替代上面
    //sp1.reset(new A(), release_self); 可替代上面
    std::cout << sp.use_count() << std::endl;  //打印1
#endif
    
    return 0;
}

