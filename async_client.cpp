#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <sstream>

using namespace boost::asio;


int main() {
    io_service ios;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 80);
    ip::tcp::socket sock(ios);

    sock.async_connect(ep, [&](const boost::system::error_code &err) {
        if (!err) {
            std::cout << "connected" << std::endl;
            sock.close();
        }
    });

    ios.run();

    return 0;
}
