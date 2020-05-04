#include "shared_memory.hpp"

#include <windows.h>

#include <iostream>  //todo remove couts

#include "sharom_exception.hpp"
#include "utility.hpp"

namespace sharom {
namespace buffer {
namespace shared_memory {

static HANDLE CreateFileMappingObject(const size_t size, const char *name, DWORD access_type) {
  std::cout << "CreateFileMappingObject : " << name << std::endl;

  uint32_t size_high = (size >> 32) & 0xFFFFFFFF;
  uint32_t size_low = size & 0xFFFFFFFF;

  SetLastError(ERROR_SUCCESS);
  HANDLE mem_handle = CreateFileMappingA(INVALID_HANDLE_VALUE,  // use paging file
                                         NULL,                  // default security
                                         access_type,           // read/write access
                                         size_high,             // maximum object size (high-order DWORD)
                                         size_low,              // maximum object size (low-order DWORD)
                                         name);                 // name of mapping object

  if (!mem_handle) {
    std::string msg = std::string{"Failed to create file mapping "} + name;
    std::cout << msg << std::endl;
    throw SharomException(msg);
  } else if (ERROR_ALREADY_EXISTS == GetLastError()) {
    CloseHandle(mem_handle);
    std::string msg = std::string{"Failed to create file mapping "} + name + ". Object already exists";
    std::cout << msg << std::endl;
    throw SharomException(msg);
    mem_handle = nullptr;
  }

  return mem_handle;
}

static HANDLE OpenFileMappingObject(const char *name, DWORD access_type) {
  std::cout << "OpenFileMappingObject : " << name << std::endl;

  HANDLE mem_handle = OpenFileMappingA(SECTION_QUERY | access_type | FILE_MAP_ALL_ACCESS,  // read/write access
                                       FALSE,                                              // do not inherit the name
                                       name);                                              // name of mapping object

  if (!mem_handle) {
    std::string msg = std::string{"Failed to open file mapping "} + name;
    std::cout << msg << std::endl;
    throw SharomException(msg);
  };
  std::cout << "OpenFileMappingObject : " << mem_handle << std::endl;
  return mem_handle;
}

static void *CreateMapView(HANDLE file_mapping, size_t size, const std::string &name) {
  auto map_view = MapViewOfFile(file_mapping,         // handle to map object
                                FILE_MAP_ALL_ACCESS,  // read/write permission
                                0, 0, size);

  if (!map_view) {
    std::string msg =
        std::string{"Failed to create map view of "} + name + ". Error: " + std::to_string(GetLastError());
    throw SharomException(msg);
  }

  return map_view;
}

uint32_t TranslateAccessMode(uint32_t mode) {
  mode;
  return PAGE_READWRITE;
}

SharedMemoryStruct::SharedMemoryStruct(const size_t size, const char *name, uint32_t mode)
    : handle{CreateFileMappingObject(size, name, TranslateAccessMode(mode))},
      size{size},
      map_view{CreateMapView(handle, size, name)} {};
SharedMemoryStruct::SharedMemoryStruct(const char *name, uint32_t mode)
    : handle{OpenFileMappingObject(name, TranslateAccessMode(mode))},
      size{utility::GetObjectSize(handle)},
      map_view{CreateMapView(handle, size, name)} {}
SharedMemoryStruct::~SharedMemoryStruct() {
  if (map_view) UnmapViewOfFile(map_view);

  if (handle) CloseHandle(handle);
}

}  // namespace shared_memory
}  // namespace buffer
}  // namespace sharom