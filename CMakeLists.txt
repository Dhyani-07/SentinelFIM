cmake_minimum_required(VERSION 3.20)
project(SentinelFIM VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(sentinel src/main.cpp)

target_include_directories(sentinel PRIVATE include)
target_link_libraries(sentinel PRIVATE
    OpenSSL::Crypto
    nlohmann_json::nlohmann_json
    spdlog::spdlog)