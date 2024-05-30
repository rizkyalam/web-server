#pragma once

#include <iostream>
#include <yaml-cpp/yaml.h>
#include <memory>

class Setting {
    private:
        std::unique_ptr<YAML::Node> _data;
    
    public:
        Setting();
        Setting(const Setting &) = delete;
        Setting &operator = (const Setting &) = delete;

        static Setting &instance();

        int get_port() const;
        int get_thread_pool() const;
        std::string get_path() const;
};
