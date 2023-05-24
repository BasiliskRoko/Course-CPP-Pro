#include "lib.h"
#include "myvector.h"
#include "gtest/gtest.h"
#include <iostream>

class HomeWorkTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
    }

    // void TearDown() override {}
public:
};

TEST_F(HomeWorkTest, factorial_1)
{
    auto index = 1;
    EXPECT_EQ(factorial(index), 1);
}

TEST_F(HomeWorkTest, factorial_5)
{
    auto index = 5;
    EXPECT_EQ(factorial(index), 1 * 2 * 3 * 4 * 5);
}
TEST_F(HomeWorkTest, my_vector_2)
{
    my_vector<int> vec(2);
    for (int index = 0; index < 2; ++index)
    {
        vec.push_back(index);
    }
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec.capacity(), 2);

    std::for_each(vec.begin(), vec.end(), [index = 0](auto &res) mutable -> void
                  { EXPECT_EQ(res, index); index++; });
}

TEST_F(HomeWorkTest, my_vector_3)
{
    my_vector<int> vec(3);
    for (int index = 0; index < 4; ++index)
    {
        vec.push_back(index);
    }
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec.capacity(), 7);
    std::for_each(vec.begin(), vec.end(), [index = 0](auto &res) mutable -> void
                  { EXPECT_EQ(res, index); index++; });
}

TEST_F(HomeWorkTest, map_10)
{
    using MapWithAlloc = std::map<int, int, std::less<int>, std_11_simple_allocator<std::pair<const int, int>>>;
    MapWithAlloc m(10);

    for (int index = 0; index < 10; ++index)
    {
        m.insert({index, factorial<decltype(index)>(index)});
    }

    EXPECT_EQ(m.get_allocator().PoolIncrement, 10);

    EXPECT_EQ(m.get_allocator().PoolSize, 15);
    std::for_each(m.begin(), m.end(), [index = 0](const auto &mapPair) mutable -> void
                  { EXPECT_EQ(mapPair.first, index);
                  EXPECT_EQ(mapPair.second, factorial<decltype(index)>(index)); index++; });
}

TEST(test_version, test_valid_version)
{
    EXPECT_TRUE(version() > 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
