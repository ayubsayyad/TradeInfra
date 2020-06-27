#include <iostream>
#include <core/config/Config.h>
#include <core/logger/Logger.h>


int main(){
    std::string str = "/mnt/e/trading-engine/TradeInfra/etc/config/TestConfig.cfg";
    core::config::Config cfg(str);
    init_logger(cfg);
    LOG_INFO("Ayub");
    LOG_INFO("Ayub {}", "Sayyad");
    return 0;
}
