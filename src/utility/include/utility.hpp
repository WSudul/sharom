#pragma once

#include <cstdint>

#ifdef _WIN32
#include <windows.h>
#include <winnt.h>

#endif //_WIN32

#ifdef __linux__
using file_handle_t = int;
#elif _WIN32
using file_handle_t = HANDLE;
#endif

namespace sharom
{
namespace utility
{

uint64_t GetObjectSize(file_handle_t file_handle);

} //namespace utility
} // namespace sharom
