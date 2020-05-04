#include "system_info.hpp"


#ifdef _WIN32
#include <windows.h>
#endif

//#include "sysinfoapi.h"




#ifdef unix
#include <unistd.h>

#endif

namespace sharom
{
namespace utility
{
namespace system
{

uint64_t ReadPageSize()
{
    #ifdef _WIN32
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    return sys_info.dwPageSize;
    #elif unix
    auto res= sysconf(_SC_PAGESIZE);
    if(-1 == res){
        //todo handle this
    }
    return res;

    #endif
}
} // namespace system
} // namespace utility
} // namespace sharom