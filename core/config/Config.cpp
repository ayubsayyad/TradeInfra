#include "Config.h"

using namespace core::config;

Config::Config(std::string filepath){
    boost::property_tree::ini_parser::read_ini(filepath.c_str(), property_tree_);
}
    

