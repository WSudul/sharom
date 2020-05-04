
#include <memory>

#include "gtest/gtest.h"

#include "mutex.hpp"
#include "sharom_exception.hpp"

struct MutexTest : public testing::Test {
 public:
  MutexTest() = default;
  virtual ~MutexTest() = default;
};

TEST_F(MutexTest, SmokeTest) { ASSERT_NO_THROW(sharom::buffer::mutex::Mutex{}); }

TEST_F(MutexTest, LockAndUnlock) {
  sharom::buffer::mutex::Mutex mtx{};
  ASSERT_NO_THROW(mtx.lock());
  ASSERT_NO_THROW(mtx.unlock());
}

TEST_F(MutexTest, UnlockOnFreshMutexThrowsException) {
  sharom::buffer::mutex::Mutex mtx{};
  ASSERT_THROW(mtx.unlock(), sharom::SharomException);
}

TEST_F(MutexTest, LockTwiceThrowsException) {
  sharom::buffer::mutex::Mutex mtx{};
  ASSERT_NO_THROW(mtx.lock());
  ASSERT_THROW(mtx.lock(), sharom::SharomException); //todo : reentrant mutex on WinApi, but cna be enabled in Posix
}

TEST_F(MutexTest, UnlockTwiceThrowsException) {
  sharom::buffer::mutex::Mutex mtx{};
  ASSERT_NO_THROW(mtx.lock());
  ASSERT_NO_THROW(mtx.unlock());
  ASSERT_THROW(mtx.unlock(), sharom::SharomException);
}


TEST_F(MutexTest, TryLockAndUnlock) {
  sharom::buffer::mutex::Mutex mtx{};
  ASSERT_TRUE(mtx.try_lock());
  ASSERT_NO_THROW(mtx.unlock());
}