#include "core/io/SharedMemory.h"

#include <iostream>
#include <cstring>
#include <memory>

int main(){
    core::io::SharedMemoryImpl shm("test", 2048, core::io::SharedMemoryImpl::AccessMode::AM_WRITE, nullptr, true);
    core::io::SharedMemoryImpl shmc("test", 2048, core::io::SharedMemoryImpl::AccessMode::AM_READ, nullptr, false);
    auto p = std::filesystem::path("test.txt");
    core::io::SharedMemoryImpl shmf(p, core::io::SharedMemoryImpl::AccessMode::AM_WRITE, nullptr);
    std::cout << shmf.begin() << std::endl;

    auto addr = shm.begin();
    std::memcpy(addr, "Ayub", 4);
    auto addr2 = shmc.begin();
    std::cout << addr2 << std::endl;
    return 0;
}

