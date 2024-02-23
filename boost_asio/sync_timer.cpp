#include <iostream>
#include <boost/asio.hpp>

int main(int argc, char* argv[])
{
    boost::asio::io_context ioc;
    boost::asio::steady_timer t(ioc, boost::asio::chrono::seconds(3));
    //std::this_thread::sleep_for(std::chrono::seconds(3));
    //std::cout << "before wait" << std::endl;
    t.wait();
    std::cout << "hello boost asio!" << std::endl;
}