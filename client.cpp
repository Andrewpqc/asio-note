#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost::asio;

void on_read(char* buf,const boost::system::error_code& err,size_t bytes_transfered){
    if(!err){
        std::cout<<"bytes transfered:"<<bytes_transfered<<std::endl;
        std::cout<<buf<<std::endl;
        delete [] buf;
    }
}

int main() {
    io_service service;
    ip::tcp::endpoint ep(ip::address::from_string("127.0.0.1"), 80);
    ip::tcp::socket sock(service);
    sock.connect(ep);
    sock.write_some(buffer("Get /index.html HTTP/1.1\r\nHost: 127.0.0.1:80\r\n\r\n"));
//    std::cout << "bytes available:" << sock.available() << std::endl;
//    char buf[512];
//    sock.read_some(buffer(buf));

    char * buf = new char[512];
    sock.async_read_some(buffer(buf,512),
            std::bind(on_read,buf,std::placeholders::_1,std::placeholders::_2));
//    std::cout << buf << std::endl;

    service.run();


    return 0;
}