#include "shared_memory.hpp"

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream> //todo remove couts
#include <string>

#include "utility.hpp"

namespace sharom
{
namespace buffer
{
namespace shared_memory
{

static int CreateFileMappingObject(size_t size, const char *name, int access_mode)
{

    constexpr int kCreateOnlyFlag = O_CREAT | O_EXCL;
    constexpr int kReadWriteFlag = O_RDWR;
    int fd = shm_open(name, kCreateOnlyFlag | kReadWriteFlag, access_mode);
    if (-1 == fd)
    {
        std::string msg = std::string{"Failed to create file mapping "} + name + "\tsize\t" + std::to_string(size) + "\terrno " + std::to_string(errno);
        std::cout << msg << std::endl;
        throw SharomException(msg);
    }

    if (-1 == ftruncate(fd, size))
    {
        //failure
        std::string msg = std::string{"Failed to resize file mapping "} + name + "\tsize\t" + std::to_string(size) + "\terrno " + std::to_string(errno);
        std::cout << msg << std::endl;
        throw SharomException(msg);
    }
    return fd;
}

static int OpenFileMappingObject(const char *name, int access_mode)
{
    constexpr int kReadWriteFlag = O_RDWR;
    int fd = shm_open(name, kReadWriteFlag, access_mode);
    if (-1 == fd)
    {
        std::string msg = std::string{"Failed to open file mapping "} + name + "\terrno " + std::to_string(errno);
        std::cout << msg << std::endl;
        throw SharomException(msg);
    }
    return fd;
}

static void *CreateMapView(int fd, size_t size, const char *name)
{
    constexpr auto kOffset = 0;
    constexpr int flags = MAP_SHARED;
    constexpr int kProtection = PROT_READ | PROT_WRITE;
    void *map_view = mmap(nullptr, size, kProtection, flags, fd, kOffset);

    if (!map_view)
    {
        std::string msg = std::string{"Failed to create map view of "} + name + "\tsize\t" + std::to_string(size);
        std::cout << msg << std::endl;
        throw SharomException(msg);
    }

    return map_view;
}

uint32_t TranslateAccessMode(uint32_t mode)
{
    mode;
    //equivalent to 606
    constexpr int kOpenModeFlags = S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH;

    return kOpenModeFlags;
}

SharedMemoryStruct::SharedMemoryStruct(const size_t size, const char *name, uint32_t mode) : name{name},
                                                                                             handle{CreateFileMappingObject(size, name, TranslateAccessMode(mode))},
                                                                                             size{size},
                                                                                             map_view{CreateMapView(handle, size, name)} {};
SharedMemoryStruct::SharedMemoryStruct(const char *name, uint32_t mode) : name{name}, handle{OpenFileMappingObject(name, TranslateAccessMode(mode))},
                                                                          size{utility::GetObjectSize(handle)},
                                                                          map_view{CreateMapView(handle, size, name)}
{
}
SharedMemoryStruct::~SharedMemoryStruct()
{
    if (map_view)
    {
        munmap(map_view, size);
    }
    if (0 != handle)
    {
        shm_unlink(name.c_str());
    }
}

} // namespace shared_memory
} // namespace buffer
} // namespace sharom