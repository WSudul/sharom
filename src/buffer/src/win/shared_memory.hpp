#pragma once

#ifdef _WIN32

#include <windows.h>  //todo remove it

#include <cstdint>
#include <string>

namespace sharom {
namespace buffer {
namespace shared_memory {

uint32_t TranslateAccessMode(uint32_t mode);

struct SharedMemoryStruct {
  SharedMemoryStruct(const size_t size, const char *name, uint32_t mode);
  SharedMemoryStruct(const char *name, uint32_t mode);
  ~SharedMemoryStruct();

  HANDLE handle;
  size_t size{0};
  PVOID map_view;
};

}  // namespace shared_memory
}  // namespace buffer
}  // namespace sharom
#endif  //_WIN32