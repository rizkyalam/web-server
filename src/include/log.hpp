#pragma once

#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/syslog_sink.h>

class Log {
    private:
        std::shared_ptr<spdlog::logger> _logger;

    public:
        Log();
        Log(const Log &) = delete;
        Log &operator = (const Log &) = delete;

        static Log &instance();
        void info(const std::string &message);
        void warn(
            const std::string &message, 
            int line, 
            const std::string &fn
        );
        void error(
            const std::string &message, 
            int line, 
            const std::string &fn
        );
};
