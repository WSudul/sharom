#include "mutex.hpp"

#include "mutex_impl.hpp"

namespace sharom {
namespace buffer {
namespace mutex {

Mutex::Mutex() : mutex_impl_{new MutexImpl, [](MutexImpl* mtx) { delete mtx; }} {}

void Mutex::lock() { mutex_impl_->lock(); }
bool Mutex::try_lock() { return mutex_impl_->try_lock(); }
void Mutex::unlock() { mutex_impl_->unlock(); }

}  // namespace mutex
}  // namespace buffer
}  // namespace sharom