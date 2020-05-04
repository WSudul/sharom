
#ifdef unix
#include <sys/mman.h>

#endif

#include <array>
#include <memory>
#include <utility>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "buffer.hpp"
#include "sharom_exception.hpp"

namespace
{
constexpr auto kName1 = "TestName1";
constexpr auto kName2 = "TestName2";
constexpr auto kSmallSize = 32;
constexpr auto kMegaByte = 1024 * 1024;
constexpr auto kBigSize = 64 * kMegaByte;
} // namespace

#ifdef unix
struct PosixBaseTest : public testing::Test
{
public:
    PosixBaseTest()
    {
        EXPECT_EQ(-1, shm_unlink(kName1));
        EXPECT_EQ(-1, shm_unlink(kName2));
    }

    virtual ~PosixBaseTest()
    {
        EXPECT_EQ(-1, shm_unlink(kName1));
        EXPECT_EQ(-1, shm_unlink(kName2));
    }
};
struct BaseTest : public PosixBaseTest
{
};

#elif _WIN32
struct WinBaseTest : public testing::Test
{
public:
    WinBaseTest() = default;
    virtual ~WinBaseTest() = default;
};

struct BaseTest : public WinBaseTest
{
};
#endif

class BufferSmokeTest : public BaseTest
{
public:
};

TEST_F(BufferSmokeTest, Create_Destroy_SmallSize)
{
    std::unique_ptr<sharom::buffer::Buffer> buff{nullptr};

    ASSERT_NO_THROW({
        buff = std::make_unique<sharom::buffer::Buffer>(
            sharom::buffer::CreateOnly_t{}, kName1, kSmallSize, sharom::buffer::AccessMode::READ_WRITE);
    });
    ASSERT_NO_THROW(buff.reset());
}

TEST_F(BufferSmokeTest, Create_Destroy_BigSize)
{
    std::unique_ptr<sharom::buffer::Buffer> buff{nullptr};

    ASSERT_NO_THROW({
        buff = std::make_unique<sharom::buffer::Buffer>(
            sharom::buffer::CreateOnly_t{}, kName1, kBigSize, sharom::buffer::AccessMode::READ_WRITE);
    });
    ASSERT_NO_THROW(buff.reset());
}

TEST_F(BufferSmokeTest, Create_WithSameName_Fails)
{
    auto buff_1 = std::make_unique<sharom::buffer::Buffer>(
        sharom::buffer::CreateOnly_t{}, kName1, kBigSize, sharom::buffer::AccessMode::READ_WRITE);
    std::unique_ptr<sharom::buffer::Buffer> buff_2{nullptr};

    ASSERT_THROW({ buff_2 = std::make_unique<sharom::buffer::Buffer>(
                       sharom::buffer::CreateOnly_t{}, kName1, kSmallSize, sharom::buffer::AccessMode::READ_WRITE); },
                 sharom::SharomException);
}

TEST_F(BufferSmokeTest, Create_DifferentNames)
{
    std::unique_ptr<sharom::buffer::Buffer> buff_1{nullptr};
    std::unique_ptr<sharom::buffer::Buffer> buff_2{nullptr};
    ASSERT_NO_THROW({
        buff_1 = std::make_unique<sharom::buffer::Buffer>(
            sharom::buffer::CreateOnly_t{}, kName1, kSmallSize, sharom::buffer::AccessMode::READ_WRITE);
    });

    ASSERT_NO_THROW({
        buff_2 = std::make_unique<sharom::buffer::Buffer>(
            sharom::buffer::CreateOnly_t{}, kName2, kSmallSize, sharom::buffer::AccessMode::READ_WRITE);
    });
}

TEST_F(BufferSmokeTest, Open_WithoutCreate_Fails)
{
    std::unique_ptr<sharom::buffer::Buffer> buff{nullptr};

    ASSERT_THROW({
        buff = std::make_unique<sharom::buffer::Buffer>(
            sharom::buffer::OpenOnly, kName1, sharom::buffer::AccessMode::READ_WRITE);
    },
                 sharom::SharomException);
}

TEST_F(BufferSmokeTest, Create_Open_SameName)
{
    std::unique_ptr<sharom::buffer::Buffer> buff_1{nullptr};
    std::unique_ptr<sharom::buffer::Buffer> buff_2{nullptr};
    ASSERT_NO_THROW({
        buff_1 = std::make_unique<sharom::buffer::Buffer>(
            sharom::buffer::CreateOnly_t{}, kName1, kSmallSize, sharom::buffer::AccessMode::READ_WRITE);
    });

    ASSERT_NO_THROW({
        buff_2 = std::make_unique<sharom::buffer::Buffer>(
            sharom::buffer::OpenOnly_t{}, kName1, sharom::buffer::AccessMode::READ_WRITE);
    });
}

namespace
{
constexpr unsigned kBlockSize = 8;
constexpr std::byte kIncrementData[kBlockSize]{std::byte(1), std::byte(2), std::byte(3), std::byte(4), std::byte(5), std::byte(6), std::byte(7), std::byte(8)};
constexpr std::byte kDecrementData[kBlockSize]{std::byte(8), std::byte(7), std::byte(6), std::byte(5), std::byte(4), std::byte(3), std::byte(2), std::byte(1)};
} // namespace

class BufferTest : public BaseTest
{
public:
    sharom::buffer::Buffer test_obj{sharom::buffer::CreateOnly_t{}, kName1, kSmallSize, sharom::buffer::AccessMode::READ_WRITE};
};

TEST_F(BufferTest, GetSize)
{
    ASSERT_EQ(kSmallSize, test_obj.Size());
}

TEST_F(BufferTest, Write_And_Read)
{
    uint64_t offset = 0;
    ASSERT_TRUE(test_obj.Write(kIncrementData, kBlockSize, offset));
    auto read_data = test_obj.ReadCopy(kBlockSize);

    ASSERT_THAT(read_data, testing::ElementsAreArray(kIncrementData, kBlockSize));
}

TEST_F(BufferTest, Write_WithOffset)
{
    uint64_t offset = 0;
    EXPECT_TRUE(test_obj.Write(kIncrementData, kBlockSize, offset));
    offset += kBlockSize;
    EXPECT_TRUE(test_obj.Write(kIncrementData, kBlockSize, offset));
    offset += kBlockSize;
    EXPECT_TRUE(test_obj.Write(kIncrementData, kBlockSize, offset));
    offset += kBlockSize;
    EXPECT_TRUE(test_obj.Write(kIncrementData, kBlockSize, offset));
    offset += kBlockSize; //offset equivalent to size
    EXPECT_FALSE(test_obj.Write(kIncrementData, kBlockSize, offset));

    offset = kSmallSize + 1; //offset 1 past size
    EXPECT_FALSE(test_obj.Write(kIncrementData, kBlockSize, offset));

    offset = 0;
    std::array<std::byte, kSmallSize * 2> too_big_data{std::byte{42}};
    EXPECT_FALSE(test_obj.Write(too_big_data.data(), too_big_data.size(), offset));

    offset = kSmallSize - (kBlockSize / 2); //data will not fit
    EXPECT_FALSE(test_obj.Write(kIncrementData, kBlockSize, offset));
}

//returns page size on Windows (4kB) instead of expected size
TEST_F(BufferTest, DISABLED_OpenExistingBuffer_GetSize)
{
    sharom::buffer::Buffer buff{
        sharom::buffer::OpenOnly_t{}, kName1, sharom::buffer::AccessMode::READ_WRITE};
    ASSERT_EQ(kSmallSize, buff.Size());
}


TEST_F(BufferTest, OpenExistingBuffer_Wirte_And_Read)
{
    sharom::buffer::Buffer buff{
        sharom::buffer::OpenOnly_t{}, kName1, sharom::buffer::AccessMode::READ_WRITE};

    EXPECT_TRUE(test_obj.Write(kIncrementData, kBlockSize));
    auto read_data_1 = buff.ReadCopy(kBlockSize);
    EXPECT_THAT(read_data_1, testing::ElementsAreArray(kIncrementData, kBlockSize));

    EXPECT_TRUE(buff.Write(kDecrementData, kBlockSize));
    auto read_data_2 = test_obj.ReadCopy(kBlockSize);
    EXPECT_THAT(read_data_2, testing::ElementsAreArray(kDecrementData, kBlockSize));
}