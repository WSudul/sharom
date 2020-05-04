#pragma once

#include <cstdint>

namespace sharom {

namespace buffer {

// Returns OS memory page size in bytes
// Multiplicity of this value should be used for creating Buffer objects
// The exact size depends on underlying CPU architecture, OS support and configuration
// Usually it will return 4096 (4kB) for Windows,Linux,Macs on x86 architecture, but might also
// return 4096 (4kB) or 16384 (16kB) on ARM devices
uint64_t ReadPageSize();

}  // namespace buffer
}  // namespace sharom