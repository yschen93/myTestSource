#include <iostream>
#include <algorithm>
#include <vector>

// bool compare(int a, int b)
// {
//     return a > b;
// } (1)

// class compare
// {
// public:
//     bool operator()(int a, int b)
//     {
//         return a > b;
//     }
// }; (2)

int main(int argc, char* argv[])
{
    std::vector<int> vi = {1,3,5,7,9,2,4,6,8,10};
    //std::sort(vi.begin(), vi.end(), compare); (1)
    //std::sort(vi.begin(), vi.end(), compare()); (2)
    std::sort(vi.begin(), vi.end(), [](int a, int b){return a > b;});
    for (auto item : vi)
        std::cout << item << std::endl;
    return 0;
}
