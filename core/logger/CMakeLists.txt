add_library(logger SHARED Logger.cpp)
target_link_libraries(logger PUBLIC spdlog::spdlog configlib)
#target_link_libraries(logger config)
