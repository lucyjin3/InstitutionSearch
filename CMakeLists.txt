cmake_minimum_required(VERSION 3.21)
project(COP3530FinalProject)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Textbox.h Button.h Institution.h Institution.cpp)
add_executable(COP3530FinalProject ${SOURCE_FILES})

include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(COP3530FinalProject sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

