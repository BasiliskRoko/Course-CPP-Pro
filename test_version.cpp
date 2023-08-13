#include "lib.h"
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
/*
TEST_F(HomeWorkTest, factorial_1)
{
    // auto index = 1;
    //  EXPECT_EQ(factorial(index), 1);
}
*/
TEST(test_version, test_valid_version)
{
    EXPECT_TRUE(version() > 0);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
