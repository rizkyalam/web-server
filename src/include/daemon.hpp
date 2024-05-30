#pragma once

#include <functional>
#include <csignal>

class Daemon {
    private:
        std::function<void()> _reloadFunc;
        bool _isRunning;
        bool _isReload;

        void _reload();
        static void _signal_handler(int signal);

    public:
        Daemon();
        Daemon(const Daemon &) = delete;
        void operator = (const Daemon &) = delete;

        static Daemon &instance();
        void set_reload_fn(std::function<void()> fn);
        bool is_running();
};
