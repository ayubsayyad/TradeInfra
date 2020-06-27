#pragma once
#include <folly/ProducerConsumerQueue.h>

namespace core::async{

template<typename T, size_t = 2048>
class SPSCBoundedQueue{
    public:
        bool push(const T& t){
            return queue_.write(t);
        }

    private:
        folly::ProducerConsumerQueue<T> queue_;
        std::thread 
};

}
