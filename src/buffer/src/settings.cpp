#include "settings.hpp"

#include "system_info.hpp"

namespace sharom {

namespace buffer {

uint64_t ReadPageSize() { return sharom::utility::system::ReadPageSize(); }

}  // namespace buffer
}  // namespace sharom