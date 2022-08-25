//
// Created by 谭鑫 on 2022/8/16.
//

#include "../include/myString.h"
#include <iostream>

myString::myString(const char *str)
{
    str_ = new char[strlen(str) + 1];
    strcpy(str_, str);
}

void myString::test_function(int n)
{
    std::cout << "test_function::n = " << n << std::endl;
}