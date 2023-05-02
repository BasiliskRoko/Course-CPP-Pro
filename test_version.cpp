#include <iostream>
#include "gtest/gtest.h"
#include "lib.h"



TEST(test_version, test_valid_version)
{
    EXPECT_TRUE(version() > 0);
}

int main (int argc, char ** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

