#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

void timerHandler(const boost::system::error_code &err) {
    std::cout << "2 seconds passed!" << std::endl;
}

int main() {
    io_service ios;
    deadline_timer timer(ios, boost::posix_time::milliseconds(2000));

    timer.async_wait(timerHandler);

    ios.run();

    return 0;
}