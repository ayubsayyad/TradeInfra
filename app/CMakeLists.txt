add_executable(app TradeInfraApp.cpp)
target_link_libraries(app PUBLIC spdlog::spdlog spdlog::spdlog_header_only configlib logger)
