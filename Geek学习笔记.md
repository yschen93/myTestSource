# Geek学习笔记

## 1.关于智能指针作为函数参数传递形式探讨

```c++
fun(Widget*)

fun(Widget&)

fun(std::unique_ptr<Widget>)

fun(std::unique_ptr<Widget>&)

fun(std::shared_ptr<Widget>)

fun(std::shared_ptr<Widget>&)
```



结论：

1.fun(std::shared_ptr<Widget>)

对于引用计数型智能指针，永远优先于使用非拷贝形式，除非有明显意图必须增加引用计数的场景（这里如果传递的是一个临时的shared_ptr，不会增加引用计数）。因为它会带来引用计数的增加和减少，而这两个操作在底层是用了原子变量或类似同步原语的方式实现，有性能损耗。并且临时对象的删除也会有成本。

使用这种形式的一种场景是，多线程中，你拥有必须显示增加其引用计数的理由，以保证在被调用函数使用此对象时仍有效。



2.fun(Widget*)和fun(Widget&)

这两种形式往往是更合适的选择。因为结构化生命周期的原因，被调用者（函数）的生命周期往往是调用者（函数）的子集，这保证了在被调用者内部对象的有效性。并且也不应该通过函数参数来传递”生存期策略“的信息。所以，还是一如往常，在需要有null语意的场合，用*，否则用&。如果有只读语意，那么就用const Widget *或const Widget &。



3.fun(std::unique_ptr<Widget>)

这种形式，拥有良好的“所有权转移”语义。这显示的告诉调用者，被调用将作为sink（接收器）获取对象的所有权。当然，并非一定要以std::unique_ptr<Widget>对象的方式显示调用函数，因为Widget*是可以显示转换为std::unique_ptr<Widget>。

```
void fun(std::unique_ptr<Widget>);
void foo()
{
	Widget* wptr = new Widget();
	fun(std::unique_ptr<Widget>(wptr)); // fun形参将接收wptr的所有权，并承担起释放它的责任
}
```



4.fun(std::unique_ptr<Widget>&)

这种形式只适合被调用者接收现有调用者的unique_ptr，并且准备在调用函数内，修改它（比如让它应用不同的对象）。永远不要使用**const std::unique_ptr<Widget>&**这种形式。而应该用Widget*或Widget&代替。



5.fun(std::shared_ptr<Widget>&)

和4类似，只有在对shared_ptr“需要做点什么”语义下，这才是该选择的形式。特殊情况是，在不需要明确增加引用计数，且存在“共享所有权”语义下，使用**const std::shared_ptr<Widget>&**。



## 2.关于异常noexcept

对于不会抛出异常的函数，显示声明为noexcept能带来多方面好处：

1.编译器优化。对于支持C++11标准以上的编译器，当声明为noexcept后，若异常产生，这个函数本身不再保存运行期栈于可展开状态（unwindable state）；也不用保证它以构造的逆序析构其中的对象。

```c++
class Base
{
public:
    Base()
    {
        std::cout << "Base::Base()" << std::endl;
    }

    virtual ~Base()
    {
        std::cout << "Base::~Base()" << std::endl;
    }
};

void baz() noexcept
{
    throw std::runtime_error("bad test");
}

int main(int argc, char* argv[])
{
    try
    {
        Base b;
        baz();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

// 输出：
// Base::Base()
// libc++abi: terminating due to uncaught exception of type std::runtime_error: bad test
// zsh: abort      ./test_smart_ptr
```

可以看到，当把baz函数声明为noexcept后，Base的析构函数并未被正常调用，而且在main函数中的try也未捕获到异常。可以理解为函数内部因为noexcept做很多简化工作，从而间接的提高了效率。



2.C++11标准中，对于移动构造和swap声明为noexcept。可带来显而易见的好处。前者在例如std::vector扩充时，为了保证“异常安全性”，只有在移动构造函数声明为noexcept时才会调用，否则调用的是拷贝构造；后者在一些移动赋值运算符重载中，是重要的依赖函数。

noexcept对于移动语义，swap函数，构造和析构最有价值。



## 3.关于vector

建议：

1.现代系统架构对于连续内存访问远快于非连续内存，所以不知道用什么数据结构时，就用vector；

2.vector有扩容的行为，所以当创建容器时知晓其大小范围，应该提前保留（reserve）大小，避免发生拷贝或移动；

3.C++11后提供的emplace_xxx语义，目的是就地构造（in place），减少一次拷贝或移动构造和析构。如果是移动，那么性能损失还好，如果是拷贝，则可能会有较大的性能损失。



## 4.关于deque

双端队列（double endian queue）

提供头、尾插入的快捷性。内存上部分连续。相比于vector，它的优势仅体现在头部插入的高效性。



## 5.关于list

双向链表，支持O(1)时间复杂度的**任意位置**插入操作；但是由于他的元素内存不是连续的，所以它的遍历性能不及vector和dequeue。适合不用频繁遍历，需要频繁插入的场景。



## 6.关于forward_list

单向链表，减少部分接口，但提高了效率。特别对于小内存大小元素。



## 7.关于queue和stack

严格来说，它们只是容器适配器，默认底层容器为deque。



## 8.关于map和unordered_map

map需要实现key的严格弱序小于比较函数：operator<。对于内置类型（包括指针），标准库里的容器类型，智能指针，编译器都已经实现了。但对于自定义类型，需要手动实现。



unordered_map，需要实现hash和元素类型的==比较符号。对于内置类型（包括指针），标准库里的容器类型，智能指针，编译器都已经实现了。但对于自定义类型，需要手动实现。