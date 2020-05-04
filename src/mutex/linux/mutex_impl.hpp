#pragma once

#include <pthread.h>
namespace sharom {
namespace buffer {
namespace mutex {

class MutexImpl {
 public:
  MutexImpl(bool robust = true,bool recursive=true);
  ~MutexImpl();
  void lock();

  bool try_lock();
  void unlock();

 private:
  pthread_mutex_t mtx_;
};

}  // namespace mutex
}  // namespace buffer
}  // namespace sharom