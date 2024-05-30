#include "cmd_line_parser.hpp"

#include <chrono>
#include <thread>
#include <libconfig.h++>
#include "log.hpp"
#include "daemon.hpp"

CommandLineParser::CommandLineParser(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        this->_tokens.push_back(static_cast<std::string>(argv[i]));
    }
}

const std::string &CommandLineParser::get_option_value(const std::string &option) const {
    auto it = std::find(this->_tokens.begin(), this->_tokens.end(), option);

    if (it != this->_tokens.end() && ++it != this->_tokens.end()) return *it;

    static const std::string emptyString = "";
    return emptyString;
}

bool CommandLineParser::is_option_exist(const std::string &option) const {
    auto it = std::find(this->_tokens.begin(), this->_tokens.end(), option);
    return it != this->_tokens.end();
}

void CommandLineParser::config_service() {
    const std::string configFileName = this->get_option_value("--config");

    const std::string infoName = "Config file name" + configFileName;
    Log::instance().info(infoName);

    libconfig::Config config;
    config.readFile(configFileName.c_str());

    std::string test;
    config.lookupValue("test", test);

    const std::string infoOption = "Config option test = " + test;
    Log::instance().info(infoOption);
}

void CommandLineParser::help() {
    std::cout << "Simple web server linux daemon" << std::endl;
    std::cout << "Creator: rizkyalam <http://github.com/rizkyalam>\n" << std::endl;
    std::cout << "Pattern selection:" << std::endl;
    std::cout << "--run\t\t\tRun the server" << std::endl;
    std::cout << "--run --config <path>\tRun the server with daemon service configuration" << std::endl;
    std::cout << "--help\t\t\tDisplay this help text\n" << std::endl;
}
