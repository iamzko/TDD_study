cmake_minimum_required(VERSION 3.11)
project(tdd_study)

add_executable(first_tdd main.cpp tdd_soundexTest.cpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall ")

target_include_directories(first_tdd PUBLIC /usr/local/include/gmock)
target_include_directories(first_tdd PUBLIC /usr/local/include/gtest)
target_include_directories(first_tdd PUBLIC ./)

target_link_libraries(first_tdd gmock)
target_link_libraries(first_tdd gtest)
target_link_libraries(first_tdd pthread)
