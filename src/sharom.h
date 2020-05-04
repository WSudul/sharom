
#include <cstdint>

#include "api_symbol.h"

#define SHAROM_API
#define SHAROM_SYMNBOL_EXPORTS

#ifdef __cplusplus
extern "C" {
#endif
SHAROM_API int32_t sh_buffer_create(const char* name,uint64_t size);

SHAROM_API int32_t sh_buffer_open(const char* name);

SHAROM_API int32_t sh_buffer_get_size(const char* name);

SHAROM_API int32_t sh_buffer_delete(const char* name);

SHAROM_API int32_t sh_buffer_write(const char* name,void* in,uint64_t size);

SHAROM_API int32_t sh_buffer_read_copy(const char* name, void* out, uint64_t* size);

SHAROM_API int32_t sh_buffer_read_stream_next(const char* name,void** buffer, uint64_t* size_read);


#ifdef __cplusplus
}
#endif