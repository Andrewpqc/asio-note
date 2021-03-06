#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <thread>

using namespace boost::asio;

typedef std::shared_ptr<ip::tcp::socket> socket_ptr;

void client_session(const socket_ptr& sock) {
    while (true) {
        char data[512];
        size_t len = sock->read_some(buffer(data));
        if (len > 0)
            write(*sock, buffer("ok", 2));
    }
}

int main() {
    io_service service;
    ip::tcp::endpoint ep(ip::tcp::v4(), 2001); // listen on 2001
    ip::tcp::acceptor acc(service, ep);

    while (true) {
        socket_ptr sock(new ip::tcp::socket(service));
        acc.accept(*sock);

        sock->set_option(ip::tcp::socket::reuse_address(true));

        std::thread(std::bind(client_session, sock));
    }

    return 0;
}
