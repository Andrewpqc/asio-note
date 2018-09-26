#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <thread>


using namespace boost::asio;

size_t read_complete(char *buf, const boost::system::error_code &err, size_t bytes_transferred) {
    if (err) return 0; //if err occurred, stop.

    bool found = std::find(buf, buf + bytes_transferred, '\n') < buf + bytes_transferred;

    // 我们一个一个读取直到读到回车,不缓存
    return found ? 0 : 1;
}

void sync_echo(std::string msg,
               const std::shared_ptr<ip::tcp::endpoint> &ep,
               const std::shared_ptr<io_service> &service) {
    msg += '\n';
    ip::tcp::socket sock(*service);
    sock.connect(*ep);
    sock.write_some(buffer(msg));
    char buf[1024];
    size_t bytes_readed = read(sock, buffer(buf),
                               std::bind(read_complete, buf, std::placeholders::_1, std::placeholders::_2));

    std::string copy(buf, bytes_readed - 1);
    msg = msg.substr(0, msg.size() - 1);
    std::cout << "server echoed our " << msg << ": "
              << (copy == msg ? "OK" : "FAIL") << std::endl;
    sock.close();
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "usage:" << argv[0] << "<port>" << std::endl;
        return 0;
    }

//    io_service ios;
    std::shared_ptr<io_service> ios = std::make_shared<io_service>();
    std::shared_ptr<ip::tcp::endpoint> ep = std::make_shared<ip::tcp::endpoint>(ip::address::from_string("127.0.0.1"),
                                                                                static_cast<unsigned short>(std::stoul(
                                                                                        argv[1])));

    while (true) {
        std::string message;
        std::cout << "message to send:";
        std::cin >> message;
        sync_echo(message, ep, ios);

    }
    return 0;
}