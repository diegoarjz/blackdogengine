cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

set(BDE_INCLUDES "/usr/local/include/")
include_directories(AFTER SYSTEM ${BDE_INCLUDES})

# Set c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

project("BlackDogEngine")

# Enable testing for the Black Dog Engine Project
# enable_testing()

add_subdirectory(source)
