//
// Created by 谭鑫 on 2022/9/28.
//
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "usage: ./daytime_client <ip:port>" << std::endl;
            return -1;
        }
        boost::asio::io_context io;
        boost::asio::ip::tcp::resolver resolver(io);
        boost::asio::ip::tcp::resolver::results_type endpoints =
                resolver.resolve(argv[1], "daytime");

        boost::asio::ip::tcp::socket sock(io);
        boost::asio::connect(sock, endpoints);

        for (; ;)
        {
            boost::array<char, 128> buf;
            boost::system::error_code ec;
            size_t len = sock.read_some(boost::asio::buffer(buf), ec);
            if (ec == boost::asio::error::eof)
                break;
            else if (ec)
                throw boost::system::system_error(ec);

            std::cout.write(buf.data(), len);
        }
    }
    catch(std::exception& e)
    {
        std::cerr << "e.what(): " << e.what() << std::endl;
    }

    return 0;
}