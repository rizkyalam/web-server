#include "log.hpp"
#include <string>

Log::Log() {
    if (spdlog::get("syslog_logger") == nullptr) {
        this->_logger = spdlog::syslog_logger_mt("syslog_logger", "web-server", LOG_PID);
    } else {
        this->_logger = spdlog::get("syslog_logger");
    }
}

Log &Log::instance() {
    static Log log;
    return log;
}

void Log::info(const std::string &message) {
    this->_logger->set_level(spdlog::level::info);
    std::string infoMessage = "INFO -> " + message;
    this->_logger->info(infoMessage);
}

void Log::warn(
    const std::string &message, 
    int line, 
    const std::string &fn
) {
    this->_logger->set_level(spdlog::level::warn);
    std::string warnMessage = "WARN [line " + std::to_string(line) + "]:" + fn + "() -> " + message;
    this->_logger->warn(warnMessage);
}

void Log::error(
    const std::string &message, 
    int line, 
    const std::string &fn
) {
    this->_logger->set_level(spdlog::level::err);
    std::string errorMessage = "ERROR [line " + std::to_string(line) + "]:" + fn + "() -> " + message;
    this->_logger->error(errorMessage);
}
