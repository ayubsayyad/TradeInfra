#pragma once
#include <string>
#include <filesystem>

namespace  core::io {


class SharedMemoryImpl    /// Shared memory implementation for POSIX platforms.
{
public:
    enum AccessMode
    {
        AM_READ = 0,
        AM_WRITE
    };

    SharedMemoryImpl(const std::string& name, std::size_t size, SharedMemoryImpl::AccessMode mode, const void* addrHint, bool server);
    SharedMemoryImpl(const std::filesystem::path& file, SharedMemoryImpl::AccessMode mode, const void* addrHint);
    void map(const void* addrHint);
    void unmap();
    void close();
    inline char* begin();
    inline char* end();
    ~SharedMemoryImpl();

private:
    SharedMemoryImpl();
    SharedMemoryImpl(const SharedMemoryImpl&);
    SharedMemoryImpl& operator = (const SharedMemoryImpl&);

    std::size_t _size;
    int         _fd;
    char*       _address;
    SharedMemoryImpl::AccessMode _access;
    std::string _name;
    bool        _fileMapped;
    bool        _server;

};
}

char* core::io::SharedMemoryImpl::begin(){
    return _address;
}

char* core::io::SharedMemoryImpl::end(){
    return begin() + _size;
}
