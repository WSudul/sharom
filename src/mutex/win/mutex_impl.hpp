#pragma once

#include <windows.h>

#include <cstring>
#include <string>

namespace sharom {
namespace buffer {
namespace mutex {

constexpr char kMutexNamePrefix[]{"Global\\shrm.ipc.mtx."};
constexpr auto kPrefixLen = sizeof(kMutexNamePrefix);
constexpr auto kNameLen = MAX_PATH - kPrefixLen;

class MutexImpl {
 public:
  MutexImpl();
  ~MutexImpl();
  void lock();
  bool try_lock();
  void unlock();

 private:
  char name_[kNameLen]{'\0'};
  HANDLE mtx_{NULL};
};

}  // namespace mutex
}  // namespace buffer
}  // namespace sharom