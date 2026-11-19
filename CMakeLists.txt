cmake_minimum_required(VERSION 3.20)
project(SentinelFIM VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Core logic as a library (tests will link to this in Phase 5)
add_library(sentinel_core STATIC
    src/hasher.cpp
    src/scanner.cpp
    src/baseline.cpp)

target_include_directories(sentinel_core PUBLIC include)
target_link_libraries(sentinel_core PUBLIC
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
    spdlog::spdlog)

# The command-line program
add_executable(sentinel src/main.cpp)
target_link_libraries(sentinel PRIVATE sentinel_core)