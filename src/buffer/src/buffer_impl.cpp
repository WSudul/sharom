#include "buffer_impl.hpp"

#include <cstring>
#include <iostream>  //todo remove it
#include <string>

#if defined(MSVC)
#pragma warning(disable : 4996)
#endif

namespace sharom {
namespace buffer {

BufferImpl::BufferImpl(CreateOnly_t, const std::string &name, const size_t size, AccessMode mode)
    : name_{name},
      size_{size},
      mode_{mode},
      memory_{size, name.c_str(), shared_memory::TranslateAccessMode(to_underlying(mode_))} {}

BufferImpl::BufferImpl(OpenOnly_t, const std::string &name, AccessMode mode)
    : name_{name}, mode_{mode}, memory_{name.c_str(), shared_memory::TranslateAccessMode(to_underlying(mode_))} {
  size_ = memory_.size;
}

uint64_t BufferImpl::Size() const { return memory_.size; }

bool BufferImpl::Read(void *input, uint64_t input_len, uint64_t read_size, uint64_t offset) const {
  auto end = read_size + offset;
  if ((offset > size_) || (end > size_)) return false;

  void *source = reinterpret_cast<char *>(memory_.map_view) + offset;
  memcpy(input, source, read_size);
  return true;
}
std::vector<std::byte> BufferImpl::ReadCopy(uint64_t read_size, const uint64_t offset) const {
  auto end = read_size + offset;
  if ((offset > size_) || (end > size_)) {
    return {};
  }
  std::vector<std::byte> output(read_size);

  void *source = reinterpret_cast<char *>(memory_.map_view) + offset;
  memcpy(output.data(), source, read_size);
  return output;
}

bool BufferImpl::Write(const void *data, uint64_t data_len, uint64_t offset) {
  if (data_len + offset > size_) {
    std::cout << "bad data_len and offset\t" << data_len << " , " << offset << "\tsize_: " << size_ << std::endl;
    return false;
  }

  void *dest = reinterpret_cast<char *>(memory_.map_view) + offset;
  memcpy(dest, data, data_len);
  return true;
}

bool BufferImpl::Write(const std::vector<std::byte> &data, uint64_t offset) {
  return Write(data.data(), data.size(), offset);
}

}  // namespace buffer
}  // namespace sharom

#if defined(MSVC)
#pragma warning(default : 4996)
#endif
