cmake_minimum_required(VERSION 4.0)
Project (Linux-Webserver)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)


add_executable (server src/main.cc src/SocketWrapper.cc src/HttpMessage.cc)

target_include_directories(server PRIVATE include)

enable_testing()


add_executable (
    HttpSerialization tests/HttpSerialization.cc src/HttpMessage.cc
)



target_link_libraries(
  HttpSerialization
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(HttpSerialization)