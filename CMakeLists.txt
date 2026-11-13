cmake_minimum_required(VERSION 3.23)
Project (Linux-Webserver)
add_executable (server src/main.cc src/SocketWrapper.cc)

target_include_directories(server PRIVATE include)