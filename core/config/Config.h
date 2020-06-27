#pragma once
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <iostream>


namespace pt = boost::property_tree;
namespace core::config{

class Config{
    public:
        Config(std::string filepath);

        template<typename T>
        T getValue(const std::string& config_path);

        template<typename T>
        T getValue(const std::string& config_path, T defaultvalue);

    private:
        pt::ptree property_tree_;
};

template<typename T>
T Config::getValue(const std::string& config_path){
    return property_tree_.get<T>(config_path);
}

template<typename T>
T Config::getValue(const std::string& config_path, T defaultvalue){
    return property_tree_.get<T>(config_path, defaultvalue);
}

}


