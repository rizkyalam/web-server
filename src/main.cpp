#include <iostream>

#include "cmd_line_parser.hpp"
#include "server.hpp"

int main(int argc, char **argv) {
    CommandLineParser cmd(argc, argv);

    if (cmd.is_option_exist("--run")) {
        if (cmd.is_option_exist("--config")) cmd.config_service();

        Server server;
        server.run();
    } else if (cmd.is_option_exist("--help")) {
        cmd.help();
    } else {
        cmd.help();
    }

    return 0;
}
