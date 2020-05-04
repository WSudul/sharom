#include "utility.hpp"

#ifdef _WIN32
#include <windows.h>
#include <libloaderapi.h>

#elif __linux__

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include <cstdint>
#include <cerrno>
#include <string>
#include <iostream>


#include "sharom_exception.hpp"

namespace sharom
{
namespace utility
{

#ifdef _WIN32

enum section_information_class
{
    section_basic_information,
    section_image_information
};

struct interprocess_section_basic_information
{
    PVOID *base_address;
    ULONG section_attributes;
    LARGE_INTEGER section_size;
};
typedef DWORD(__stdcall *NtQuerySection_t)(void *, section_information_class, interprocess_section_basic_information *pinfo, unsigned long info_size, unsigned long *ret_len);

#endif

static bool TryToReadObjectSize(file_handle_t file_handle, uint64_t &size)
{
#ifdef _WIN32
    HMODULE hL = LoadLibraryA("Ntdll.dll");
    NtQuerySection_t NtQuerySection = reinterpret_cast<NtQuerySection_t>(GetProcAddress(hL, "NtQuerySection"));
std::cout<<"TryToReadObjectSize \n";
    interprocess_section_basic_information info;

    auto ntstatus =
        NtQuerySection(file_handle, section_basic_information, &info, sizeof(info), 0);
   
    if(ntstatus>=0){
         size = info.section_size.QuadPart;
    }
    return !ntstatus;

#elif __linux__
    struct stat stat_struct;
    if (0 == fstat(file_handle, &stat_struct))
    {
        size = stat_struct.st_size;
        return true;
    }
    else
        return false;
#endif
}


uint64_t GetObjectSize(file_handle_t file_handle)
{
    uint64_t output{};
    if (TryToReadObjectSize(file_handle, output))
        return output;
    else
    {
        std::string msg = std::string{"Query to object size has failed. Errno: "} + std::to_string(errno);
        std::cout << msg << std::endl;
        throw SharomException(msg);
    }
}

} // namespace utilitiy
} // namespace sharom