//
// Created by 谭鑫 on 2022/8/16.
//

#include "../include/myString.h"

myString::myString(const char *str)
{
    str_ = new char[strlen(str) + 1];
    strcpy(str_, str);
}