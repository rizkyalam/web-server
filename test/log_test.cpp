#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "log.hpp"

std::string get_last_log() {
    std::string logPath = "/var/log/syslog";
    std::unique_ptr<std::ifstream> file = std::make_unique<std::ifstream>(logPath);
        
    std::string line;
    std::string lastLine;
    
    while (std::getline(*file, line)) {
        lastLine = line;
    }
    
    file->close();

    return lastLine;
}

using namespace testing;

TEST(LogTest, MatchesInfoLog) {
    Log::instance().info("Testing info log euy");

    std::string lastLog = get_last_log();
    std::string message = ".*INFO -> Testing info log euy";

    EXPECT_THAT(lastLog, MatchesRegex(message));
}

TEST(LogTest, MatchesWarningLog) {
    Log::instance().warn("Kade ieu mah", __LINE__, __FUNCTION__);

    std::string lastLog = get_last_log();
    std::string message = ".*WARN \[line [0-9]+\]:.*\(\) -> Kade ieu mah";

    EXPECT_THAT(lastLog, MatchesRegex(message));
}

TEST(LogTest, MatchesErrorLog) {
    Log::instance().error("Hadeuh error wae euy", __LINE__, __FUNCTION__);

    std::string lastLog = get_last_log();
    std::string message = ".*ERROR \[line [0-9]+\]:.*\(\) -> Hadeuh error wae euy";

    EXPECT_THAT(lastLog, MatchesRegex(message));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
