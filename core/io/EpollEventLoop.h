#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <thread>
#include <mutex>
#include <condition_variable>

template<typename Session>
class EpollEventLoop
{
    public:
        EpollEventLoop();
        ~EpollEventLoop();

        bool init();
        void start();
        bool epollThreadFunc();
        bool addSession(Session* session);
        void removeSession(Session* session);
        void setConnectionCount(uint32_t numConnections);
        void join();

    private:
        std::thread epoll_thread_;
        int epoll_fd_;
        //epoll_event epoll_event_;
        epoll_event *events_;
        uint32_t connection_cout_;
        uint32_t max_connection_cout_;
        std::mutex mutex_;
        std::condition_variable star_wait_;
};

