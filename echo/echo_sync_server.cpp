#include <boost/asio.hpp>
#include <string>
#include <iostream>

using namespace boost::asio;

size_t read_complete(char * buff, const boost::system::error_code & err, size_t bytes_transferred) {
    if ( err) return 0;
    bool found = std::find(buff, buff + bytes_transferred, '\n') < buff + bytes_transferred;

    // 我们一个一个读取直到读到回车,不缓存
    return found ? 0 : 1;
}

void handle_connections(const std::shared_ptr<io_service>& ios) {
    ip::tcp::acceptor acceptor(*ios, ip::tcp::endpoint(ip::tcp::v4(),8001));
    char buff[1024];
    while ( true) {
        ip::tcp::socket sock(*ios);
        acceptor.accept(sock);
        size_t bytes = read(sock, buffer(buff), std::bind(read_complete,buff,std::placeholders::_1,std::placeholders::_2));
        std::string msg(buff, bytes);
        sock.write_some(buffer(msg));
        sock.close();
    }
}

int main(int argc, char *argv[]) {
    std::shared_ptr<io_service> ios = std::make_shared<io_service>();
    handle_connections(ios);
}