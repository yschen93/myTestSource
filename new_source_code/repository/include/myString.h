//
// Created by 谭鑫 on 2022/8/16.
//

#ifndef WORKSPACE_MYSTRING_H
#define WORKSPACE_MYSTRING_H
#include <string.h>

class myString {
public:
    myString(const char* str = "");
    /*copy constructor*/
    myString(const myString& rhs);

    /*assignment operator override*/
    myString& operator = (const myString& rhs);

    /*get string size(contain '\0')*/

    /*for mock test*/
    void test_function(int n);

    size_t size() const
    {
        return strlen(str_);
    }
private:
    char *str_;
};


#endif //WORKSPACE_MYSTRING_H
