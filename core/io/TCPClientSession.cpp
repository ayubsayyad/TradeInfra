#include "TCPClientSession.h"
#include "core/logger/Logger.h"

using namespace core::io;

bool TCPClientSession::init(const core::config::Config& config){
    return true;
}

bool TCPClientSession::connectSession(){
    socket_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); //as ony ports will be expected on running assuming server as local
    server_address.sin_port = htons(port_number_);
    int ret = connect(socket_fd_, (sockaddr*)&server_address, sizeof (sockaddr_in));
    if(-1 == ret){
        std::cout << "error connecting socket "  << errno << std::endl;
        return false;
    }

    int flags;
    flags = fcntl(socket_fd_, F_GETFL, 0);
    if ( flags < 0){
        std::cout << "error getting sock flags socket " << std::endl;
        return false;
    }

    if (fcntl(socket_fd_, F_SETFL, flags | O_NONBLOCK) < 0){
        std::cout << "error setting sock flags non block" << std::endl;
        return false;
    }

    return true;
}

bool TCPClientSession::write(char* msg, size_t length){
    auto sizewritten = send(socket_fd_, msg, length, 0);
    return true;
}

bool TCPClientSession::readAndProcessData(){
    size_t numBytesRead = read(socket_fd_, buffer_.buffer_ + buffer_.bufferSize_, 2048 - buffer_.bufferSize_);
    if (!numBytesRead){
        //socket closed, remove from epoll
        return false;
    }

    buffer_.bufferSize_ += numBytesRead;
    processData();

    return true;
}

void TCPClientSession::processData(){
    /*
    size_t currIdx = 0;
    while ((buffer_.bufferSize_ - currIdx) >= sizeof(Message)){
        Message* msg = (Message*)&buffer_.buffer_[currIdx];
        int64_t* exchangeVal = (int64_t*)&msg->message[4];
        if(0 == *exchangeVal){
            closeSession();
            return;
        }
        lastIndex_ = sorted_list.insert(*exchangeVal, lastIndex_);
        currIdx += sizeof(Message);
    }
    if((buffer_.bufferSize_ - currIdx)){
        buffer_.moveToStart(currIdx);
    }
    else{
        buffer_.bufferSize_ = 0;
    }*/
}

