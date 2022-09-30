//
// Created by 谭鑫 on 2022/9/28.
//
#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <ctime>

using namespace boost::asio;

std::string echo_string()
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

int main(int argc, char *argv[])
{
    try
    {
        io_context io;
        ip::tcp::acceptor acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), 13));
        for (; ;)
        {
            ip::tcp::socket sock(io);
            acceptor.accept(sock);
            std::cout << "ok" << std::endl;
            std::string message = echo_string();
            boost::system::error_code ec;
            write(sock, boost::asio::buffer(message), ec);
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "e.what()" << e.what() << std::endl;
    }

    return 0;
}