#define BOOST_TEST_MODULE test_main
#include <boost/test/unit_test.hpp>
#include "myString.h"
#include <string>

struct myStringFixture
{
    myStringFixture(int count = 0)
    :i(count) {}
    int i;
    void printCount()
    {
        BOOST_TEST_MESSAGE("printCount");
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

BOOST_AUTO_TEST_SUITE_END()


