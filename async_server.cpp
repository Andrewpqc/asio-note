// a async server

#include <boost/asio.hpp>
#include <iostream>
#include <thread>
using namespace boost::asio;


int main(void) {
    io_service ios;

    ip::tcp::endpoint ep(ip::tcp::v4(),12345);

    ip::tcp::acceptor acc(ios,ep);

    ip::tcp::socket sock(ios);

    acc.async_accept(sock,[&](const boost::system::error_code & err){
       if(!err){
           std::cout<<"accept a connect"<<std::endl;
           std::cout<<ip::host_name()<<std::endl; //andrew-ubuntu 返回本地主机名
       }
    });

    ios.run();




    return 0;
}