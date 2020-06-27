#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include "Logger.h"

using namespace core::logger;

bool Logger::init(core::config::Config& config){
    spdlog_ = spdlog::basic_logger_mt("basic_logger",
                            config.getValue<std::string>("Logger.logFileName"));


    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    setLogLevel(config);
    spdlog::set_default_logger(spdlog_);

    return init_ = true;
}

void Logger::setLogLevel(core::config::Config& config){
    auto loglevel = config.getValue<std::string>("Logger.logLevel", "INFO");
    auto level = spdlog::level::debug;

    if(loglevel == "INFO"){
        level = spdlog::level::info;
    }
    else if(loglevel == "TRACE"){
        level = spdlog::level::trace;
    }
    else if(loglevel == "DEBUG"){
        level = spdlog::level::debug;
    }
    else if(loglevel == "WARN"){
        level = spdlog::level::warn;
    }
    else if(loglevel == "ERROR"){
        level = spdlog::level::err;
    }
    spdlog::set_level(level);
}


Logger_Wrapper::Logger_Wrapper(){}

core::logger::Logger& Logger_Wrapper::getLogger(){
    static core::logger::Logger logger;
    return logger;
}

void init_logger(core::config::Config& config){
    Logger_Wrapper::getLogger().init(config);
}


