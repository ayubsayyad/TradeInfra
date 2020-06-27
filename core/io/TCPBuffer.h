#pragma once
#include <string>

namespace core::io{
struct Buffer{
    Buffer(){
        bufferSize_ = 0;
    }

    void moveToStart(size_t idx){
        std::memcpy(buffer_, buffer_ + idx, bufferSize_ - idx);
        bufferSize_ = bufferSize_ - idx;
    }

    void append(char* data, size_t len){
        std::memcpy(buffer_ + bufferSize_, data, len);
    }


    char buffer_[2048];
    size_t bufferSize_;
};
}
