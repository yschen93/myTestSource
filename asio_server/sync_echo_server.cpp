#include <iostream>
#include <exception>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#define BUF_SIZE 1024

using namespace boost::asio;

void Session(ip::tcp::socket sock)
{
    try{
        while (true) {
            boost::array<char, BUF_SIZE> buf;
            boost::system::error_code ec;
            size_t length = sock.read_some(buffer(buf), ec);
            if (boost::asio::error::eof == ec) {
                std::cout << "connection closed normally" << std::endl;
                break;
            } else if (ec) {
                throw boost::system::system_error(ec);
            } else {
                write(sock, buffer(buf, length));
            }
        }
    } catch (const std::exception& e) {
        std::cout << "exception! e.what(): " << e.what() << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "usage: "<< argv[0] <<  " <port>" << std::endl;
        return -1;
    }

    size_t port = std::atoi(argv[1]);

    io_context ioc;

    ip::tcp::acceptor acceptor(ioc, ip::tcp::endpoint(ip::tcp::v4(), port));
    while (true) {
        Session(acceptor.accept());
    }

    return 0;
}