#include "buffer.hpp"

#include <cstring>

#include "buffer_impl.hpp"
#include "sharom_exception.hpp"
#include "utility.hpp"

namespace sharom {
namespace buffer {

Buffer::Buffer(CreateOnly_t, const std::string &name, const size_t size, AccessMode mode)
    : impl_{new BufferImpl(CreateOnly, name, size, mode), [](BufferImpl *b) { delete b; }} {}
Buffer::Buffer(OpenOnly_t, const std::string &name, AccessMode mode)
    : impl_{new BufferImpl(OpenOnly, name, mode), [](BufferImpl *b) { delete b; }} {}

uint64_t Buffer::Size() const { return impl_->Size(); }

bool Buffer::Read(void *input, uint64_t input_len, uint64_t read_size, uint64_t offset) const {
  return impl_->Read(input, input_len, read_size, offset);
}
std::vector<std::byte> Buffer::ReadCopy(uint64_t read_size, const uint64_t offset) const {
  return impl_->ReadCopy(read_size, offset);
}

bool Buffer::Write(const void *data, uint64_t data_len, uint64_t offset) {
  return impl_->Write(data, data_len, offset);
}

bool Buffer::Write(const std::vector<std::byte> &data, uint64_t offset) { return impl_->Write(data, offset); }

}  // namespace buffer
}  // namespace sharom