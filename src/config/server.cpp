#include "server.hpp"
#include "setting.hpp"
#include "log.hpp"
#include "daemon.hpp"

#include <fstream>

std::string Server::_mime_type(const std::string &path) {
    const auto extension = fs::extension(path);
    if (extension == ".html")  return "text/html";
    if (extension == ".css")  return "text/css";
    if (extension == ".js")  return "application/javascript";
    return "application/text";
}

void Server::_handle_request(
    const http::request<http::string_body> &request,
    http::response<http::string_body> &response
) {
    std::string rootDir = Setting::instance().get_path();
    std::string target;

    if (request.target() == "/") {
        target = rootDir + "/index.html";
        Log::instance().info("Accessing file root path url: " + target);
    } else {
        target = rootDir + static_cast<std::string>(request.target());
        Log::instance().info("Accessing file: " + target);
    }

    if (!fs::exists(target) || fs::is_directory(target)) {
        response = http::response<http::string_body>(http::status::not_found, request.version());
        response.set(http::field::content_type, "text/html");
        response.body() = "<h1>404 not found</h1>\r\n";
        response.prepare_payload();
        Log::instance().warn("File not found", __LINE__, __FUNCTION__);
        return;
    }

    std::unique_ptr<std::ifstream> file = std::make_unique<std::ifstream>(target);
    if (!*file) {
        response = http::response<http::string_body>(http::status::internal_server_error, request.version());
        response.set(http::field::content_type, "text/html");
        response.body() = "<h1>500 internal server error</h1>";
        response.prepare_payload();
        Log::instance().error("Error opening file", __LINE__, __FUNCTION__);
        return;
    }

    std::string body((std::istreambuf_iterator<char>(*file)), std::istreambuf_iterator<char>());
    response = http::response<http::string_body>(http::status::ok, request.version());
    response.set(http::field::content_type, this->_mime_type(target));
    response.body() = body;
    response.prepare_payload();
}

void Server::_session(tcp::socket socket) {
    bool isClose = false;
    beast::error_code ec;

    beast::flat_buffer buffer;

    http::request<http::string_body> request;
    http::response<http::string_body> response;

    http::read(socket, buffer, request, ec);
    if (ec == http::error::end_of_stream) {
        Log::instance().error("Buffer stream error", __LINE__, __FUNCTION__);
        return;
    }

    this->_handle_request(request, response);

    http::write(socket, response, ec);
    if (ec) {
        Log::instance().error("Session failed to write http connection", __LINE__, __FUNCTION__);
        return;
    }

    socket.shutdown(tcp::socket::shutdown_send, ec);
}

void Server::run() {
    try {
        asio::io_context ioc(1);
        short unsigned int port = static_cast<short unsigned int>(Setting::instance().get_port());

        tcp::acceptor acceptor(ioc, {
            tcp::v4(), port
        });

        auto reload = [](){
            Log::instance().info("Reload function called.");
        };

        Daemon &daemon = Daemon::instance();
        daemon.set_reload_fn(reload);

        int totalThreadPool = Setting::instance().get_thread_pool();
        ThreadPool pool(totalThreadPool);

        Log::instance().info("Server listening at http://127.0.0.1:" + std::to_string(port));

        while (daemon.is_running()) {
            pool.enqueue([&]() {
                tcp::socket socket(ioc);
                acceptor.accept(socket);
                this->_session(std::move(socket));
            });
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        Log::instance().info("Web server process ended");
    } catch (const std::exception &e) {
        Log::instance().error(e.what(), __LINE__, __FUNCTION__);
    }
}
