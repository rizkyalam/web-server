#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <memory>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

#include "setting.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
namespace fs = boost::filesystem;
using tcp = asio::ip::tcp;

class ThreadPool {
    private:
        std::vector<std::thread> _threads;
        std::condition_variable _cv;
        std::mutex _mtx;
        bool _isStop = false;
        std::queue<std::shared_ptr<std::function<void()>>> _tasks;

        void _start(int total);
        void _stop() noexcept;
    
    public:
        ThreadPool(int total);
        ~ThreadPool();

        void enqueue(std::function<void()> task);
};

class Server {
    private:
        std::string _mime_type(const std::string &path);
        void _handle_request(
            const http::request<http::string_body> &request,
            http::response<http::string_body> &response
        );
        void _session(tcp::socket socket);
    
    public:
        void run();
};
