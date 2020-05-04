#include "mutex_impl.hpp"

#include <array>
#include <chrono>

#include "sharom_exception.hpp"

namespace sharom {
namespace buffer {
namespace mutex {

class sync_id {
 public:
  typedef __int64 internal_type;

 private:
  void* k;
  internal_type x;
};

using Stamp = std::array<char, 2 * sizeof(uint64_t) + 1>;

static Stamp ToHex(const uint64_t& input) {
  static const char hex_digits[] = "0123456789ABCDEF";
  Stamp output{};

  union InputUnion {
    uint64_t input;
    unsigned char array[sizeof(uint64_t)];
  };
  InputUnion in{input};

  unsigned output_counter = 0;
  for (auto i = 0; i < sizeof(uint64_t); ++i) {
    output[output_counter++] = (hex_digits[in.array[i] & 0xF0 >> 4]);
    output[output_counter++] = (hex_digits[in.array[i] & 0x0F]);
  }
  output[output_counter] = '\0';

  return output;
}
static auto generate_stamp(void) {
  auto duration = std::chrono::system_clock::now().time_since_epoch();
  uint64_t microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
  return microseconds;
}

MutexImpl::MutexImpl() {
  std::strcpy(name_, kMutexNamePrefix);
  std::strcpy(&name_[kPrefixLen], ToHex(generate_stamp()).data());

  mtx_ = CreateMutexA(NULL, FALSE, name_);  // OpenMutexW ?
  if (NULL == mtx_) {
    const std::string msg{"Unable to create mutex"};
    throw SharomException(msg);
  }
};
MutexImpl::~MutexImpl() { CloseHandle(mtx_); };

void MutexImpl::lock() {
  auto res = WaitForSingleObject(mtx_, INFINITE);
  // todo
  switch (res) {
    case WAIT_OBJECT_0:
      break;
    case WAIT_FAILED: {  // error
      const std::string msg{"Mutex lock failed"};
      throw SharomException(msg);
    } break;
    case WAIT_ABANDONED: {
      // handle abandoned state
      const std::string msg{"Mutex is abandonded"};
      throw SharomException(msg);
    } break;
    default:
      break;
  }
};

bool MutexImpl::try_lock() {
  auto kNoWait = 0;
  auto res = WaitForSingleObject(mtx_, kNoWait);

  return WAIT_OBJECT_0 == res;
}

void MutexImpl::unlock() { 
  if(!ReleaseMutex(mtx_)){
      const std::string msg{"Mutex unlock failed"};
      throw SharomException(msg);
  } }

}  // namespace mutex
}  // namespace buffer
}  // namespace sharom