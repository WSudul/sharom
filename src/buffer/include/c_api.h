// C compatibile interface for buffer
#pragma once

#include <cstddef>
#include <cstdint>

#include "api_symbol.h"

#ifdef __cplusplus
extern "C" {

struct SHAROM_API Buffer_t {};

enum AccessMode_t { READ_ONLY = 0x1, WRITE_ONLY = 0x2, READ_WRITE = READ_ONLY | WRITE_ONLY };

SHAROM_API Buffer_t* sharom_buffer_create(const char* name, const char* size_t, AccessMode_t mode);
SHAROM_API void sharom_buffer_delete(Buffer_t* buffer);

SHAROM_API Buffer_t* sharom_buffer_open(const char* name, AccessMode_t mode);

SHAROM_API uint64_t sharom_buffer_size(Buffer_t* buffer);
SHAROM_API bool sharom_buffer_read(Buffer_t* buffer, void* input, uint64_t input_len, uint64_t read_size,
                                   uint64_t offset);
SHAROM_API bool sharom_buffer_write(Buffer_t* buffer, const void* source, uint64_t source_len, uint64_t offset);
}

#endif