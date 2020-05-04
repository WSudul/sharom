#include "sharom.h"

#include <string>


#include "sharom/buffer/buffer.hpp"



int32_t sh_buffer_create(const char *name, uint64_t size)
{
sharom::buffer
};


int32_t sh_buffer_open(const char *name)
{

};

int32_t sh_buffer_get_size(const char *name)
{

};

int32_t sh_buffer_delete(const char *name)
{
    return 0;
};

int32_t sh_buffer_write(const char *name, void *in, uint64_t size)
{
    return 0;
};

int32_t sh_buffer_read_copy(const char *name, void *out, uint64_t *size)
{
    return 0;
};

int32_t sh_buffer_read_stream_next(const char *name, void **buffer, uint64_t *size_read)
{
    return 0;
};