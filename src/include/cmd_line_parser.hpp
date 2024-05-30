#pragma once

#include <iostream>
#include <vector>

class CommandLineParser {
    private:
        std::vector<std::string> _tokens;

    public:
        CommandLineParser(int argc, char **argv);
        const std::string &get_option_value(const std::string &option) const;
        bool is_option_exist(const std::string &option) const;
        void config_service();
        void help();
};
