#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;

int main() {

    io_service ios;

    ip::tcp::resolver resolver(ios);

    ip::tcp::resolver::query query("www.baidu.com", "80");

    ip::tcp::resolver::iterator iter = resolver.resolve(query);

    ip::tcp::endpoint ep = *iter;

    std::cout << ep.address().to_string() << std::endl;
    std::cout << ep.port() << std::endl;
    std::cout << ep.protocol().type() << std::endl;


    return 0;
}