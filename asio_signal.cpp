#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

void SigHandler(const boost::system::error_code & err,int signal){

    if(!err){
        std::cout << "signal coming..." << std::endl;
        switch (signal){
            case SIGQUIT:
                std::cout << "SIGQUIT ..." << std::endl;
                break;
            default:
                std::cout << "other signal ..." << std::endl;
        }
    }
    else std::cout << err.message() << std::endl;
    std::cout << "signal handler called" << std::endl;

}

int main() {
    io_service ios;
    signal_set sigSet(ios,SIGINT,SIGTERM,SIGQUIT);


    sigSet.async_wait(SigHandler);

    ios.run();
//    for(int i=0;i<10;i++){
//        std::cout<<i<<std::endl;
//        sleep(2);
//    }


    return 0;
}
