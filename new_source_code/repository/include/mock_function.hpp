//
// Created by 谭鑫 on 2022/8/16.
//

#ifndef WORKSPACE_MOCK_FUNCTION_HPP
#define WORKSPACE_MOCK_FUNCTION_HPP
#include "turtle/mock.hpp"

MOCK_CLASS(mock_myString)
{
    MOCK_METHOD(test_function, 1, void(int));
};

#endif //WORKSPACE_MOCK_FUNCTION_HPP
