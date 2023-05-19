#include "lib.h"
#include "gtest/gtest.h"
#include <iostream>

class IPTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // q0_ remains empty
        ip_pool.push_back(split("113.162.145.156", '.'));
        ip_pool.push_back(split("157.39.22.224", '.'));
        ip_pool.push_back(split("79.180.73.190", '.'));
        ip_pool.push_back(split("1.29.168.152", '.'));
        ip_pool.push_back(split("46.182.19.219", '.'));
        ip_pool.push_back(split("154.160.1.180", '.'));
        ip_pool.push_back(split("168.195.231.1", '.'));
        ip_pool.push_back(split("46.70.113.73", '.'));
        ip_pool.push_back(split("185.84.46.70", '.'));
        ip_pool.push_back(split("89.46.70.220", '.'));
        ip_pool.push_back(split("185.84.47.70", '.'));
        ip_pool.push_back(split("46.70.225.39", '.'));
    }

    // void TearDown() override {}
  public:
    VectorVectorString ip_pool;
};

TEST_F(IPTest, test_sort_desc) {
    sortIP(ip_pool, false);
    VectorString v = ip_pool.at(0);
    EXPECT_STREQ(ip_pool.begin()->begin()->c_str(), "185");
    EXPECT_STREQ(ip_pool.begin()->at(2).c_str(), "47");
    EXPECT_TRUE(atoi(ip_pool.rbegin()->begin()->c_str()) == 1);
}

TEST_F(IPTest, test_value_1) {
    testing::internal::CaptureStdout();
    auto finder1 = [value = 1](auto a) { return value == atoi(a.cbegin()->c_str()); };
    printOn(ip_pool, finder1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(output.c_str(), "1.29.168.152\n");
}

TEST_F(IPTest, test_value_46_70) {
    testing::internal::CaptureStdout();
    auto finder2 = [value1 = 46, value2 = 70](VectorString a) { return value1 == atoi(a.at(0).c_str()) && value2 == atoi(a.at(1).c_str()); };
    printOn(ip_pool, finder2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(output.c_str(), "46.70.113.73\n46.70.225.39\n");
}

TEST_F(IPTest, test_value_46) {
    testing::internal::CaptureStdout();
    filter_any(ip_pool, 46);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(output.c_str(), "46.182.19.219\n46.70.113.73\n185.84.46.70\n89.46.70.220\n46.70.225.39\n");
}

TEST_F(IPTest, test_value_46_sort_desc) {
    testing::internal::CaptureStdout();
    sortIP(ip_pool, false);
    filter_any(ip_pool, 46);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(output.c_str(), "185.84.46.70\n89.46.70.220\n46.182.19.219\n46.70.225.39\n46.70.113.73\n");
}

TEST(test_version, test_valid_version) {
    EXPECT_TRUE(version() > 0);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
