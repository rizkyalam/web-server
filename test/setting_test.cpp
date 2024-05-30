#include <gtest/gtest.h>
#include "setting.hpp"

TEST(SettingTest, CheckPortConnection) {
    int port = Setting::instance().get_port();
    EXPECT_EQ(port, 80);
}

TEST(SettingTest, CheckTotalThreadPool) {
    int total = Setting::instance().get_thread_pool();
    EXPECT_EQ(total, 4);
}

TEST(SettingTest, CheckWebFilePath) {
    std::string path = Setting::instance().get_path();
    EXPECT_EQ(path, "/var/www/html");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
