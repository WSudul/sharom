#include "mutex_impl.hpp"

namespace sharom {
namespace buffer {
namespace mutex {

MutexImpl::MutexImpl(bool robust, bool recursive) {
  pthread_mutexattr_t attributes;
  pthread_mutexattr_init(&attributes);
  pthread_mutexattr_setpshared(&attributes, PTHREAD_PROCESS_SHARED);
  if (robust) {
    pthread_mutexattr_setrobust(&attributes,PTHREAD_MUTEX_ROBUST);
  }
  if (recursive) {
   pthread_mutexattr_settype(&attributes,PTHREAD_MUTEX_RECURSIVE);
  }

  pthread_mutex_init(&mtx_, &attributes);

  pthread_mutexattr_destroy(&attributes);
};
MutexImpl::~MutexImpl() { pthread_mutex_destroy(&mtx_); }

void MutexImpl::lock() {
  if (!pthread_mutex_lock(&mtx_)) {
    // error handling
  }
};

bool MutexImpl::try_lock() {
  if (!pthread_mutex_trylock(&mtx_)) {
    // error handling
    return false;
  }

  return true;
}

void MutexImpl::unlock() {
  if (!pthread_mutex_unlock(&mtx_)) {
    // error handling
  };
}

}  // namespace mutex
}  // namespace buffer
}  // namespace sharom