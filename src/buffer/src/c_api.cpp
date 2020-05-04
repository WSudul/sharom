#include "c_api.h"

#include "buffer.hpp"
#include "buffer_flags.hpp"
#include "sharom_exception.hpp"

static sharom::buffer::Buffer* ToBuffer(Buffer_t* b) { return reinterpret_cast<sharom::buffer::Buffer*>(b); }

static Buffer_t* ToBufferCType(sharom::buffer::Buffer* b) { return reinterpret_cast<Buffer_t*>(b); }

static sharom::buffer::AccessMode TranslateMode(AccessMode_t mode) {
  sharom::buffer::AccessMode internal_mode;
  switch (mode) {
    case AccessMode_t::READ_ONLY:
      internal_mode = sharom::buffer::AccessMode::READ_ONLY;
    case AccessMode_t::WRITE_ONLY:
      internal_mode = sharom::buffer::AccessMode::WRITE_ONLY;
    case AccessMode_t::READ_WRITE:
      internal_mode = sharom::buffer::AccessMode::READ_WRITE;
  }
  return internal_mode;
}

Buffer_t* sharom_buffer_create(const char* name, size_t size, AccessMode_t mode) {
  try {
    auto internal_mode = TranslateMode(mode);
    auto buf = new sharom::buffer::Buffer(sharom::buffer::CreateOnly, name, size, internal_mode);
    return ToBufferCType(buf);
  } catch (sharom::SharomException& /*sharom_ex*/) {
    // todo signal failure via C api
    return nullptr;
  }
}

void sharom_buffer_delete(Buffer_t* buffer) {
  auto buf = ToBuffer(buffer);
  delete buf;
}

Buffer_t* sharom_buffer_open(const char* name, AccessMode_t mode) {
  try {
    auto internal_mode = TranslateMode(mode);
    auto buf = new sharom::buffer::Buffer(sharom::buffer::OpenOnly, name, sharom::buffer::AccessMode::READ_WRITE);

    return ToBufferCType(buf);
  } catch (sharom::SharomException& /*sharom_ex*/) {
    // todo signal failure via C api
    return nullptr;
  }
}

uint64_t sharom_buffer_size(Buffer_t* buffer) {
  auto buf = ToBuffer(buffer);
  return buf->Size();
}

bool sharom_buffer_read(Buffer_t* buffer, void* input, uint64_t input_len, uint64_t read_size, uint64_t offset) {
  auto buf = ToBuffer(buffer);
  return buf->Read(input, input_len, read_size, offset);
}

bool sharom_buffer_write(Buffer_t* buffer, const void* source, uint64_t source_len, uint64_t offset) {
  auto buf = ToBuffer(buffer);
  return buf->Write(source, source_len, offset);
}
