cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(BDE_INCLUDES "/usr/local/include/")
include_directories(AFTER SYSTEM ${BDE_INCLUDES})

LINK_DIRECTORIES("/usr/local/lib/")

project("BlackDogEngine")

# Set c++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)

# Enable testing for the Black Dog Engine Project
enable_testing()

add_subdirectory(source)
add_subdirectory(tests)

set_property(TARGET blackdogengine PROPERTY CXX_STANDARD 11)
set_property(TARGET bdemath PROPERTY CXX_STANDARD 11)

add_test(NAME BlackDogEngine COMMAND UnitTest BlackDogEngine)
add_test(NAME Geometry COMMAND UnitTest Geometry)
