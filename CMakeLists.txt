cmake_minimum_required(VERSION 3.23)
Project (Linux-Webserver)
set(CMAKE_CXX_STANDARD 26)

add_executable (server src/main.cc src/SocketWrapper.cc src/HttpMessage.cc)

target_include_directories(server PRIVATE include)