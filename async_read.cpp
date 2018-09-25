#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;

size_t up_to_enter(const boost::system::error_code &, size_t bytes) {
    for ( size_t i = 0; i < bytes; ++i)
        if ( buff[i + offset] == '\n')  //读取到第一个换行符
            return 0;
    return 1;
}

void on_read(const boost::system::error_code & err,size_t bytes_transfered){}

int main() {
    io_service ios;
    ip::tcp::endpoint ep(ip::tcp::v4(),12345);

    ip::tcp::socket sock(ios);

    ip::tcp::acceptor acc(ios,ep);

    acc.async_accept(sock, [&](const boost::system::error_code &err) {
        if (!err) {
            std::cout << "accept a connect" << std::endl;
            std::cout << ip::host_name() << std::endl; //andrew-ubuntu 返回本地主机名

            char* buf = new char[512];
            //read
            async_read(sock,buffer(buf,512),up_to_enter,on_read);

            //write

        }
    });

    ios.run();



    return 0;
}