#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include <memory>

using namespace boost::asio;

#define MEM_FN(x) std::bind(&self_type::x, shared_from_this())
#define MEM_FN1(x,y) std::bind(&self_type::x, shared_from_this(),y)
#define MEM_FN2(x,y,z) std::bind(&self_type::x, shared_from_this(),y,z)

class talk_to_svr : public std::enable_shared_from_this<talk_to_svr> {
public:
    typedef talk_to_svr self_type;

    explicit talk_to_svr(const std::string & message) : sock_(service), started_(true), message_(message) {}

    void start(ip::tcp::endpoint & ep) {
        sock_.async_connect(ep, MEM_FN1(on_connect,std::placeholders::_1));
    }


    typedef boost::system::error_code error_code;
    typedef std::shared_ptr<talk_to_svr> ptr;

    static ptr start(ip::tcp::endpoint ep, const std::string &message) {
        ptr new_(new talk_to_svr(message));
        new_->start(ep);
        return new_;
    }

    void stop() {
        if ( !started_) return;
        started_ = false;
        sock_.close();
    }

    bool started() { return started_; }

private:
    ip::tcp::socket sock_;
    enum { max_msg = 1024 };
    char read_buffer_[max_msg];
    char write_buffer_[max_msg];
    bool started_;
    std::string message_;
};



int main() {




    return 0;
}