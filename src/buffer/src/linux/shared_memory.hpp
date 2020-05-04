#pragma once

#ifdef __linux__

#include <string>

#include "sharom_exception.hpp"

namespace sharom {
namespace buffer {
namespace shared_memory {

uint32_t TranslateAccessMode(uint32_t mode);

struct SharedMemoryStruct {
 public:
  SharedMemoryStruct(const size_t size, const char *name, uint32_t mode);
  SharedMemoryStruct(const char *name, uint32_t mode);
  ~SharedMemoryStruct();

  std::string name{};
  int handle{0};
  size_t size{0};
  void *map_view{nullptr};
};

}  // namespace shared_memory
}  // namespace buffer
}  // namespace sharom
#endif