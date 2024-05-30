#include "daemon.hpp"
#include "log.hpp"
#include <string>

Daemon::Daemon() {
    this->_isRunning = true;
    this->_isReload = false;
    signal(SIGINT, Daemon::_signal_handler);
    signal(SIGTERM, Daemon::_signal_handler);
    signal(SIGHUP, Daemon::_signal_handler);
}

Daemon &Daemon::instance() {
    static Daemon daemon;
    return daemon;
}

void Daemon::set_reload_fn(std::function<void()> fn) {
    this->_reloadFunc = fn;
}

bool Daemon::is_running() {
    if (this->_isReload) {
        this->_isReload = false;
        this->_reloadFunc();
    }
    return this->_isRunning;
}

void Daemon::_signal_handler(int signal) {
    std::string message = "Interrup signal number[" + std::to_string(signal) + "] received.";
    Log::instance().info(message);

    switch (signal) {
        case SIGINT:
        case SIGTERM: {
            Daemon::instance()._isRunning = false;
            break;
        }
        case SIGHUP: {
            Daemon::instance()._isReload = true;
            break;
        }
    }
}
