#include "SharedMemory.h"
#include <stdexcept>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>

using namespace core::io;

SharedMemoryImpl::SharedMemoryImpl(const std::string& name, std::size_t size, SharedMemoryImpl::AccessMode mode, const void* addrHint, bool server):
    _size(size),
    _fd(-1),
    _address(0),
    _access(mode),
    _name("/"),
    _fileMapped(false),
    _server(server)
{
    _name.append(name);

    int flags = _server ? O_CREAT : 0;
    if (_access == SharedMemoryImpl::AM_WRITE)
        flags |= O_RDWR;
    else
        flags |= O_RDONLY;

    // open the shared memory segment
    _fd = ::shm_open(_name.c_str(), flags, S_IRUSR | S_IWUSR);
    if (_fd == -1)
        throw std::runtime_error("Cannot create shared memory object:" + _name);

    // now set the correct size for the segment
    if (_server && -1 == ::ftruncate(_fd, size))
    {
        ::close(_fd);
        _fd = -1;
        ::shm_unlink(_name.c_str());
        throw std::runtime_error(std::string("Cannot resize shared memory object" + _name).c_str());
    }
    map(addrHint);
}


SharedMemoryImpl::SharedMemoryImpl(const std::filesystem::path& file, SharedMemoryImpl::AccessMode mode, const void* addrHint):
    _size(0),
    _fd(-1),
    _address(0),
    _access(mode),
    _name(file),
    _fileMapped(true),
    _server(false)
{
    if (!std::filesystem::exists(file) || 
        std::filesystem::file_type::regular != std::filesystem::status(file).type()){
        throw std::runtime_error(file);
    }

    _size = std::filesystem::file_size(file);
    int flag = O_RDONLY;
    if (mode == SharedMemoryImpl::AM_WRITE)
        flag = O_RDWR;
    _fd = ::open(_name.c_str(), flag);
    if (-1 == _fd)
        throw std::runtime_error(std::string("Cannot open memory mapped file" + _name).c_str());

    map(addrHint);
}


SharedMemoryImpl::~SharedMemoryImpl()
{
    unmap();
    close();
}


void SharedMemoryImpl::map(const void* addrHint)
{
    int access = PROT_READ;
    if (_access == SharedMemoryImpl::AM_WRITE)
        access |= PROT_WRITE;

    void* addr = ::mmap(const_cast<void*>(addrHint), _size, access, MAP_SHARED, _fd, 0);
    if (addr == MAP_FAILED)
        throw std::runtime_error("Cannot map file into shared memory" + _name);

    _address = static_cast<char*>(addr);
}


void SharedMemoryImpl::unmap()
{
    if (_address)
    {
        ::munmap(_address, _size);
    }
}


void SharedMemoryImpl::close()
{
    if (_fd != -1)
    {
        ::close(_fd);
        _fd = -1;
    }
    if (!_fileMapped && _server)
    {
        ::shm_unlink(_name.c_str());
    }
}
