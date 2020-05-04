#pragma once

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "buffer_flags.hpp"
#include "shared_memory.hpp"

namespace sharom {
namespace buffer {

class BufferImpl {
 public:
  BufferImpl(CreateOnly_t, const std::string &name, const size_t size, AccessMode mode);
  BufferImpl(OpenOnly_t, const std::string &name, AccessMode mode);
  uint64_t Size() const;

  bool Read(void *input, uint64_t input_len, uint64_t read_size, uint64_t offset = 0) const;
  std::vector<std::byte> ReadCopy(uint64_t read_size, const uint64_t offset = 0) const;

  bool Write(const void *source, uint64_t source_len, uint64_t offset = 0);
  bool Write(const std::vector<std::byte> &source, uint64_t offset = 0);

 private:
  const std::string name_;
  size_t size_;
  shared_memory::SharedMemoryStruct memory_;
  AccessMode mode_;
};

}  // namespace buffer
}  // namespace sharom