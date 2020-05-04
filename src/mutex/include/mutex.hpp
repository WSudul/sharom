#pragma once

#include <functional>
#include <memory>

namespace sharom {
namespace buffer {
namespace mutex {

class MutexImpl;

class Mutex {
 public:
  Mutex();
  void lock();
  bool try_lock();
  void unlock();

 private:
  std::unique_ptr<MutexImpl, std::function<void(MutexImpl*)>> mutex_impl_;
};

}  // namespace mutex
}  // namespace buffer
}  // namespace sharom