cmake_minimum_required(VERSION 3.16)
project(TradeInfra)

set (CMAKE_CXX_STANDARD 17)
set(warnings "-Wall -Wextra -Werror")
message("VCPKG_TARGET_TRIPLET=${VCPKG_TARGET_TRIPLET}")

# Configuration options:
set(TRADE_ENGINE_BUILD_ARCH "native" CACHE STRING "Target architecture.")
set(TRADE_ENGINE_BUILD_SHARED ON CACHE BOOL "Enable shared libs.")
set(TRADE_ENGINE_VERSION "snapshot" CACHE STRING "Release version.")
set(TRADE_ENGINE_TOOLCHAIN "" CACHE PATH "Toolchain prefix.")

# Toolbox options.
set(TOOLBOX_BUILD_ARCH   "${TRADE_ENGINE_BUILD_ARCH}")
set(TOOLBOX_BUILD_SHARED "${TRADE_ENGINE_BUILD_SHARED}")
set(TOOLBOX_VERSION      "${TRADE_ENGINE_VERSION}")
set(TOOLBOX_TOOLCHAIN    "${TRADE_ENGINE_TOOLCHAIN}")

if (NOT "${TOOLBOX_TOOLCHAIN}" STREQUAL "")
  get_filename_component(TOOLBOX_TOOLCHAIN "${TOOLBOX_TOOLCHAIN}" REALPATH)
  set(CMAKE_PREFIX_PATH "${TOOLBOX_TOOLCHAIN}")
  message(STATUS "TOOLBOX_TOOLCHAIN: ${TOOLBOX_TOOLCHAIN}")
endif()



set(CMAKE_C_FLAGS_DEBUG   "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

# Intended for use with Linux Perf.
set(CMAKE_C_FLAGS_PERF   "${CMAKE_C_FLAGS_RELEASE} -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_PERF "${CMAKE_CXX_FLAGS_RELEASE} -fno-omit-frame-pointer")

# Coverage build
set(CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")

# Address sanitizer build
set(CMAKE_C_FLAGS_ASAN "${CMAKE_C_FLAGS_RELWITHDEBINFO} -fsanitize=address")
set(CMAKE_CXX_FLAGS_ASAN "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -fsanitize=address")

# Thread sanitizer build
set(CMAKE_C_FLAGS_TSAN "${CMAKE_C_FLAGS_RELWITHDEBINFO} -fsanitize=thread")
set(CMAKE_CXX_FLAGS_TSAN "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -fsanitize=thread")

if(NOT CMAKE_BUILD_TYPE)
  #set(CMAKE_BUILD_TYPE DEBUG)
  #set(CMAKE_BUILD_TYPE RELEASE)
  set(CMAKE_BUILD_TYPE RELWITHDEBINFO CACHE STRING "Choose the type of build : DEBUG, RELEASE, RELWITHDEBINFO*, MINSIZEREL PERF COVERAGE ASAN TSAN" FORCE)
  #set(CMAKE_BUILD_TYPE MINSIZEREL)
  #set(CMAKE_BUILD_TYPE PERF)
  #set(CMAKE_BUILD_TYPE COVERAGE)
endif()

message(STATUS "Build architecture: ${TOOLBOX_BUILD_ARCH}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Build version: ${TOOLBOX_VERSION}")

include_directories("./")



find_package(Boost REQUIRED)
find_package(Sqlite3 REQUIRED)
find_package(spdlog REQUIRED)
find_package(folly REQUIRED)

#find_package(folly CONFIG REQUIRED)
#target_link_libraries(main PRIVATE Folly::folly Folly::folly_deps Folly::follybenchmark Folly::folly_test_util)

add_subdirectory("core/io")
add_subdirectory("core/config")
add_subdirectory("core/logger")
add_subdirectory("core/async")
add_subdirectory("app")
add_subdirectory("test")

enable_testing()
find_package(GTest CONFIG REQUIRED)

set(CPACK_GENERATOR "TGZ;RPM;DEB")
include(CPack)
