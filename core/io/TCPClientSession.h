#pragma once

#include <memory>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "core/config/Config.h"
#include "TCPBuffer.h"

namespace core::io{

class TCPClientSession{
public:
    TCPClientSession()
    {}

    bool init(const core::config::Config& config);
    bool connectSession();
    bool readAndProcessData();
    void processData();
    bool write(char* msg, size_t length);

    void setPortNumber(uint16_t port){
        port_number_ = port;
    }

    bool closeSession(){
        shutdown(socket_fd_, SHUT_RDWR);
        return true;
    }

    bool onReadReady(){
        return readAndProcessData();
    }

    int getSocketFd(){
        return socket_fd_;
    }

private:
    Buffer buffer_;
    int socket_fd_;
    std::string host_name_;
    uint16_t port_number_;
};

}
