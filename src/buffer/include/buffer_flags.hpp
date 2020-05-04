#pragma once

#include <cstdint>
#include <type_traits>

namespace sharom {
namespace buffer {

enum class AccessMode : uint32_t {
  READ_ONLY = 0x1,
  WRITE_ONLY = 0x2,
  READ_WRITE = READ_ONLY | WRITE_ONLY,
};

template <typename E>
constexpr auto to_underlying(E e) noexcept {
  return static_cast<std::underlying_type_t<E>>(e);
}

struct CreateOnly_t {};
struct OpenOnly_t {};

static const CreateOnly_t CreateOnly{};
static const OpenOnly_t OpenOnly{};

}  // namespace buffer
}  // namespace sharom