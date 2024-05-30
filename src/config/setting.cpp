#include "setting.hpp"

Setting::Setting() {
    std::string path = "/etc/web-server/setting.yaml";
    this->_data = std::make_unique<YAML::Node>(YAML::LoadFile(path));
}

Setting &Setting::instance() {
    static Setting setting;
    return setting;
}

int Setting::get_port() const {
    int port = (*this->_data)["port"].as<int>();
    return port;
}

int Setting::get_thread_pool() const {
    int threadPool = (*this->_data)["thread-pool"].as<int>();
    return threadPool;
}

std::string Setting::get_path() const {
    std::string path = (*this->_data)["path"].as<std::string>();
    return path;
}
