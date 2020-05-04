#ifndef SHAROM_BUFFER_BUFFER_H_
#define SHAROM_BUFFER_BUFFER_H_

#include <cstddef>
#include <functional>
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "buffer_flags.hpp"

namespace sharom {
namespace buffer {

// forward decl
class BufferImpl;

class Buffer {
 public:
  Buffer(CreateOnly_t, const std::string &name, const size_t size, AccessMode mode);
  Buffer(OpenOnly_t, const std::string &name, AccessMode mode);

  uint64_t Size() const;

  bool Read(void *input, uint64_t input_len, uint64_t read_size, uint64_t offset = 0) const;
  std::vector<std::byte> ReadCopy(uint64_t read_size, const uint64_t offset = 0) const;

  bool Write(const void *source, uint64_t source_len, uint64_t offset = 0);
  bool Write(const std::vector<std::byte> &source, uint64_t offset = 0);

 private:
  std::unique_ptr<BufferImpl, std::function<void(BufferImpl *)>> impl_;
};
}  // namespace buffer
}  // namespace sharom
#endif  // SHAROM_BUFFER_BUFFER_H_
