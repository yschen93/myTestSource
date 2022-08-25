#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include <string>
#include "myString.h"
#include "mock_function.hpp"

struct myStringFixture
{
    myStringFixture(int count = 0)
    :i(count) {}
    int i;
    mock_myString mystr;
    void printCount()
    {
        std::cout << i << std::endl;
    }
};

BOOST_AUTO_TEST_SUITE(test_main)

BOOST_AUTO_TEST_CASE(test_constructor)
{
    //test default constructor string length
    BOOST_TEST( myString().size() == std::string().size());
    //test non-default constructor string length
    BOOST_TEST( myString("123").size() == std::string("123").size());
}

BOOST_FIXTURE_TEST_CASE(test_counter, myStringFixture)
{
    i++;
    printCount();
}

BOOST_FIXTURE_TEST_CASE(test_mock, myStringFixture)
{
    MOCK_EXPECT(mystr.test_function).once().with(1);
}

BOOST_AUTO_TEST_SUITE_END()


