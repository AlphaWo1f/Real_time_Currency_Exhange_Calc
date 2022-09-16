cmake_minimum_required(VERSION 3.23)
project(currency_simulator_tycoon)

set(CMAKE_CXX_STANDARD 23)

add_executable(currency_simulator_tycoon lib/cpp-httplib.hpp lib/json.hpp main.cpp)
target_link_libraries(currency_simulator_tycoon wsock32 ws2_32)
