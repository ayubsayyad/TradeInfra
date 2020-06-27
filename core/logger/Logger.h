#pragma once 
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

#include <core/config/Config.h>

namespace spdlog{
    class logger;
}

namespace core::logger{
class Logger{
    public:
        Logger() : init_(false){}
        bool init(core::config::Config& config);
        void setLogLevel(core::config::Config& config);

    private:
        std::shared_ptr<spdlog::logger> spdlog_;
        bool init_;
};

}

struct Logger_Wrapper{
    Logger_Wrapper();
    static core::logger::Logger& getLogger();
};

void init_logger(core::config::Config& config);

template<typename Type>
void LOG_INFO(const Type& t){
    spdlog::info(t);
}

template<typename F, typename ... Args>
void LOG_INFO(F format, Args... args){
    spdlog::info(format, args ...);
}

